/*
 * Copyright (c) 2018 Zilliqa
 * This source code is being disclosed to you solely for the purpose of your
 * participation in testing Zilliqa. You may view, compile and run the code for
 * that purpose and pursuant to the protocols and algorithms that are programmed
 * into, and intended by, the code. You may not do anything else with the code
 * without express permission from Zilliqa Research Pte. Ltd., including
 * modifying or publishing the code (or any part of it), and developing or
 * forming another public or private blockchain network. This source code is
 * provided 'as is' and no warranties are given as to title or non-infringement,
 * merchantability or fitness for purpose and, to the extent permitted by law,
 * all liability for your use of the code is disclaimed. Some programs in this
 * code are governed by the GNU General Public License v3.0 (available at
 * https://www.gnu.org/licenses/gpl-3.0.en.html) ('GPLv3'). The programs that
 * are governed by GPLv3.0 are those programs that are located in the folders
 * src/depends and tests/depends and which include a reference to GPLv3 in their
 * program files.
 */

#include "TestUtils.h"

using namespace std;
using namespace boost::multiprecision;

namespace TestUtils {
void Initialize() { rng.seed(std::random_device()()); }

uint8_t DistUint8() {
  return RandomIntInRng<uint8_t>(std::numeric_limits<uint8_t>::min(),
                                 std::numeric_limits<uint8_t>::max());
}
uint16_t DistUint16() {
  return RandomIntInRng<uint16_t>(std::numeric_limits<uint16_t>::min(),
                                  std::numeric_limits<uint16_t>::max());
}
uint32_t DistUint32() {
  return RandomIntInRng<uint32_t>(std::numeric_limits<uint32_t>::min(),
                                  std::numeric_limits<uint32_t>::max());
}
uint32_t DistUint64() {
  return RandomIntInRng<uint64_t>(std::numeric_limits<uint64_t>::min(),
                                  std::numeric_limits<uint64_t>::max());
}
// Doesn't work!
//uint32_t DistUint128() {
//  return RandomIntInRng<uint128_t>(std::numeric_limits<uint128_t>::min(),
//                                  std::numeric_limits<uint128_t>::max());
//}
uint8_t Dist1to99() { return RandomIntInRng<uint8_t>((uint8_t)1, (uint8_t)99); }

PubKey GenerateRandomPubKey() { return PubKey(PrivKey()); }

Peer GenerateRandomPeer() {
  uint128_t ip_address = DistUint32();
  uint32_t listen_port_host = DistUint32();
  return Peer(ip_address, listen_port_host);
}

Peer GenerateRandomPeer(uint8_t bit_i, bool setreset) {
  uint128_t ip_address = DistUint32();
  uint32_t listen_port_host = DistUint32();
  if (setreset){
    ip_address |= 1UL << bit_i;
  }
  else{
    ip_address &= ~(1UL << bit_i);
  }
  return Peer(ip_address, listen_port_host);
}

PubKey GenerateRandomPubKey(PrivKey privK) { return PubKey(privK); }

KeyPair GenerateRandomKeyPair(){
  PrivKey privk;
  return KeyPair(privk, GenerateRandomPubKey(privk));
}

DSBlockHeader GenerateRandomDSBlockHeader() {
  uint8_t dsDifficulty = DistUint8();
  uint8_t difficulty = DistUint8();
  BlockHash prevHash;
  PubKey leaderPubKey = GenerateRandomPubKey();
  uint64_t blockNum = DistUint32();
  uint256_t timestamp = DistUint32();
  SWInfo swInfo;
  map<PubKey, Peer> powDSWinners;
  DSBlockHashSet hash;
  CommitteeHash committeeHash;
  for (unsigned int i = 0; i < 3; i++) {
    powDSWinners.emplace(GenerateRandomPubKey(), GenerateRandomPeer());
  }

  return DSBlockHeader(dsDifficulty, difficulty, prevHash, leaderPubKey,
                       blockNum, timestamp, swInfo, powDSWinners, hash,
                       committeeHash);
}

MicroBlockHeader GenerateRandomMicroBlockHeader() {
  uint8_t type = DistUint8();
  uint32_t version = DistUint32();
  uint32_t shardId = DistUint32();
  uint256_t gasLimit = DistUint32();
  uint256_t gasUsed = DistUint32();
  uint256_t rewards = DistUint32();
  BlockHash prevHash;
  uint64_t blockNum = DistUint32();
  uint256_t timestamp = DistUint32();
  TxnHash txRootHash;
  uint32_t numTxs = Dist1to99();
  PubKey minerPubKey = GenerateRandomPubKey();
  uint64_t dsBlockNum = DistUint32();
  BlockHash dsBlockHash;
  StateHash stateDeltaHash;
  TxnHash tranReceiptHash;
  CommitteeHash committeeHash;

  return MicroBlockHeader(type, version, shardId, gasLimit, gasUsed, rewards,
                          prevHash, blockNum, timestamp, txRootHash, numTxs,
                          minerPubKey, dsBlockNum, dsBlockHash, stateDeltaHash,
                          tranReceiptHash, committeeHash);
}

TxBlockHeader GenerateRandomTxBlockHeader() {
  uint8_t type = DistUint8();
  uint32_t version = DistUint32();
  uint256_t gasLimit = DistUint32();
  uint256_t gasUsed = DistUint32();
  uint256_t rewards = DistUint32();
  BlockHash prevHash;
  uint64_t blockNum = DistUint32();
  uint256_t timestamp = DistUint32();
  TxnHash txRootHash;
  StateHash stateRootHash;
  StateHash deltaRootHash;
  StateHash stateDeltaHash;
  TxnHash tranReceiptRootHash;
  uint32_t numTxs = Dist1to99();
  uint32_t numMicroBlockHashes = Dist1to99();
  PubKey minerPubKey = GenerateRandomPubKey();
  uint64_t dsBlockNum = DistUint32();
  BlockHash dsBlockHeader;
  CommitteeHash committeeHash;

  return TxBlockHeader(type, version, gasLimit, gasUsed, rewards, prevHash,
                       blockNum, timestamp, txRootHash, stateRootHash,
                       deltaRootHash, stateDeltaHash, tranReceiptRootHash,
                       numTxs, numMicroBlockHashes, minerPubKey, dsBlockNum,
                       dsBlockHeader, committeeHash);
}

VCBlockHeader GenerateRandomVCBlockHeader() {
  uint64_t vieWChangeDSEpochNo = DistUint32();
  uint64_t viewChangeEpochNo = DistUint32();
  unsigned char viewChangeState = DistUint8();
  uint32_t expectedCandidateLeaderIndex = DistUint32();
  Peer candidateLeaderNetworkInfo = GenerateRandomPeer();
  PubKey candidateLeaderPubKey = GenerateRandomPubKey();
  uint32_t vcCounter = DistUint32();
  uint256_t timestamp = DistUint32();
  CommitteeHash committeeHash;

  return VCBlockHeader(vieWChangeDSEpochNo, viewChangeEpochNo, viewChangeState,
                       expectedCandidateLeaderIndex, candidateLeaderNetworkInfo,
                       candidateLeaderPubKey, vcCounter, timestamp,
                       committeeHash);
}

FallbackBlockHeader GenerateRandomFallbackBlockHeader() {
  uint64_t fallbackDSEpochNo = DistUint32();
  uint64_t fallbackEpochNo = DistUint32();
  unsigned char fallbackState = DistUint8();
  StateHash stateRootHash;
  uint32_t leaderConsensusId = DistUint32();
  Peer leaderNetworkInfo = GenerateRandomPeer();
  PubKey leaderPubKey = GenerateRandomPubKey();
  uint32_t shardId = DistUint32();
  uint256_t timestamp = DistUint32();
  CommitteeHash committeeHash;

  return FallbackBlockHeader(fallbackDSEpochNo, fallbackEpochNo, fallbackState,
                             stateRootHash, leaderConsensusId,
                             leaderNetworkInfo, leaderPubKey, shardId,
                             timestamp, committeeHash);
}

CoSignatures GenerateRandomCoSignatures() { return CoSignatures(Dist1to99()); }

DS_Comitte_t GenerateRandomDSCommittee(uint32_t size){
  DS_Comitte_t ds_c;
  for (uint32_t i = 1; i <= size; i++){
    ds_c.push_front(std::make_pair(GenerateRandomPubKey(), Peer()));
  }
  return ds_c;
}

Shard generateRandomShard(size_t size){
  Shard s;
  for (size_t i = 1; i <= size; i++)
    s.push_back(std::make_tuple(GenerateRandomPubKey(PrivKey()), GenerateRandomPeer(), DistUint16()));
  return s;
}

DequeOfShard generateDequeueOfShard(size_t size){
  DequeOfShard dos;
  for (size_t i = 1; i <= size; i++)
    dos.push_front(generateRandomShard(i));
  return dos;
}


}  // namespace TestUtils
