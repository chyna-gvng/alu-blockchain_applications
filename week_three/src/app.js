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
                await window.ethereum.enable();
                const accounts = await web3.eth.getAccounts();
                account = accounts[0];
                accountSpan.textContent = account;
                walletInfo.style.display = 'block';
                connectWalletButton.style.display = 'none';
                await loadContract();
                await updateBalance();
            } catch (error) {
                console.error("User denied account access");
            }
        } else {
            console.error("Ethereum browser extension not detected");
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
        }
    });

    async function loadContract() {
        const networkId = await web3.eth.net.getId();
        const deployedNetwork = MyToken.networks[networkId];
        contract = new web3.eth.Contract(MyToken.abi, deployedNetwork && deployedNetwork.address);
    }

    async function updateBalance() {
        const balance = await contract.methods.balanceOf(account).call();
        balanceSpan.textContent = web3.utils.fromWei(balance, 'ether');
    }
});
