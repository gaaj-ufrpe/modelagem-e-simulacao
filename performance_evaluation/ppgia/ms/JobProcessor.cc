#include "JobProcessor.h"

namespace ms {

JobProcessor::~JobProcessor() {
    if (processing) {
        delete processing;
    }
    cancelAndDelete(finishJob);
}

void JobProcessor::initialize() {
    queueLengthSignal = registerSignal("queueLength");
    droppedSignal = registerSignal("dropped");
    busySignal = registerSignal("busy");
    emit(queueLengthSignal, 0);
    emit(busySignal, 0);

    delay = par("delay");
    int queueCapacity = par("queueCapacity");
    queue = JobQueue(queueCapacity);
    processing = nullptr;
    finishJob = new Job("finish");
}

void JobProcessor::handleMessage(cMessage *msg) {
    if (msg == finishJob) {
        finishProcessing();
        emit(busySignal, 0);
    } else {
        Job *job = check_and_cast<Job*>(msg);
        handleExternalJob(job);
    }
}

void JobProcessor::handleExternalJob(Job *job) {
    if (processing) {
        bool result = queue.enqueue(job);
        emit(droppedSignal, result ? 0 : 1);
    } else {
        emit(droppedSignal, 0);
        processing = job;
        startProcessing();
    }
    emit(queueLengthSignal, queue.getLength());
}

void JobProcessor::startProcessing() {
    EV << "Processing \"" << processing->getFullName() << "\"." << endl;
    simtime_t st = serviceTime(processing);
    scheduleAt(simTime()+st, finishJob);
    emit(busySignal, 1);
}

simtime_t JobProcessor::serviceTime(Job *job) {
    return exponential(delay);
}

void JobProcessor::finishProcessing() {
    EV << "Processed \"" << processing->getFullName() << "\"." << endl;
    process(processing);
    processing = queue.dequeue();
    if (processing != nullptr) {
        startProcessing();
    }
}

void JobProcessor::process(Job *job) {}

};//namespace

