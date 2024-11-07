document.addEventListener('DOMContentLoaded', async () => {
    let web3;
    let contract;
    let account;

    const connectWalletButton = document.getElementById('connectWallet');
    const walletInfo = document.getElementById('walletInfo');
    const accountSpan = document.getElementById('account');
    const balanceSpan = document.getElementById('balance');
    const toAddressInput = document.getElementById('toAddress');
    const amountInput = document.getElementById('amount');
    const transferButton = document.getElementById('transfer');

    connectWalletButton.addEventListener('click', async () => {
        if (window.ethereum) {
            web3 = new Web3(window.ethereum);
            try {
                const accounts = await window.ethereum.request({ method: 'eth_requestAccounts' });
                account = accounts[0];
                accountSpan.textContent = account;
                walletInfo.style.display = 'block';
                connectWalletButton.style.display = 'none';
                await loadContract();
                await updateBalance();
            } catch (error) {
                if (error.code === 4001) {
                    console.error("User denied account access");
                    alert("Please connect your wallet to use this DApp.");
                } else {
                    console.error("Error connecting to wallet:", error);
                }
            }
        } else {
            console.error("Ethereum browser extension not detected");
            alert("Please install MetaMask to use this DApp.");
        }
    });

    transferButton.addEventListener('click', async () => {
        const toAddress = toAddressInput.value;
        const amount = web3.utils.toWei(amountInput.value, 'ether');
        try {
            await contract.methods.transfer(toAddress, amount).send({ from: account });
            await updateBalance();
            alert('Transfer successful!');
        } catch (error) {
            console.error("Error transferring tokens:", error);
            alert("Transfer failed. Please try again.");
        }
    });

    async function loadContract() {
        const MyToken = await fetch('MyToken.json').then(response => response.json());
        const networkId = await web3.eth.net.getId();
        const deployedNetwork = MyToken.networks[networkId];
        contract = new web3.eth.Contract(MyToken.abi, deployedNetwork && deployedNetwork.address);
    }

    async function updateBalance() {
        const balance = await contract.methods.balanceOf(account).call();
        balanceSpan.textContent = web3.utils.fromWei(balance, 'ether');
    }
});
