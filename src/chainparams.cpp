// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "key_io.h"
#include "main.h"
#include "crypto/equihash.h"

#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 520617983 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nSolution = nSolution;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database (and is in any case of zero value).
 *
 * >>> from pyblake2 import blake2s
 * >>> 'Commercium' + blake2s(b'2018-01-01 Commercium is born.').hexdigest()
 */

static CBlock CreateGenesisBlock(uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Commercium5b983e3f258fb03419cbb777bf926eacc96a9f1affd5294d11cf0c351a6785fd";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nSolution, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        strCurrencyUnits = "CMM";
        bip44CoinType = 767; // As registered in https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 8000;
        consensus.nSubsidyHalvingInterval = 60 * 24 * 365;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        consensus.nMasternodePaymentsStartBlock = 1200;
        consensus.nMasternodePaymentsIncreasePeriod = 43200; // 1 month

        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 1 * 60; // 1 min
        consensus.nPowAllowMinDifficultyBlocksAfterHeight = boost::none;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nProtocolVersion = 170006;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nProtocolVersion = 170006;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nProtocolVersion = 170007;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nActivationHeight = 100;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nProtocolVersion = 170008;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nActivationHeight = 100;
        // The best chain should have at least this much work.
	consensus.nMinimumChainWork = uint256S("0000000000000000000000000000000000000000000000000000000000000767");
        /**
         * The message start string should be awesome! Ⓢ❤
         */
        pchMessageStart[0] = 0xba;
        pchMessageStart[1] = 0xad;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x55;
        vAlertPubKey = ParseHex("04388fbebb11406e3760971a8f21d410009df52c3c14aa6856626fccd815da45e3d3e3cf323a2087692b1ead972cf6300731f1f8cd3617b8d739526f213dd9f138");
        nDefaultPort = 2019;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 100000;
        newTimeRule = 246600;
        eh_epoch_1 = eh200_9;
        eh_epoch_2 = eh200_9;
        eh_epoch_1_endblock = 1;
        eh_epoch_2_startblock = 2;

        nMasternodeCountDrift = 0;

        genesis = CreateGenesisBlock(
            1546139923,
            uint256S("0x0000000000000000000000000000000000000000000000000000000000000767"),
            ParseHex("0023b23f1d0ca4068453e474d644343b1931be7209105c21f2900f3fc9ce03b411ce7d9406007d57d776043b56eddfd47c1fe51e80d343c79255890daf9c4f0da14892d7d44547504b219ed55083ba122778aa6906c02c83e861bb759c6d38af025fcaab8c16def1c80753c44a8a82d477e73fc304736ca1eaae5757f90c0cb3b8c818c571317f1912d8cc7a34f332229acdf151029fb3a1e92d07cff2294ccb732baf735a7bfd2603c90d58b696300ab37c543bc0a3753a65c65b9fb00e6a18e24e23c7c3cd02226c56f486e2c951d83f4210a5d333cc45424e79a8d86c6ee4d5d385851cebc24329de4204115f8d6d7cb45282579d16791179374003e82269e1de683ddb6be714f9dfe85ecad99c9c9807fdd64ad64453dce51e30a2455848c5463715107103f4d6ed10cf9143645020b375dbf27c54b9eef2fd3f16568ece5614a174a0d671f1cd4dd1ba3cf59e6f012bec66227710a1f1d5c253399c31f4ced1c730ac113672b085c64b518fa8e28cf3f0953ed8eb7e669814e24f4547c5fd370365a2998625c25cbe61ec5a074008a6c1a814fdff9b5035a27d636635a92e1d6dee1b723eb8eb09f23596a3e27370e91ecccccd98ce861c67e9e1b21434758282977bbe4e80f6292f1de5f21fa7d125d2db16bb141d635ac1ad5b2578082db1ac29ae1daa8d4ffdd9c52ba6fec156154fb33bfee33802725f0d48422868e8248488f7da7a57d0569fcd5d0b881b818f16b121ee17036019ad8eaa9bb158f6262d4a77b95ff50b7dd84e32d786d1d64a8eb157469b7b5605a8f9f5c627f43759e86f6c8466b31ffc027806881211e1a05009561348010042614e58aab3aa5736eb7f5dd19312cd1ae51892d9f31b7ee183d7dc3a06d261a115074b2848dc151be236c2019c79b2487b0988c38dd0c87731ce1452756255ac2de142bbf0490176297f2b6b4b5ba94b50487aeaa22c2fc410f8d404c840760d0ff723316f63d092be61ae9faf7972350826fac76f1dd0c8fe4811d72d306e607694c5609e0e9dc3f57a217491274df1764aba982d9523af8f36093e066e21c922a9b3cb12dbb02012756fcd183506490ba67dc5ac0bcbf8d9a609b5dc07e6985cf6718b213a02c6510c6da4ed7594eca3a816857083beaa4a3e221c05f061ca43fdeb74158bda6b62945c96a6db03ed4f012e49ee2485948372e267bfed14b4f7290d2600ee0104612bb9bc54d2ed405daa01c48b9dbc9f075494c7dc82bf9be6265b1f9c7fa15b0cbb1ea54027efffb030251a5f68d8b4598ef9d3ff2d553d09ad04db6e9f2c31e54fa165e1a0ba6a6f49fcf1f5e9d30845bbbae949742742af13ecfb5f678b0ea1f8aecc2306b68c49ec0bfb6cb24b40df77c6cf2e1c5f24ea3750d4cd03565ad5e0b315f66dbe2665aa1ed477e005716bf7a5eb8e05b4b2985932fb7ea25d2a3745f246110d597e9436878534299ca07d7cbe940938c2e117a0aceae9506fa9e53319cd0be925f36b147cd04320359baee2242f27c38ec3597d2fdf5e24251df76a0d805126c459a7a100c9ab0a35edd1435d341eef051d24baf8d7150186b90ed5555444ad424bf8156925118662b0be8d381bc97bf4b9d963fa0a256c5965bf291d77e12dcd4ca3ba31a806347acca6ecbe9934420663a4d7b6b73451c63cc50636bad48973a3d0970a4a0b339da62924cf82e929776775ecaf8d661f5f330ee3cf65f4d440e39af9549716767b5d50199217b21573b4f8d06969c7e49ac3e74f7566952693902fdb15cc5e89cb4e6f7688bba456ad2438ad6a384fa5341d1f372dad1d4163621e8612ade204d9faebf26e7e17e8424b525211b3721662a803a9d03dee45f049fd2417133e281c525d43b4f5a732c3ec5970d74c3597"),
            0x1f07ffff, 4, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00069418c278f4defdf27e431e82e35d640a6a95d9413bea1f80543c8eccb9a4"));
        assert(genesis.hashMerkleRoot == uint256S("0x2c27c06852f8cb8b5c68adeb46f87a7dbbc3db18094e2a44d5df690546e35fac"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("seed04.commercium.net", "seed04.commercium.net")); //Commercium seed node
        vSeeds.push_back(CDNSSeedData("seed03.commercium.net", "seed03.commercium.net")); //Commercium seed node
        vSeeds.push_back(CDNSSeedData("seed02.commercium.net", "seed02.commercium.net")); //Commercium seed node
        vSeeds.push_back(CDNSSeedData("seed01.commercium.net", "seed01.commercium.net")); //Commercium seed node

        // guarantees the first character, when base58 encoded, is "C"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1C};
        // the first character of MULTISIG, when base58 encoded, is "M"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x33};
        // the first character, when base58 encoded, is "M"
        base58Prefixes[SECRET_KEY]         = {0x8C};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x88,0xB2,0x1E};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x88,0xAD,0xE4};
        // guarantees the first 2 characters, when base58 encoded, are "zc"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0x9A};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVK"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAB,0xD3};
        // guarantees the first 2 characters, when base58 encoded, are "SK"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAB,0x36};

        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "zs";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "zviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "zivks";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "secret-extended-key-main";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;
	fHeadersFirstSyncingActive = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
          //  (0, consensus.hashGenesisBlock),
	    (0, uint256S("0x00069418c278f4defdf27e431e82e35d640a6a95d9413bea1f80543c8eccb9a4"))
            (500, uint256S("0x0000026851a98e7cb0c299128145468728eaf5b056d1c7a8bee3efa794d153f2")),
            1547262827,     // * UNIX timestamp of last checkpoint block
            505,              // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            1222            // * estimated number of transactions per day after checkpoint
                            //   total number of tx / (checkpoint block height / (24 * 24))
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
            "MZMN4YjaYhnnDgMWLQVC93LuCPFJ51tBwT", /* main-index: 0*/
            "MujoWRKHEy3ndn2V5JZrXhQSiy3huZPV8U", /* main-index: 1*/
            "MqdZ2ji6rX2HsBXdt9WpES2RSaE7R6A5zF", /* main-index: 2*/
        };
        nPoolMaxTransactions = 3;
        strSporkKey = "03fdf4907810a9f5d9462a1ae09feee5ab205d32798b0ffcc379442021f84c5bbf";

        strObfuscationPoolDummyAddress = "CVM2U1RDmX7sezRgiYwSDxcLsHkYXLzAPj";
        nStartMasternodePayments = 1546862400; //2019-01-07
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        strCurrencyUnits = "CMMT";
        bip44CoinType = 1;
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 8000;
        consensus.nSubsidyHalvingInterval = 60 * 24 * 365 * 4;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 400;
        consensus.powLimit = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.nPowAllowMinDifficultyBlocksAfterHeight = 13000;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nProtocolVersion = 170006;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nProtocolVersion = 170006;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nProtocolVersion = 170007;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nActivationHeight = 11000;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nProtocolVersion = 170008;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nActivationHeight = 11200;
        consensus.nMasternodePaymentsStartBlock = 1500;
        consensus.nMasternodePaymentsIncreasePeriod = 200;

		// The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0xf9;
        pchMessageStart[3] = 0xbf;
        vAlertPubKey = ParseHex("044e7a1553392325c871c5ace5d6ad73501c66f4c185d6b0453cf45dec5a1322e705c672ac1a27ef7cdaf588c10effdf50ed5f95f85f2f54a5f6159fca394ed0c6");
        nDefaultPort = 22019;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 1000;
        eh_epoch_1 = eh200_9;
        eh_epoch_2 = eh144_5;
        eh_epoch_1_endblock = 7600;
        eh_epoch_2_startblock = 7583;


    	genesis = CreateGenesisBlock(
            1546144639,
            uint256S("0000000000000000000000000000000000000000000000000000000000000231"),
            ParseHex("0066c401f2a4df15ba0c85e8a7c3351987c05450ba0917b5e2d715a677e0f5c3dd8dee4e12197394d874007f28a3464881b87d8e67190bbfe6174d375a74972647060292181b5df2f5068c8f66475a4c95f3d49b040ddf0ca7a78a09a768578523f2f362d13a96dbfc2607fd9cf069db79feb2e35742cc724acf82f95cd511a631ff2a920907d828c494d23d6e85a81bbf852d34d03f143412938cabcdb6b5fc79f7f63ee237f3230269de68cc5c27791d2005eaabfcd1facba1f8096515e7cb4f18cb81575c4615740058b5466732beff790612fe1cee6bc2bdff46f16a365e6a755f5c1fddb21a438a4b8edcb829f57c56399b73051a9967f603300bdd59de236c1987b872c0f3029663b78a0bdfea5e0cbb0c9e116c1031e65b717e2c533a12285b7a458f0c4b2a50014d1c7c8ec3c22b0f74d3e150a94abd855aec9b144065e347a18465f294b90ff6807c9e7db60284ee7e7e05631434d5b44b35bad9c930a413f4de04e2cb7dba523befe1c1e0ffdeae3ca23a357c8813300bd20302e5950f6d5db56b8ae2aee62c8115371c48bb6f4ab36d2747ded614e47dc1429f9164ddc30104ea9970cacb229e6d63e5b533333e8593596e84f6378ae58a7f1de141c152855924cc068a21e3f68c44122f8abd5fe8bf43fa8f08ae47522a3a5d177a97ac1ed967dbc85f5befb80125a6bb78fe69bf884e8cac0c3feb9eb88d46d139b511a1992b7cee131d1a06173c05b9e1059fcda174ade4cf445b5741caa59836a30e75b79a111b6dcdce7d05e90c563ac6afbc7ad3db10ce3f300621d6ff7de971caf95f49f4a5987864360cb7d5418c4fd9b92907d84336de331a2f023a32910f51a91136abab85eec663d8942f6204fdcaafa70c158c86ff019aa6d53435b50aa973d929cb695d4a0b237f0a1945d04b7f2ac0d66652d305c6ff08d892fc0089981b139c99f5460fe6ac26461dde88a796bfe9298b1de757593fe59c554554a9e9c4974190bdc94d0ba29b687bb51591f42c125e66edb2651c1a4aff5b142958c3e9118bb0fd1514fe3a70dc531d0dbcb04d04892d1f21aea151d6ff17220eedc479eba1f838da3537de77971fe9cf5ba606450b7754bf6bf03dcc3008d9f6213c57ed0146f052b5bdbb5c599b1e8e5fac1e5f0571c907f0fc454165218535ba0f5a317c0ed4017be77182cc5726897de85ee7ca99eee021f9dc550497e832882236f1f70491492b506b42a046d5602c1b59c2e56a982a2ac73ce68138c002ce46f0958c703343830e15711a63f73eb5b61b68fc1d7a370e52540a3d22c96ba4f32b362fd29ea5d004e0c8fbe749c325efda6d8dccdd01110e33b423b21ba2a4901b191323785f6fe59bcfdf103eb2a19f785cd5f1b0dc6a764e0c462fa9aa007d814b58c9dcdba3b28da61f9b4a015c481658085399fc7b8414f3eaaf25380bf61a653fbd6d301f9980f0f4c9a6a657ce986e065fffd0ec0f743a35698486e36765040a3f5989495fae8e2d011bbc0d4cddb0ed0f890861ec993830c5283b71a56302ddfc05b2e2e16396c143b1e5266883a8939e92d72311f25df2b1c41faf8a82ce2cf8a90cd46947d2b52bbf03f1b5ec2465903bb37b2ce3d108f4ae99be7a8dbc4499083db295f7e768f2c4f72c0b664d3dfa8502160ac7cd530f499dbee1e0e1bf3e950ace565f482aa23e1c345184d8a08f054afce2bf8a8f291877d9234af4caa2b11cd1a23ff49d69ff03e5896b6ee9cd2b78cde99690ca3bb02c13b11efac7b50a51deabda039c085ba7c49fe508fdf4c435589a4a669bf3ebe00e3006e9581deca1b40f9166ef5d71bacf155e59ab088a07fdb28bd3c7fea7416f8615806223be155a862053eef1094d049da2aa5ab0185aab4ee7e0db1453"),
            0x2007ffff, 4, 0);

		consensus.hashGenesisBlock = genesis.GetHash();

