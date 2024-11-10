# Blockchain File Security and Intellectual Property Protection

## Overview

This project implements a simple blockchain structure in C to secure files and intellectual property (IP) by storing file metadata and IP information in the blockchain. The blockchain is capable of detecting tampering by comparing stored hashes with recalculated hashes. The program uses the OpenSSL library for SHA-256 hashing and provides a user-friendly interface for adding blocks, verifying the blockchain, and simulating tampering.

## Features

- **Blockchain Structure**: A linked list of blocks, each containing an index, previous hash, timestamp, data, and hash.
- **Genesis Block**: The first block in the blockchain with predefined data.
- **Add Blocks**: Functionality to add new blocks to the blockchain containing file metadata and intellectual property data.
- **Hash Calculation**: SHA-256 hashing using the OpenSSL library to hash block data and store the hash in the block.
- **File Metadata Extraction**: Functions to extract metadata from files and add this metadata to a block in the blockchain.
- **Tamper Detection**: Functionality to verify the blockchain's integrity by comparing stored hashes with recalculated hashes.
- **User Interface**: A menu-driven interface for adding blocks, verifying the blockchain, printing the blockchain, simulating tampering, and exiting the program.

## Requirements

- **Programming Language**: C
- **Libraries**: OpenSSL (for SHA-256 hashing)
- **Development Environment**: Linux (Ubuntu/Debian, CentOS/RHEL, macOS with Homebrew)

## Installation

### 1. Install OpenSSL Development Libraries

#### On Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install libssl-dev
```

#### On CentOS/RHEL:
```bash
sudo yum install openssl-devel
```

#### On macOS (using Homebrew):
```bash
brew install openssl
```

### 2. Compile the Program

Navigate to the directory containing the `main.c` file and run the following command to compile the program:

```bash
gcc -o blockchain main.c -lssl -lcrypto
```

### 3. Run the Program

After successful compilation, run the program with:

```bash
./blockchain
```

## Usage

### Menu Options

1. **Add Blocks from store Directory**:
   - Automatically adds blocks for each file in the `store` directory, extracting metadata such as filename, size, and creation date.
   - Example:
     ```
     Block added for file: store/file.txt
     Block added for file: store/new.txt
     ```

2. **Verify Blockchain**:
   - Verify the integrity of the blockchain.
   - Example:
     ```
     Blockchain is valid.
     ```

3. **Print Blockchain**:
   - Print detailed information about each block in the blockchain.
   - Example:
     ```
     Block 0
     Previous Hash: 0
     Timestamp: Sun Nov 10 18:32:26 2024
     Data: Genesis Block
     Hash: 89eb0ac031a63d2421cd05a2fbe41f3ea35f5c3712ca839cbf6b85c4ee07b7a3
     -----------------------------
     Block 1
     Previous Hash: 89eb0ac031a63d2421cd05a2fbe41f3ea35f5c3712ca839cbf6b85c4ee07b7a3
     Timestamp: Sun Nov 10 18:32:32 2024
     Data: File: store/file.txt, Size: 7 bytes, Created: Sun Nov 10 18:21:35 2024
     Hash: 84394db80556ec7e65a922099a7447758465bf27138778a1c41ecfe213b83e3b
     -----------------------------
     Block 2
     Previous Hash: 84394db80556ec7e65a922099a7447758465bf27138778a1c41ecfe213b83e3b
     Timestamp: Sun Nov 10 18:32:32 2024
     Data: File: store/new.txt, Size: 6 bytes, Created: Sun Nov 10 18:32:04 2024
     Hash: 33f5bf88ac7d176216e080a8fb87db96c1c93fe4a12524e095270927d0ddc685
     -----------------------------
     ```

4. **Simulate Tampering**:
   - Enter the index of the block to tamper and input new data.
   - Example:
     ```
     Enter the index of the block to tamper: 1
     Enter new data for the block: Tampered Data
     Block tampered successfully.
     ```

5. **Exit**:
   - Exit the program.
   - Example:
     ```
     Exiting...
     ```

## Example Interaction

1. **Add Blocks from store Directory**:
   ```
   Block added for file: store/file.txt
   Block added for file: store/new.txt
   ```

2. **Verify Blockchain**:
   ```
   Blockchain is valid.
   ```

3. **Print Blockchain**:
   ```
   Block 0
   Previous Hash: 0
   Timestamp: Sun Nov 10 18:32:26 2024
   Data: Genesis Block
   Hash: 89eb0ac031a63d2421cd05a2fbe41f3ea35f5c3712ca839cbf6b85c4ee07b7a3
   -----------------------------
   Block 1
   Previous Hash: 89eb0ac031a63d2421cd05a2fbe41f3ea35f5c3712ca839cbf6b85c4ee07b7a3
   Timestamp: Sun Nov 10 18:32:32 2024
   Data: File: store/file.txt, Size: 7 bytes, Created: Sun Nov 10 18:21:35 2024
   Hash: 84394db80556ec7e65a922099a7447758465bf27138778a1c41ecfe213b83e3b
   -----------------------------
   Block 2
   Previous Hash: 84394db80556ec7e65a922099a7447758465bf27138778a1c41ecfe213b83e3b
   Timestamp: Sun Nov 10 18:32:32 2024
   Data: File: store/new.txt, Size: 6 bytes, Created: Sun Nov 10 18:32:04 2024
   Hash: 33f5bf88ac7d176216e080a8fb87db96c1c93fe4a12524e095270927d0ddc685
   -----------------------------
   ```

4. **Simulate Tampering**:
   ```
   Enter the index of the block to tamper: 1
   Enter new data for the block: Tampered Data
   Block tampered successfully.
   ```

5. **Verify Blockchain After Tampering**:
   ```
   Blockchain is tampered.
   ```
