# Token Transfer DApp

This is a decentralized application (DApp) that allows users to transfer tokens between accounts on the Ethereum blockchain. The DApp is built using Solidity for the smart contract, and HTML, CSS, and JavaScript for the frontend.

## Setup Instructions

1. **Install Node.js and npm**:
   - Ensure you have Node.js and npm installed. You can check this by running:
     ```bash
     node -v
     npm -v
     ```
   - If not installed, download and install from [nodejs.org](https://nodejs.org/).

2. **Install Truffle**:
   - Install Truffle globally using npm:
     ```bash
     npm install -g truffle
     ```

3. **Install Dependencies**:
   - Navigate to your project directory and initialize a new npm project:
     ```bash
     npm init -y
     ```
   - Install necessary dependencies:
     ```bash
     npm install @truffle/hdwallet-provider dotenv web3
     ```

4. **Set Up Environment Variables**:
   - Create a `.env` file in the root directory and add your Alchemy API key and mnemonic phrase:
     ```plaintext
     ALCHEMY_API_KEY=your_alchemy_api_key_here
     MNEMONIC=your mnemonic phrase here
     ```

5. **Deploy the Contract**:
   - Deploy the contract to the Sepolia testnet:
     ```bash
     truffle migrate --network sepolia
     ```

6. **Run the DApp**:
   - Open the `index.html` file in your browser.

## Testing the DApp

- Run the tests:
  ```bash
  truffle test