//        assert(consensus.hashGenesisBlock == uint256S("0x00078b6e9ca0592873fd6030bfaa237a3051c9c6775d2c8d3497f1bee896a4fa"));
//        assert(genesis.hashMerkleRoot == uint256S("0x21a36313979029de20976f0cc6ea5988d1989280fd3a1f2f826673dbbb882524"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("test02.commercium.net", "test02.commercium.net")); // Commercium
        vSeeds.push_back(CDNSSeedData("test01.commercium.net", "test01.commercium.net")); // Commercium

        // guarantees the first 2 characters, when base58 encoded, are "tm"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1D,0x25};
        // guarantees the first 2 characters, when base58 encoded, are "t2"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBA};
        // the first character, when base58 encoded, is "9" or "c" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        // guarantees the first 2 characters, when base58 encoded, are "zt"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVt"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        // guarantees the first 2 characters, when base58 encoded, are "ST"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};

        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ztestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "zviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "zivktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "secret-extended-key-test";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

		checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, consensus.hashGenesisBlock),
            1546144639,  // * UNIX timestamp of last checkpoint block
            0,       // * total number of transactions between genesis and last checkpoint
                         //   (the tx=... number in the SetBestChain debug.log lines)
            715          //   total number of tx / (checkpoint block height / (24 * 24))
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
            "t2UNzUUx8mWBCRYPRezvA363EYXyEpHokyi"
            };
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());

		nStartMasternodePayments = 1546144639; //2018-29-12
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        strCurrencyUnits = "REG";
        bip44CoinType = 1;
        consensus.fCoinbaseMustBeProtected = false;
        consensus.nSubsidySlowStartInterval = 0;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 0; // Turn off adjustment down
        consensus.nPowMaxAdjustUp = 0; // Turn off adjustment up
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.nPowAllowMinDifficultyBlocksAfterHeight = 0;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nProtocolVersion = 170002;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nProtocolVersion = 170002;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nProtocolVersion = 170006;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nProtocolVersion = 170007;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xe8;
        pchMessageStart[2] = 0x3f;
        pchMessageStart[3] = 0x5f;
        nDefaultPort = 26114;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 1000;
        eh_epoch_1 = eh48_5;
        eh_epoch_2 = eh48_5;
        eh_epoch_1_endblock = 1;
        eh_epoch_2_startblock = 1;

    	genesis = CreateGenesisBlock(
            1546145182,
            uint256S("00000000000000000000000000000000000000000000000000000000000027a9"),
            ParseHex("020c8e7be26cbb01b013702a5c64b5296607048e63da513ead513c29d30f7f079fa2572d"),
            0x200f0f0f, 4, 0);

        consensus.hashGenesisBlock = genesis.GetHash();

