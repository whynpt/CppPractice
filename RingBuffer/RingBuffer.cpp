#include "RingBuffer.h"

#define BUFFER_PRINT_LEN 10

// const char sKeyFrameTag[FRAME_TAG_LEN+1] = {0x00,0x00,0x00,0x01,0x41,0x06};

string bufToHexStr(char *pBuf, int bufLen)
{
    if(NULL == pBuf || bufLen < 0)
    {
        return "";
    }
    int i = 0;
    string sRet = "";
    for(i = 0; i < bufLen; i++)
    {
        char szTmp[3] = {0};
        sprintf(szTmp, "%02x", (unsigned char)pBuf[i]);
        sRet += szTmp;
    }

    return sRet;
}

// long getCurrentTime() {  
//     struct timeval tv;  
//     gettimeofday(&tv,NULL);  
//     return tv.tv_sec * 1000 + tv.tv_usec / 1000;  
// } 

// bool Data::canDrop() {
//     long curTick = getCurrentTime();
//     return ((curTick - timestamp > DELAY_THREHOLD_MS) && (type != TYPE_IFRAME));
// }

Data::Data(std::shared_ptr<int> b,int index) {
    // mData = ABuffer::CreateAsCopy(b->data(), b->size());
    mData = b;
    frameIndex = index;
    // type = isKeyFrame()?TYPE_IFRAME:TYPE_PFRAME;
    // timestamp = getCurrentTime();
    // printf("CirCularQueue Data() keyFrame=%d,frameIndex=%d,tick=%ld,mData=%s",(type==TYPE_IFRAME),frameIndex,timestamp,
    //        bufToHexStr((char*)mData->data(),mData->size()<BUFFER_PRINT_LEN?mData->size():BUFFER_PRINT_LEN).c_str());
}

// bool Data::isKeyFrame() {
    // if (mData->size() < FRAME_TAG_LEN) {
    //     return false;
    // }
    // for (size_t i = 0; i < FRAME_TAG_LEN - 1; i++) {
    //     if (mData->data()[i] != sKeyFrameTag[i]) {
    //         return false;
    //     }
    // }
    // if (mData->data()[FRAME_TAG_LEN - 1] == sKeyFrameTag[FRAME_TAG_LEN - 1] ||
    //     mData->data()[FRAME_TAG_LEN - 1] == sKeyFrameTag[FRAME_TAG_LEN]) {
    //         return true;
    // }
//     return false;
// } 

void Data::kill() {  
   
}

RingBuffer::RingBuffer(){
    m_front = 0;
    m_rear = 0;
    for (int i = 0; i < MAX_QUEUE_NUM; i++) {
        m_data[i] = NULL;
    }
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);
}


RingBuffer::~RingBuffer(){
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}


int RingBuffer::size(){
    if (m_rear < m_front) {
        return m_rear + MAX_QUEUE_NUM - m_front;
    } else {
        return m_rear - m_front;
    }
}


bool RingBuffer::empty(){
    return m_front == m_rear;
}

// insert data at m_rear
void RingBuffer::push(std::shared_ptr<Data> data){
        pthread_mutex_lock(&mutex);
        //printf("RingBuffer::push()+++ m_rear=%d,m_front=%d",m_rear,m_front);
        if (m_rear == m_front) {
            if (m_data[m_front] != NULL) {
                // printf("wrong: m_rear equals m_front, while not empty");
                //printf("RingBuffer::push() skip");
                m_rear = (m_rear + 1) % MAX_QUEUE_NUM;
            }
        }
        if (m_data[m_rear] != NULL) {
            // if (m_data[m_rear]->mData != NULL) {
            //     //free(m_data[m_rear]->mData);
            //     //m_data[m_rear]->mData = NULL;
            // }
            printf("wrong: m_rear is not null");
            m_data[m_rear] = NULL;
        }
        m_data[m_rear] = data;
        m_rear = (m_rear + 1) % MAX_QUEUE_NUM;
        //printf("RingBuffer::push()--- m_rear=%d,m_front=%d",m_rear,m_front);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
}


void RingBuffer::pop(){
    pthread_mutex_lock(&mutex);
    //printf("RingBuffer::pop()+++ m_rear=%d,m_front=%d",m_rear,m_front);
    if(empty()){
        //printf("RingBuffer::pop() empty!");
        pthread_cond_wait(&cond, &mutex);
    }
    m_data[m_front] = NULL;
    m_front = (m_front + 1) % MAX_QUEUE_NUM;
    //printf("RingBuffer::pop()--- m_rear=%d,m_front=%d",m_rear,m_front);
    pthread_mutex_unlock(&mutex);
}


std::shared_ptr<Data> RingBuffer::front() {
    pthread_mutex_lock(&mutex);
    if(empty()){
        pthread_cond_wait(&cond, & mutex);
    }
    std::shared_ptr<Data> pData = m_data[m_front];
    pthread_mutex_unlock(&mutex);
    return pData;
}