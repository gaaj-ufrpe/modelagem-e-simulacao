#include "JobProcessor.h"

namespace ms {

JobProcessor::~JobProcessor() {
    if (processing) {
        delete processing;
    }
    cancelAndDelete(finishJob);
}

void JobProcessor::initialize() {
    delay = par("delay");
    int queueCapacity = par("queueCapacity");
    queue = JobQueue(queueCapacity);
    processing = nullptr;
    finishJob = new Job("finish");
}

void JobProcessor::handleMessage(cMessage *msg) {
    if (msg == finishJob) {
        finishProcessing();
    } else {
        Job *job = check_and_cast<Job*>(msg);
        handleExternalJob(job);
    }
}

void JobProcessor::handleExternalJob(Job *job) {
    if (processing) {
        queue.enqueue(job);
    } else {
        processing = job;
        startProcessing();
    }
}

void JobProcessor::startProcessing() {
    EV << "Processing \"" << processing->getFullName() << "\"." << endl;
    simtime_t st = serviceTime(processing);
    scheduleAt(simTime()+st, finishJob);

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

