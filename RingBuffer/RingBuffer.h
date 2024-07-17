#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <thread>
#include <fstream>
#include <string>

using std::string;

class Data {
public:
    std::shared_ptr<int> mData;
    int frameIndex;
    // int type;
    // long timestamp;
public:    
    bool canDrop();
    Data(std::shared_ptr<int> d,int index);
    void kill();
 
private:
    bool isKeyFrame();
};

class RingBuffer {
public:
    RingBuffer();
    ~RingBuffer();

public:
    int size();
    bool empty();
    void push(std::shared_ptr<Data> data);
    void pop();
    std::shared_ptr<Data> front();

private:
    static const int MAX_QUEUE_NUM = 32;
    std::shared_ptr<Data> m_data[MAX_QUEUE_NUM];
    int m_front;
    int m_rear;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};
#endif
