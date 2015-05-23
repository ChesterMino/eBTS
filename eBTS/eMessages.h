/* 
 * File:   eMessages.h
 * Author: dp
 *
 * Created on April 5, 2015, 4:16 AM
 */

#ifndef EMESSAGES_H
#define	EMESSAGES_H


struct recv_gsmtap_msg{
    char message[1500];
    int size;
};

struct l1{
    uint8_t tn;
    int8_t rssi;
    float toa;
    uint32_t fn;
    int8_t bits[148];
};


int clock_fd;
int ctrl_fd;
int data_fd;
int pcu_fd;
int mobile_fd;
int inova_fd;
int gsmtap_fd;
char message;

//char * CtrlCmd;

int SendClockCommand(int clock_fd);
void CompareClockCommand (const char *ClkCmd);
int CompareControlCommand(int CtrlCmd, int ctrl_fd);


#endif	/* EMESSAGES_H */

