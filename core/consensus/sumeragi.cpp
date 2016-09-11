#include "sumeragi.hpp"

#include "../util/logger.hpp"
#include "../domain/entityRepository.hpp"
#include "../domain/transaction.hpp"
#include "../peer/connection.hpp" // TODO: rather than this low-level interface, abstract out events and broadcasts
#include "../crypto/hash.hpp"
#include "../validation/transactionValidator.hpp"

/**
* |ーーー|　|ーーー|　|ーーー|　|ーーー|
* |　ス　|ー|　メ　|ー|　ラ　|ー|　ギ　|
* |ーーー|　|ーーー|　|ーーー|　|ーーー|
*
* A chain-based byzantine fault tolerant consensus algorithm, based in large part on BChain: 
*
* Duan, S., Meling, H., Peisert, S., & Zhang, H. (2014). Bchain: Byzantine replication with 
* high throughput and embedded reconfiguration. In International Conference on Principles of 
* Distributed Systems (pp. 91-106). Springer.
*/
namespace sumeragi {

struct Context {
    int numberOfPeers;  // peerの数 // TODO: get this from membership service
    int maxFaulty;  // f
    std::string name;  // name Options
    bool isLeader;
    // bool isPanic;
    int myPeerNumber;
    std::string leaderNumber;
    int timeCounter;
    int peerCounter;
    std::unique_ptr<TransactionRepository> repository;
    std::unique_ptr<TransactionCache> txCache;
    std::unique_ptr<TransactionValidator> txValidator;
};

void initializeSumeragi(int const myNumber, int const numberOfPeers, int const leaderNumber, int const batchSize) {
    logger("initialize_sumeragi, my number:"+std::to_string(myNumber)+" leader:"+std::to_string(myNumber == leaderNumber)+"");
    // context->batchSize = batchSize;
    // context->myPeerNumber = myNumber;
    // context->numberOfPeers = numberOfPeers; // TODO(M→I): C++として、このsyntaxは大丈夫？
    // context->maxFaulty = numberOfPeers/3;  // Default to approx. 1/3 of the network. TODO(M→M): make this configurable 
    // context->validatingPeers;
    // context->isLeader = myNumber == leaderNumber;
    // context->leaderNumber = std::to_string(leaderNumber);
    // context->timeCounter = 0;
    // context->peerCounter = 0;
    context->txRepository = std::make_unique<TransactionRepository>();

    buffer = "";
}

void loopLeader(td::shared_ptr<std::string> const tx) {
    txValidator::isValid(tx);

    seq++;

    context->processingOrder = ::determineProcessingOrder();
    ::prepareTransaction();
    
    tx::addSignature();
    peerConnection::broadcastToNextValidator(tx);
    setAwkTimer(5000, [&]{ reconfigure(); };);
}

/**
* Move the suspected validator to the end of the chain and the suspector to the 2f+1'th position.
* 
* For example, given:
* |---|  |---|  |---|  |---|  |---|  |---|
* | H |--| 1 |--| 2 |--| 3 |--| 4 |--| 5 |
* |---|  |---|  |---|  |---|  |---|  |---|,
*
* if [2] suspects [3] and f := 2, then the validation chain order will become:
* |---|  |---|  |---|  |---|  |---|  |---|
* | H |--| 1 |--| 4 |--| 5 |--| 2 |--| 3 |
* |---|  |---|  |---|  |---|  |---|  |---|.
*
* Only the head (H) can reconfigure the chain order. If the head has a problem, other nodes should 
* request a view change.
*/
void reconfigureSuspects(int const suspected, int const suspector) {
//TODO:
}

void reconfigure() {
    // Any suspects?
    getSuspects();
    reconfigureSuspects();

    // If no suspects, kick the second node to the end of the chain
}

void setAwkTimer(int const sleepMillisecs, std::function<void(void)> action, actionArgs ...) {
    std::thread([sleepMillisecs, tx]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMillisecs));
        action();
    }).detach();
}

void checkForAwk(tx) {
    if (!context->repository->txHashFinalized(tx)) {
        // Panic
    }
}

void loopMember(td::shared_ptr<Transaction> const tx, int const currLeader) { //TODO(M->I): I want to use const like final in Java. Is this good practice and/or correct?
    if (tx::isChain()) {
        context->txValidator::isValid(tx);
        tx::addSignature();
        peerConnection::broadcastNext(tx);  // Broadcast to the next validator in the chain
        setAwkTimer(5000);

    } else if (tx::isAwk()) {


    } else if (tx::isSuspect()) {


    } else if (tx::isViewChange()) {

    }
}

void loopProxyTail(td::shared_ptr<std::string> const tx, int const currLeader) {
    if (tx::isChain()) {
        context->txValidator::isValid(tx);
        tx::addSignature();
        peerConnection::broadcastFinalizedAll(tx);

    } else if (tx::isPanic()) {
        if (panicMessages.length >= context->maxFaulty) {
            peerConnection::broadcastPanicAll();
        }
    }
}

void loop() {
    logger("start loop");
    // int count = 0;
    while (true) {  // TODO(M->M): replace with callback linking aeron
        if (context->eventCache::hasConsensusEvent()) { // TODO: make event cache (std::map in memory is fine)
            std::shared_ptr<ConsensusEvent> const event = context->eventCache::popConsensusEvent();

            if (ConsensusEvent.types.transaction == event->type) {

            } else if (ConsensusEvent.types.awk == event->type) {

            } else if (ConsensusEvent.types.suspicion == event->type) {

            } else if (ConsensusEvent.types.viewChange == event->type) {

            }

        //     if (txValidator::isValid()) { //TODO: write validation code (check signatures and account balances, if applicable)
        //         // context->timeCounter++;

        //         int const currLeader = context->numberOfPeers;
        //         if (tx->hash % context->numberOfPeers == context->myPeerNumber) {
        //             loopLeader(tx);
        //         } else {
        //             loopMember(tx, txContext);
        //         }
        //     }
        // }

        // if (context->panicCache::hasAwk()) {
        //     std::shared_ptr<Panic> const panic = context->repository->popPanic();

        //     peerConnection::broadcastUpchain(panic);
        // }

        // if (context->panicCache::hasPanic()) {
        //     std::shared_ptr<Panic> const panic = context->repository->popPanic();

        //     peerConnection::broadcastUpchain(panic);
        // }
    }
}

};  // namespace sumeragi