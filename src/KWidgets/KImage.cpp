#include "KImage.h"

KImage::KImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    KWidget(x, y, w, h),
    imageDataPtr(0)
{

}

KImage::~KImage()
{

}

void KImage::setImage(uint8_t* imageDataPtr, bool isInFlash)
{
    this->imageDataPtr = imageDataPtr;
    this->isInFlash = isInFlash;
}

void KImage::paint()
{
    if(!imageDataPtr) 
        return;

    if(isInFlash) {
        showPictureInFlash(x, y, w, h, imageDataPtr);
    } else {
        showPicture(x, y, w, h, imageDataPtr);
    }
}