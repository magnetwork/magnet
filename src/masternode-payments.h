

// Copyright (c) 2014-2015 The Dash developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef MASTERNODE_PAYMENTS_H
#define MASTERNODE_PAYMENTS_H

#include "sync.h"
#include "net.h"
#include "key.h"
#include "util.h"
#include "base58.h"
#include "main.h"
#include "masternode.h"

using namespace std;

class CMasternodePayments;
class CMasternodePaymentWinner;

extern CMasternodePayments masternodePayments;
extern map<uint256, CMasternodePaymentWinner> mapSeenMasternodeVotes;

void ProcessMessageMasternodePayments(CNode* pfrom, std::string& strCommand, CDataStream& vRecv);


// for storing the winning payments
class CMasternodePaymentWinner
{
public:
    int nBlockHeight;
    CTxIn vin;
    CScript payee;
    std::vector<unsigned char> vchSig;
    uint64_t score;

    CMasternodePaymentWinner() {
        nBlockHeight = 0;
        score = 0;
        vin = CTxIn();
        payee = CScript();
    }

    uint256 GetHash(){
        uint256 n2 = Hash(BEGIN(nBlockHeight), END(nBlockHeight));
        uint256 n3 = vin.prevout.hash > n2 ? (vin.prevout.hash - n2) : (n2 - vin.prevout.hash);

        return n3;
    }

    IMPLEMENT_SERIALIZE(
        READWRITE(nBlockHeight);
        READWRITE(payee);
        READWRITE(vin);
        READWRITE(score);
        READWRITE(vchSig);
    )
};

//
// Masternode Payments Class
// Keeps track of who should get paid for which blocks
//

class CMasternodePayments
{
public:
    struct MetaData {
        int spendableOutputs;
        bool hasProofOfStake;
        int lastTxHeight;
        CScript payee;
    };

private:
    std::vector<CMasternodePaymentWinner> vWinning;
    int nSyncedFromPeer;
    std::string strMasterPrivKey;
    std::string strMainPubKey;
    bool enabled;
    int nLastBlockHeight;
    int syncHeight;

    // Masternode payments meta data.
    std::map<std::string, MetaData> mapMetaData;
    std::map<uint256, std::string> mapMetaCache;
    std::map<std::string, int> mapMetaPosPayments;

public:

    CMasternodePayments() {
        strMainPubKey = "";
        enabled = false;
        syncHeight = 0;
    }

    bool SetPrivKey(std::string strPrivKey);
    bool CheckSignature(CMasternodePaymentWinner& winner);
    bool Sign(CMasternodePaymentWinner& winner);

    // Deterministically calculate a given "score" for a masternode depending on how close it's hash is
    // to the blockHeight. The further away they are the better, the furthest will win the election
    // and get paid this block
    //

    uint64_t CalculateScore(uint256 blockHash, CTxIn& vin);
    bool GetWinningMasternode(int nBlockHeight, CTxIn& vinOut);
    bool AddWinningMasternode(CMasternodePaymentWinner& winner);
    bool ProcessBlock(int nBlockHeight);
    void Relay(CMasternodePaymentWinner& winner);
    void Sync(CNode* node);
    void CleanPaymentList();
    int LastPayment(CMasternode& mn);
    int GetMinMasternodePaymentsProto();

    bool GetBlockPayee(int nBlockHeight, CScript& payee, CTxIn& vin);

    void setMetaData(const std::string& address, MetaData data, uint256 hash, bool cache)
    {
        mapMetaData[address] = data;
        if(cache){
            mapMetaCache[hash] = address;
        }
    }

    bool getMetaData(const std::string& address, MetaData& data)
    {
        std::map<std::string, MetaData>::iterator it = mapMetaData.find(address);
        if (it != mapMetaData.end()) {
            data = (*it).second;
            return true;
        }
        return false;
    }

    const std::map<std::string, MetaData>& getMetaData() { return mapMetaData; }

    bool isMetaCached(uint256 hash, std::string& address)
    {
        std::map<uint256, std::string>::iterator it = mapMetaCache.find(hash);
        if (it != mapMetaCache.end()) {
            address = (*it).second;
            return true;
        }
        return false;
    }

    void setSyncHeight(int newHeight) { syncHeight = newHeight; }
    int getSyncHeight() const { return syncHeight; }

    void addProofOfStakePayment(const std::string& address, int height)
    {
        mapMetaPosPayments[address] = height;
    }

    void updateProofOfStakePayments()
    {
        // Only keep entries which block height is within 960 from the height we synced against.
        for(std::map<std::string, int>::iterator it = mapMetaPosPayments.begin(); it != mapMetaPosPayments.end();)
        {
            if((*it).second < syncHeight - 960){
                mapMetaPosPayments.erase(it ++);
            }
            else {
                ++ it;
            }
        }
    }

    int getMinConfirms() { return std::max(1, (int)mapMetaPosPayments.size() / 3); }

    bool checkMasternode(const CMasternode& masternode, int height, bool proofOfStake, bool force = false);
};


#endif
