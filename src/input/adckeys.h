#ifndef _ADC_KEY_H_
#define _ADC_KEY_H_

class AdcKeys
{
public:
    AdcKeys(int adcPin);
    ~AdcKeys();

    int getPinNum(); // 获取当前按键 < 0 当前无按键按下

private:
    int adcPin;
    int delaytime;
};



#endif
