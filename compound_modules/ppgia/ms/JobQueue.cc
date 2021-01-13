#include "JobQueue.h"

namespace ms {

JobQueue::JobQueue() {
    this->capacity = -1;
}

JobQueue::JobQueue(int capacity) {
    this->capacity = capacity;
}

bool JobQueue::enqueue(Job *job) {
    bool result;
    if (capacity > 0 && this->getLength() == capacity) {
        EV << "Discarded \"" << job->getFullName() << "\"" << endl;
        delete job;
        return false;
    } else {
        EV << "Enqueued \"" << job->getFullName() << "\"" << endl;
        this->insert(job);
        return true;
    }
}

Job* JobQueue::dequeue() {
    Job* result = nullptr;
    if (!this->isEmpty()) {
        result = check_and_cast<Job*>(this->pop());
    }
    return result;
}
};//namespace

