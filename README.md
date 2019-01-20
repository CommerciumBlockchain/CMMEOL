# CommerciumContinuum
Commercium gradual transition platform

## Technical Specifications
- Algorithm: Equihash
- Max Supply: 58 million CMM
- Block Time: 60 Seconds
- Block Reward: 8 CMM, 30% to Masternode 7.5% to Founders and Stake wallet.
### Dependencies

```shell
#The following packages are needed:
sudo apt-get install build-essential pkg-config libc6-dev m4 g++-multilib autoconf libtool ncurses-dev unzip git python python-zmq zlib1g-dev wget libcurl4-gnutls-dev bsdmainutils automake curl
```

#### Linux
```shell
git clone https://github.com/CommerciumBlockchain/CommerciumContinuum
cd CommerciumContinuum
./zcutil/fetch-params.sh
./zcutil/build.sh
```

#### MacOSX and Windows
Review Dockerfile


#### Windows and Linux VPS Masternode Setup
https://github.com/CommerciumBlockchain/masternode-scripts

#### Linux to Linux VPS Masternode Setup
https://www.commercium.net/masternode-guide/
