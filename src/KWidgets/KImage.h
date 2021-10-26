#ifndef _K_IMAGE_H_
#define _K_IMAGE_H_
#include "KWidget.h"

class KImage : public KWidget
{
public:
    KImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    ~KImage();

    /**
     * 取模软件：PCToLCD
     * 取模方式：列行式
     */
    void setImage(uint8_t* imageDataPtr, bool isInFlash);
protected:
    void paint();

private:
    uint8_t* imageDataPtr;
    bool isInFlash;
};

#endif