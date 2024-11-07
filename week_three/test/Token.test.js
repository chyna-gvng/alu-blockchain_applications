const MyToken = artifacts.require("MyToken");

contract("MyToken", accounts => {
    it("should put 1000000 MyToken in the first account", async () => {
        const myTokenInstance = await MyToken.deployed();
        const balance = await myTokenInstance.balanceOf(accounts[0]);
        assert.equal(balance.toString(), "1000000", "1000000 wasn't in the first account");
    });

    it("should transfer token correctly", async () => {
        const myTokenInstance = await MyToken.deployed();
        const accountOne = accounts[0];
        const accountTwo = accounts[1];

        await myTokenInstance.transfer(accountTwo, "100", { from: accountOne });
        const balanceAccountOne = await myTokenInstance.balanceOf(accountOne);
        const balanceAccountTwo = await myTokenInstance.balanceOf(accountTwo);

        assert.equal(balanceAccountOne.toString(), "999900", "Amount wasn't correctly taken from the sender");
        assert.equal(balanceAccountTwo.toString(), "100", "Amount wasn't correctly sent to the receiver");
    });
});
