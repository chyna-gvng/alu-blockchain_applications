const MyToken = artifacts.require("MyToken");

module.exports = function (deployer) {
  deployer.deploy(MyToken, 1000000000); // Deploy with an initial supply of 1,000,000,000 tokens
};
