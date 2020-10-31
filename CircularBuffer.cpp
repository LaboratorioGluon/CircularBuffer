#if 0
#include "CircularBuffer.h"
#include <stdlib.h>

template<class T>
CircularBuffer<T>::CircularBuffer(uint8_t pBufferSize){

    mBufferSize = pBufferSize*sizeof(T);
    mBuffer = malloc(mBufferSize);

    memset(mBuffer,0, mBufferSize);

    isFull = false;
    isEmpty = true;

    pRead = mBuffer;
    pWrite = mBuffer;
}

template<class T>
CIRCULAR_BUFFER_STATUS CircularBuffer<T>::Read(T *out){

    if(isEmpty())
        return CIRCULAR_BUFFER_EMPTY;

    *out = *pRead;

    // Si hemos leido uno ya no está lleno
    mIsFull = false;
    
    IncrementRead();

}

template<class T>
CIRCULAR_BUFFER_STATUS CircularBuffer<T>::Write(T data){

    if(isFull()){
        return CIRCULAR_BUFFER_FULL;
    }

    mIsEmpty = false;

    *pWrite = data;

    IncrementWrite();

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
    if(pRead == mBuffer + mBufferSize){
            pRead = mBuffer;
    }else{
            pRead++;
    }

    if (pRead == pWrite){
        isEmpty = true;
    }

    return CIRCULAR_BUFFER_OK;

}

template<class T>
CIRCULAR_BUFFER_STATUS CircularBuffer<T>::IncrementWrite(){

    if(pWrite == mBuffer + mBufferSize){
         pWrite = mBuffer;
    }else{
         pWrite++;
    }

    if (pRead == pWrite){
        isFull = true;
    }

    return CIRCULAR_BUFFER_OK;
}


#endif