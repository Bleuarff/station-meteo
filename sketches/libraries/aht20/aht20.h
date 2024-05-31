/*
  Interacts with AHT20 temperature & humidity sensor
*/

#ifndef aht20_h
#define aht20_h

class AHT20 {
  private:
    static const uint8_t I2C_ADDR = 0x38;
    static const uint8_t STATUS_OK = 0x18;
  public:
    AHT20();
    bool isReady;
    void begin();
    void getValues(float *temp, float *humid);
};

#endif