//        assert(consensus.hashGenesisBlock == uint256S("0x0003b244a6b5c08c189c4ea4e692b2d8f4d690148c32ec3ec4594e3516d11fd2"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, consensus.hashGenesisBlock),
            0,
            0,
            0
        };
        // These prefixes are the same as the testnet prefixes
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1D,0x25};
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBA};
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};

        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "zregtestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "zviewregtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "zivkregtestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "secret-extended-key-regtest";

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = { "t2f9nkUG1Xe2TrQ4StHKcxUgLGuYszo8iS4" };
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_SPROUT && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);

    // Some python qa rpc tests need to enforce the coinbase consensus rule
    if (network == CBaseChainParams::REGTEST && mapArgs.count("-regtestprotectcoinbase")) {
        regTestParams.SetRegTestCoinbaseMustBeProtected();
    }
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}


// Block height must be >0 and <=last founders reward block height
// Index variable i ranges from 0 - (vFoundersRewardAddress.size()-1)
std::string CChainParams::GetFoundersRewardAddressAtHeight(int nHeight) const {
    int maxHeight = consensus.GetLastFoundersRewardBlockHeight();
    assert(nHeight > 0 && nHeight <= maxHeight);

    size_t addressChangeInterval = (maxHeight + vFoundersRewardAddress.size()) / vFoundersRewardAddress.size();
    size_t i = nHeight / addressChangeInterval;
    return vFoundersRewardAddress[i];
}

