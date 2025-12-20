#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct {
    char lane;
    int priority;
} LaneNode;

typedef struct {
    LaneNode arr[4];
    int size;
} PriorityQueue;

void initPQ(PriorityQueue *pq);
void updatePriority(PriorityQueue *pq, char lane, int priority);
char getNextLane(PriorityQueue *pq);

#endif
