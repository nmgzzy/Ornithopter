#include "BLE.h"
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define COM_LEN 10 //7+3

BluetoothSerial SerialBT;
uint8_t buf[COM_LEN];
uint8_t buf_cnt = 0;
int sum = 0;
int8_t chjoy[4];
uint8_t flag_r = 1;
int debug_datai[4] = {0};
float debug_dataf[4] = {0};

void BLEsetup(){
  SerialBT.begin("ESP32test");
}

void BLEloop(){
    while (SerialBT.available()) {
        int a = SerialBT.read();
        if( a < 0 ) {
            break;
        }
        buf[buf_cnt] = 0xff & a;
        if (buf_cnt==0 && buf[buf_cnt]!=0xa5)
        {
            buf_cnt=0;
            continue;
        }
        if (buf_cnt == (COM_LEN-1) && buf[buf_cnt]==0x5a)
        {
            for(uint8_t i=0; i<4; i++) {
                chjoy[i] = buf[i+1];
            }
            flag_r = buf[5];
            if((int8_t)buf[6] < 33 && SystemMode == 1 && channels[5] < 90) {
                SystemMode = 0;
            }
            else if((int8_t)buf[6] < 66 && (SystemMode == 0 || SystemMode == 1) && channels[5] < 90) {
                SystemMode = 1;
            }
            else if((int8_t)buf[6] < 100 && SystemMode == 1 && channels[5] < 90) {
                SystemMode = 2;
            }
            if (buf[7]==1) {
                ESP.restart();
            }
        }
        buf_cnt++;
        if (buf_cnt >= COM_LEN)
        {
            buf_cnt = 0;
        }
    }
    if(count % 4 == 0) {
        uint8_t sum = 0;
        uint8_t* pi = (uint8_t*)debug_datai;
        uint8_t* pf = (uint8_t*)debug_dataf;
        for(uint8_t i = 0; i < 16; i++) {
            sum+= pi[i] + pf[i];
        }
        SerialBT.write(0xA5);
        SerialBT.write(pi,16);
        SerialBT.write(pf,16);
        SerialBT.write(sum);
        SerialBT.write(0x5A);
    }
}
