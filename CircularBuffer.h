#ifndef __CIRCULARBUFFER_H__
#define __CIRCULARBUFFER_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum CIRCULAR_BUFFER_STATUS{
    CIRCULAR_BUFFER_ERROR = 0,
    CIRCULAR_BUFFER_OK,
    CIRCULAR_BUFFER_EMPTY,
    CIRCULAR_BUFFER_FULL
};

template<class T>
class CircularBuffer{
public:
    CircularBuffer(uint8_t pBufferSize);

    void Init();

    CIRCULAR_BUFFER_STATUS Read(T *out);

    CIRCULAR_BUFFER_STATUS Write(T data);

    uint16_t Available();

    //CIRCULAR_BUFFER_STATUS Write(T *data, uint32_t len);

    bool isFull(){ return mIsFull; }
    bool isEmpty(){ return mIsEmpty; }

    
private:

    T *mBuffer;
    uint32_t mBufferSize;

    T *pWrite, *pRead;
    
    bool mIsFull, mIsEmpty;

    uint16_t count;


    CIRCULAR_BUFFER_STATUS IncrementRead();
    CIRCULAR_BUFFER_STATUS IncrementWrite();


};


template<class T>
CircularBuffer<T>::CircularBuffer(uint8_t pBufferSize){

    mBufferSize = pBufferSize*sizeof(T);
    mBuffer = (T*)malloc(mBufferSize);

    memset(mBuffer,0, mBufferSize);

    mIsFull = false;
    mIsEmpty = true;

    pRead = mBuffer;
    pWrite = mBuffer;

    count = 0;
}

template<class T>
void CircularBuffer<T>::Init(){

}

template<class T>
uint16_t CircularBuffer<T>::Available(){
    return count;
}

template<class T>
CIRCULAR_BUFFER_STATUS CircularBuffer<T>::Read(T *out){

    if(isEmpty())
        return CIRCULAR_BUFFER_EMPTY;

    *out = *pRead;

    // Si hemos leido uno ya no está lleno
    mIsFull = false;
    
    return IncrementRead();

}

template<class T>
CIRCULAR_BUFFER_STATUS CircularBuffer<T>::Write(T data){

    if(isFull()){
        return CIRCULAR_BUFFER_FULL;
    }

    mIsEmpty = false;

    *pWrite = data;

    return IncrementWrite();
}

/*
template<class T>
CIRCULAR_BUFFER_STATUS CircularBuffer<T>::Write(T *data, uint32_t len){

    if(pCb->isFull){
        return BUFFER_FULL;
    }

    pCb->isEmpty = false;

    *(pCb->pWrite) = data;

    IncrementWrite(pCb);

}*/

template<class T>
CIRCULAR_BUFFER_STATUS CircularBuffer<T>::IncrementRead(){
    count--;
    if(pRead == mBuffer + mBufferSize){
            pRead = mBuffer;
    }else{
            pRead++;
    }

    if (pRead == pWrite){
        mIsEmpty = true;
    }

    return CIRCULAR_BUFFER_OK;

}

template<class T>
CIRCULAR_BUFFER_STATUS CircularBuffer<T>::IncrementWrite(){

    count++;

    if(pWrite == mBuffer + mBufferSize){
         pWrite = mBuffer;
    }else{
         pWrite++;
         
    }

    if (pRead == pWrite){
        mIsFull = true;
    }

    return CIRCULAR_BUFFER_OK;
}


#endif //__CIRCULARBUFFER_H__