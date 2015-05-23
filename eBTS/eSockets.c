#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>

#include "eSockets.h"
#include "eBTS.h"
#include "eL1.h"
#include "eMessages.h"

#include <osmocom/core/gsmtap_util.h>
#include <osmocom/core/gsmtap.h>
#include <osmocom/gsm/protocol/gsm_04_08.h>

/**************** Create Sockets *****************/

int OpenClockSocket()
{
    struct sockaddr_in si_clock, si_other_clock;
    int clock_fd, i, slen = sizeof(si_other_clock) , recv_len;
    char buf[BUFLEN];
       
    if ((clock_fd=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        printf("socket\n");
    }
      
    memset((char *) &si_clock, 0, sizeof(si_clock));
     
    si_clock.sin_family = AF_INET;
    si_clock.sin_port = htons(CLK_DST_PORT);
    si_clock.sin_addr.s_addr = inet_addr(LOCAL_HOST);
     
    
    if( bind(clock_fd , (struct sockaddr*)&si_clock, sizeof(si_clock) ) == -1)
    {
        printf("Clock bind error\n");
    }  
    
    printf("Bind to clock  port: %d  successful.\n", CLK_DST_PORT);
    return clock_fd;   
}

int OpenControlSocket()
{
    struct sockaddr_in si_control, si_other_control;
    int ctrl_fd, i, slen = sizeof(si_other_control) , recv_len;
    char buf[BUFLEN];
     
    if ((ctrl_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("socket\n");
    }

    memset((char *) &si_control, 0, sizeof(si_control));
     
    si_control.sin_family = AF_INET;
    si_control.sin_port = htons(CTR_DST_PORT);
    si_control.sin_addr.s_addr = inet_addr(LOCAL_HOST);
     
    if( bind(ctrl_fd , (struct sockaddr*)&si_control, sizeof(si_control) ) == -1)
    {
        printf("Control bind error\n");
    }
   
    printf("Bind to ctrl   port: %d  successful.\n", CTR_DST_PORT);
    return ctrl_fd;  
}

int OpenDataSocket()
{
    struct sockaddr_in si_data, si_data_other;
    int data_fd, i, slen = sizeof(si_data_other) , recv_len;
    char buf[DATA_BUFFER];

    if ((data_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("socket\n");
    }

    memset((char *) &si_data, 0, sizeof(si_data));
     
    si_data.sin_family = AF_INET;
    si_data.sin_port = htons(DATA_DST_PORT);
    si_data.sin_addr.s_addr = inet_addr(LOCAL_HOST);
     
    if( bind(data_fd , (struct sockaddr*)&si_data, sizeof(si_data) ) == -1)
    {
        printf("Data bind error\n");
    }
   
    printf("Bind to data   port: %d  successful.\n", DATA_DST_PORT);
    return data_fd; 
}

int OpenInovaSocket()
{
    struct sockaddr_in si_control, si_other_control;
    int inova_fd, i, slen = sizeof(si_other_control) , recv_len;
    char buf[BUFLEN];
     
    if ((inova_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("socket\n");
    }

    memset((char *) &si_control, 0, sizeof(si_control));
     
    si_control.sin_family = AF_INET;
    si_control.sin_port = htons(INOVA_DST_PORT);
    si_control.sin_addr.s_addr = inet_addr(LOCAL_HOST);
     
    if( bind(inova_fd , (struct sockaddr*)&si_control, sizeof(si_control) ) == -1)
    {
        printf("Inova bind error\n");
    }
   
    printf("Bind to inova  port: %d successful.\n", INOVA_DST_PORT);
    return inova_fd;  
}

int OpenGSMTAPSocket()
{
    struct sockaddr_in si_gsmtap, si_gsmtap_other;
    int gsmtap_fd, i, slen = sizeof(si_gsmtap_other) , recv_len;
    char buf[DATA_BUFFER];

    if ((gsmtap_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("socket\n");
    }

    memset((char *) &si_gsmtap, 0, sizeof(si_gsmtap));
     
    si_gsmtap.sin_family = AF_INET;
    si_gsmtap.sin_port = htons(GSMTAP_DST_PORT);
    si_gsmtap.sin_addr.s_addr = inet_addr(LOCAL_HOST);
     
    if( bind(gsmtap_fd , (struct sockaddr*)&si_gsmtap, sizeof(si_gsmtap) ) == -1)
    {
        printf("GSMTAP bind error\n");
    }
   
    printf("Bind to GSMTAP port: %d  successful.\n", GSMTAP_DST_PORT);
    return gsmtap_fd; 
}

int OpenMobileSocket()
{
    struct sockaddr_in si_mobile, si_mobile_other;
    int mobile_fd, i, slen = sizeof(si_mobile_other) , recv_len;
    char buf[DATA_BUFFER];

    if ((mobile_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("socket\n");
    }

    memset((char *) &si_mobile, 0, sizeof(si_mobile));
     
    si_mobile.sin_family = AF_INET;
    si_mobile.sin_port = htons(MOBILE_SRC_PORT);
    si_mobile.sin_addr.s_addr = inet_addr(LOCAL_HOST);
     
    if( bind(mobile_fd , (struct sockaddr*)&si_mobile, sizeof(si_mobile) ) == -1)
    {
        printf("Mobile bind error\n");
    }
   
    printf("Bind to mobile port: %d  successful.\n", MOBILE_SRC_PORT);
    return mobile_fd;
    
}

/**************** Receive from Sockets *****************/

int ReceiveFromClockSocket(int clock_fd)
{
    struct sockaddr_in si_clock, si_other_clock;
    int s, i, slen = sizeof(si_other_clock) , recv_len;
    char buf[BUFLEN];

    memset((char *) &si_clock, 0, sizeof(si_clock));
     
    si_clock.sin_family = AF_INET;
    si_clock.sin_port = htons(CLK_DST_PORT);
    si_clock.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    
    if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other_clock, &slen)) == -1)
        {
            printf("recvfrom()\n");
        }
    
    printf("Received packet from %s:%d .\n", inet_ntoa(si_other_clock.sin_addr), ntohs(si_other_clock.sin_port));
    printf("Data: %s .\n" , buf);   
    return 0;
}

int ReceiveFromControlSocket(int ctrl_fd)
{
    struct sockaddr_in si_control, si_other_control;
    int i, slen = sizeof(si_other_control) , recv_len;
    char CtrlCmd[BUFLEN]; 

    memset((char *) &si_control, 0, sizeof(si_control));
     
    si_control.sin_family = AF_INET;
    si_control.sin_port = htons(CTR_DST_PORT);
    si_control.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    
    if ((recv_len = recvfrom(ctrl_fd, CtrlCmd, BUFLEN, 0, (struct sockaddr *) &si_other_control, &slen)) == -1)
        {
            printf("recvfrom()");
        }
  
    printf("Received packet with data: %s , from %s:%d .\n", CtrlCmd, inet_ntoa(si_other_control.sin_addr), ntohs(si_other_control.sin_port));   
    CompareControlCommand(&CtrlCmd, ctrl_fd);     
    return 0;
}

int ReceiveFromDataSocket(int data_fd)
{
    struct sockaddr_in si_data, si_other_data;
    struct l1 *l1msg=malloc(sizeof(struct l1));
    int i, slen = sizeof(si_other_data), recv_len;
    //struct gsm48_system_information_type3 *si3=malloc(sizeof(struct gsm48_system_information_type3));
    uint8_t Data[256];
    /*
    ;
    uint8_t tn;
    int8_t rssi;
    float toa;
    uint32_t fn;
    sbit_t bits[148];
    */
    memset((char *) &si_data, 0, sizeof(si_data));
     
    si_data.sin_family = AF_INET;
    si_data.sin_port = htons(DATA_SRC_PORT);
    si_data.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    
    if ((recv_len = recvfrom(data_fd, Data, DATA_BUFFER, 0, (struct sockaddr *) &si_other_data, &slen)) == -1)
        {
            printf("recvfrom()");
        }
    
    l1msg->tn = Data[0];
    l1msg->fn = (Data[1] << 24) | (Data[2] << 16) | (Data[3] << 8) | Data[4];
    l1msg->rssi = -(int8_t)Data[5];
    l1msg->toa = ((int16_t)(Data[6] << 8) | Data[7]) / 256.0F;

    //copy and convert bits {254..0} to sbits {-127..127} 
    for (i = 0; i < 148; i++) {
    if (Data[8 + i] == 255)
		l1msg->bits[i] = -127;
        	else
		l1msg->bits[i] = 127 - Data[8 + i];
	}

    if (l1msg->tn >= 8) {
	printf("Illegal TS %d\n", l1msg->tn);
    }
    if (l1msg->fn >= 2715648) {
    	printf("Illegal FN %u\n", l1msg->fn);
    }

    printf("RX burst tn=%u fn=%u rssi=%d toa=%.2f\n", l1msg->tn, l1msg->fn, l1msg->rssi, l1msg->toa);
    
    //si3=l1msg->bits
    printf("BITS=%d\n", l1msg->bits);
    
    

    return 0;
}

int ReceiveFromInovaSocket(int inova_fd)
{
    struct sockaddr_in si_control, si_other_control;
    int i, slen = sizeof(si_other_control) , recv_len;
    char InovaCmd[BUFLEN];

    memset((char *) &si_control, 0, sizeof(si_control));
     
    si_control.sin_family = AF_INET;
    si_control.sin_port = htons(INOVA_DST_PORT);
    si_control.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    
    if ((recv_len = recvfrom(inova_fd, InovaCmd, BUFLEN, 0, (struct sockaddr *) &si_other_control, &slen)) == -1)
        {
            printf("recvfrom()");
        }
  
    printf("Received packet with data: %s , from %s:%d .\n", InovaCmd, inet_ntoa(si_other_control.sin_addr), ntohs(si_other_control.sin_port)); 
    return 0;
}

int ReceiveFromGSMTAPSocket(int gsmtap_fd, int mobile_fd, int data_fd)
{
    struct sockaddr_in si_gsmtap, si_other_gsmtap;
    int s, size, i, slen = sizeof(si_other_gsmtap) , recv_len;
    char recv_buf[1500];
    
    memset((char *) &si_gsmtap, 0, sizeof(si_gsmtap));
     
    si_gsmtap.sin_family = AF_INET;
    si_gsmtap.sin_port = htons(GSMTAP_SRC_PORT);
    si_gsmtap.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    
    if ((recv_len = recvfrom(gsmtap_fd, recv_buf, sizeof(recv_buf) , 0, (struct sockaddr *) &si_other_gsmtap, &slen)) == -1)
        {
            printf("recvfrom()\n");
        }
    //SendToMobileSocket(mobile_fd, recv_buf, recv_len);
    HandleReceivedMobileMessage(mobile_fd, recv_buf, recv_len);
    
    return 0;
}

int ReceiveFromMobileSocket(int mobile_fd, int data_fd)
{
    struct gsmtap_hdr *gsmtap_msg= malloc(sizeof(struct gsmtap_hdr));
    struct sockaddr_in si_mobile, si_other_mobile;
    int i, size, slen = sizeof(si_other_mobile) , recv_len;
    ubit_t *bits;
    char recv_buf[BUFLEN];

    memset((char *) &si_mobile, 0, sizeof(si_mobile));
     
    si_mobile.sin_family = AF_INET;
    si_mobile.sin_port = htons(MOBILE_SRC_PORT);
    si_mobile.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    
    if ((recv_len = recvfrom(mobile_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *) &si_other_mobile, &slen)) == -1)
        {
            printf("Failed recvfrom() mobile socket\n");
        }
    printf("Received packet from %s:%d .\n", inet_ntoa(si_other_mobile.sin_addr), ntohs(si_other_mobile.sin_port));
    
    bits = malloc(recv_len-sizeof(struct gsmtap_hdr));
    memcpy(gsmtap_msg, recv_buf, sizeof(struct gsmtap_hdr));
    memcpy(bits, recv_buf+sizeof(struct gsmtap_hdr), recv_len-sizeof(struct gsmtap_hdr));
    HandleReceivedMobileMessage(gsmtap_msg, bits, data_fd);
    return 0; 
}

/**************** Send to Sockets *****************/

int SendToClockSocket(int ClkCmd,  int clock_fd)
{
    struct sockaddr_in si_clock, si_other_clock;
    int i, slen = sizeof(si_other_clock) , recv_len;
    
    memset((char *) &si_clock, 0, sizeof(si_clock));
       
    si_clock.sin_family = AF_INET;
    si_clock.sin_port = htons(CLK_SRC_PORT);
    si_clock.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    
    if (sendto(clock_fd, ClkCmd, BUFLEN , 0, (struct sockaddr*) &si_clock, slen) == -1)
        {
            printf("sendto()");
        } 
    
    printf("Sending clocks: %s to clock port.\n", ClkCmd);
    return 0;
}

int SendToControlSocket(int CtrlCmdResp,  int ctrl_fd)
{
    struct sockaddr_in si_control, si_other_control;
    int i, slen = sizeof(si_other_control) , recv_len;

    memset((char *) &si_control, 0, sizeof(si_control));
     
    si_control.sin_family = AF_INET;
    si_control.sin_port = htons(CTR_SRC_PORT);
    si_control.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    printf("CTRL buffer: %s\n", CtrlCmdResp);
    
    if (sendto(ctrl_fd, CtrlCmdResp, BUFLEN, 0, (struct sockaddr*) &si_control, slen) == -1)
        {
            printf("sendto()\n");
        }
    
    return 0;
}

int SendToDataSocket(struct gsmtap_hdr *gsmtap_rach, int data_fd, int size)
{
    struct sockaddr_in si_data, si_other_data;
    int slen = sizeof(si_other_data);

    memset((char *) &si_data, 0, sizeof(si_data));
     
    si_data.sin_family = AF_INET;
    si_data.sin_port = htons(MOBILE_SRC_PORT);
    si_data.sin_addr.s_addr = inet_addr(LOCAL_HOST);

    printf("Sending data to Data port");
    
    if (sendto(data_fd, gsmtap_rach, size, 0, (struct sockaddr*) &si_data, slen) == -1)
        {
            printf("sendto()");
        } 
    return 0; 
}

int SendToMobileSocket(int mobile_fd, unsigned char *buf, int size)
{
    struct sockaddr_in si_data, si_other_data;
    int i, slen = sizeof(si_other_data), recv_len;
  
    //clear structure
    memset((char *) &si_data, 0, sizeof(si_data));
     
    si_data.sin_family = AF_INET;
    si_data.sin_port = htons(MOBILE_DST_PORT);
    si_data.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    
    if (sendto(mobile_fd, buf, size, 0, (struct sockaddr*) &si_data, slen) == -1)
        {
            printf("sendto()");
        }
    
    return 0; 
}
