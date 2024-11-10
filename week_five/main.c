#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct Block {
    int index;
    char previousHash[65];
    time_t timestamp;
    char data[256];
    char hash[65];
    struct Block* next;
} Block;

typedef struct Blockchain {
    Block* genesisBlock;
    Block* lastBlock;
} Blockchain;

Block* createBlock(int index, const char* previousHash, const char* data) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->index = index;
    strncpy(newBlock->previousHash, previousHash, 64);
    newBlock->previousHash[64] = '\0'; // Ensure null-termination
    newBlock->timestamp = time(NULL);
    strncpy(newBlock->data, data, 255);
    newBlock->data[255] = '\0'; // Ensure null-termination
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data, strlen(data), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&newBlock->hash[i*2], "%02x", hash[i]);
    }
    newBlock->hash[64] = '\0'; // Ensure null-termination
    newBlock->next = NULL;
    return newBlock;
}

Blockchain* createBlockchain() {
    Blockchain* blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    blockchain->genesisBlock = createBlock(0, "0", "Genesis Block");
    blockchain->lastBlock = blockchain->genesisBlock;
    return blockchain;
}

void addBlock(Blockchain* blockchain, const char* data) {
    Block* newBlock = createBlock(blockchain->lastBlock->index + 1, blockchain->lastBlock->hash, data);
    blockchain->lastBlock->next = newBlock;
    blockchain->lastBlock = newBlock;
}

int verifyBlockchain(Blockchain* blockchain) {
    Block* current = blockchain->genesisBlock;
    while (current != NULL) {
        char recalculatedHash[65];
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)current->data, strlen(current->data), hash);
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(&recalculatedHash[i*2], "%02x", hash[i]);
        }
        recalculatedHash[64] = '\0'; // Ensure null-termination
        if (strcmp(current->hash, recalculatedHash) != 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void printBlockchain(Blockchain* blockchain) {
    Block* current = blockchain->genesisBlock;
    while (current != NULL) {
        printf("Block %d\n", current->index);
        printf("Previous Hash: %s\n", current->previousHash);
        printf("Timestamp: %s", ctime(&current->timestamp));
        printf("Data: %s\n", current->data);
        printf("Hash: %s\n", current->hash);
        printf("-----------------------------\n");
        current = current->next;
    }
}

void extractFileMetadata(const char* filePath, char* metadata) {
    struct stat fileStat;
    if (stat(filePath, &fileStat) == 0) {
        sprintf(metadata, "File: %s, Size: %ld bytes, Created: %s", filePath, fileStat.st_size, ctime(&fileStat.st_ctime));
    } else {
        sprintf(metadata, "Error extracting metadata for file: %s", filePath);
    }
}

void addFilesFromDirectory(Blockchain* blockchain, const char* directoryPath) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(directoryPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // Check if it's a regular file
                char filePath[512];
                char metadata[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, ent->d_name);
                extractFileMetadata(filePath, metadata);
                addBlock(blockchain, metadata);
                printf("Block added for file: %s\n", filePath);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}

int main() {
    Blockchain* blockchain = createBlockchain();
    int choice;
    char data[256];
    char filePath[256];

    while (1) {
        printf("1. Add Blocks from store Directory\n");
        printf("2. Verify Blockchain\n");
        printf("3. Print Blockchain\n");
        printf("4. Simulate Tampering\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFilesFromDirectory(blockchain, "store");
                break;
            case 2:
                if (verifyBlockchain(blockchain)) {
                    printf("Blockchain is valid.\n");
                } else {
                    printf("Blockchain is tampered.\n");
                }
                break;
            case 3:
                printBlockchain(blockchain);
                break;
            case 4:
                printf("Enter the index of the block to tamper: ");
                int index;
                scanf("%d", &index);
                Block* current = blockchain->genesisBlock;
                while (current != NULL && current->index != index) {
                    current = current->next;
                }
                if (current != NULL) {
                    printf("Enter new data for the block: ");
                    scanf(" %[^\n]", data);
                    strncpy(current->data, data, 255);
                    current->data[255] = '\0'; // Ensure null-termination
                    printf("Block tampered successfully.\n");
                } else {
                    printf("Block not found.\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
