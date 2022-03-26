#ifndef __MYWIFI_H__
#define __MYWIFI_H__

#include "config.h"

#define DEBUGCHANNLE 16

extern float debugData[DEBUGCHANNLE];

enum dataCh_par_e {
    //todo = 1
    //pid
    //bat
    //rssi
    //
    CN_NUM_PAR

};

enum dataCh_pose_e {
    CH_W = 1,
    CH_X,
    CH_Y,
    CH_Z,
    CH_ACCX,
    CH_ACCY,
    CH_ACCZ,
    CH_GYRX,
    CH_GYRY,
    CH_GYRZ,

    CN_NUM_POSE
};

enum dataCh_data_e {
    
    //todo = 1,

    CN_NUM_DATA
};

enum sendMode_e {
    MODE_NONE = 0,
    MODE_DATA,
    MODE_PAR,
    MODE_POSE,
};

union par_u {
    int par_i;
    float par_f;
};

struct pair_s {
    String name;
    par_u data;
};

extern uint8_t sendMode;

void tcpSetup();
void tcpSendData();
int  tcpReceiveData();
void udpSetup();
void udpSendData();
int  udpReceiveData();

#endif