#include "priority_queue.h"

void initPQ(PriorityQueue *pq) {
    pq->size = 4;
    pq->arr[0] = (LaneNode){'A', 1};
    pq->arr[1] = (LaneNode){'B', 1};
    pq->arr[2] = (LaneNode){'C', 1};
    pq->arr[3] = (LaneNode){'D', 1};
}

void updatePriority(PriorityQueue *pq, char lane, int priority) {
    for (int i = 0; i < 4; i++) {
        if (pq->arr[i].lane == lane) {
            pq->arr[i].priority = priority;
        }
    }
}

char getNextLane(PriorityQueue *pq) {
    int best = 999;
    char result = 'A';

    for (int i = 0; i < pq->size; i++) {
        if (pq->arr[i].priority < best) {
            best = pq->arr[i].priority;
            result = pq->arr[i].lane;
        }
    }
    return result;
}
