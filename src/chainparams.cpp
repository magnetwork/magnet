// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "base58.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 91;
        pchMessageStart[1] = 62;
        pchMessageStart[2] = 173;
        pchMessageStart[3] = 204;
        vAlertPubKey = ParseHex("04efa3a230591895a2a274a733989e10bd15f9cf7bfc26fcfc2d72d872378bd208c59f7809220154bd808b53abbd422e864f359105f277a30026752fd404a0fc76");
        nDefaultPort = 17177;
        nRPCPort = 17178;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block.
            // transaction:  Coinbase(hash=3c8eb5ab2277426f2f48bd70eeb32416b1c94456a3e56e1871d15b568dde3e1e, nTime=1508673600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            // CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a284f63742032322c20323031373a20426974636f696e2070726963652061626f76652024362c303030)
            // CTxOut(empty)

        const char* pszTimestamp = "Oct 22, 2017: Bitcoin price above $6,000";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        //vout[0].nValue = 500000 * COIN;
        //vout[0].scriptPubKey.SetDestination(address.Get());
        //vout[0].scriptPubKey = CScript() << ParseHex("0417acd980bb51a07ffe27ed06ff4c04d42621692d4a611afc74888abe3ba3248abc89466705d44944c61953a680ba6cb7f0111190627291a2481ed8ddf706e684") << OP_CHECKSIG;
        CTransaction txNew(1, 1508673600, vin, vout, 0);

        LogPrintf("genesis mainnet transaction:  %s\n", txNew.ToString().c_str());

        genesis.vtx.push_back(txNew);

        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1508673600;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact(); 
        genesis.nNonce   = 54489;

        // Mine the genesis block.
        if (false)
        {
            hashGenesisBlock = uint256("0x01");
            LogPrintf("recalculating params for mainnet.\n");
            LogPrintf("old mainnet genesis nonce: %d\n", genesis.nNonce);
            LogPrintf("old mainnet genesis hash:  %s\n", hashGenesisBlock.ToString().c_str());
            // deliberately empty for loop finds nonce value.
            for(genesis.nNonce = 0; genesis.GetHash() > (~uint256(0) >> 16); genesis.nNonce++){ }
            LogPrintf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
            LogPrintf("new mainnet genesis nonce: %d\n", genesis.nNonce);
            LogPrintf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString().c_str());
        }

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00002f0bcbcd210c16700d44e506d605553d6ee891e81e644a1b184ed512354f"));
        assert(genesis.hashMerkleRoot == uint256("0x3c8eb5ab2277426f2f48bd70eeb32416b1c94456a3e56e1871d15b568dde3e1e"));

        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,51);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,83);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("First",  "txdns.infernopool.com"));
        vSeeds.push_back(CDNSSeedData("Second",  "txdns2.infernopool.com"));
        vSeeds.push_back(CDNSSeedData("Third",  "txdns3.infernopool.com"));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);    

        vFixedSeeds.clear();
        vSeeds.clear();

        nPoolMaxTransactions = 3;
        //strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "MqXy5e1QhqYgUqXn8mWqhn1dogj2caf7hb";
        nLastPOWBlock = 15000;
        nPOSStartBlock = 1000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 231;
        pchMessageStart[1] = 96;
        pchMessageStart[2] = 51;
        pchMessageStart[3] = 129;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04efa3a230591895a2a274a733989e10bd15f9cf7bfc26fcfc2d72d872378bd208c59f7809220154bd808b53abbd422e864f359105f277a30026752fd404a0fc76");
        nDefaultPort = 27170;
        nRPCPort = 27171;
        strDataDir = "testnet";

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00002f0bcbcd210c16700d44e506d605553d6ee891e81e644a1b184ed512354f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,73);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,83);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