// Block height must be >0 and <=last founders reward block height
// The founders reward address is expected to be a multisig (P2SH) address
CScript CChainParams::GetFoundersRewardScriptAtHeight(int nHeight) const {
    assert(nHeight > 0 && nHeight <= consensus.GetLastFoundersRewardBlockHeight());

    CTxDestination address = DecodeDestination(GetFoundersRewardAddressAtHeight(nHeight).c_str());
    assert(IsValidDestination(address));
    assert(boost::get<CScriptID>(&address) != nullptr);
    CScriptID scriptID = boost::get<CScriptID>(address); // address is a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script;
}

std::string CChainParams::GetFoundersRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vFoundersRewardAddress.size());
    return vFoundersRewardAddress[i];
}


int validEHparameterList(EHparameters *ehparams, unsigned long blockheight, const CChainParams& params){
    //if in overlap period, there will be two valid solutions, else 1.
    //The upcoming version of EH is preferred so will always be first element
    //returns number of elements in list
    if(blockheight>=params.eh_epoch_2_start() && blockheight>params.eh_epoch_1_end()){
        ehparams[0]=params.eh_epoch_2_params();
        return 1;
    }
    if(blockheight<params.eh_epoch_2_start()){
        ehparams[0]=params.eh_epoch_1_params();
        return 1;
    }
    ehparams[0]=params.eh_epoch_2_params();
    ehparams[1]=params.eh_epoch_1_params();
    return 2;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
