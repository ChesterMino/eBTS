/* 
 * File:   sockets.h
 * Author: dp
 *
 * Created on January 6, 2015, 1:55 PM
 */
#ifndef SOCKET_H
#define	SOCKET_H

#define BUFLEN 512
#define DATA_BUFFER 158
#define GSMTAP_BUFLEN 81

#define CLK_SRC_PORT 5800
#define CLK_DST_PORT 5700   
#define CTR_SRC_PORT 5801
#define CTR_DST_PORT 5701
#define DATA_SRC_PORT 5802
#define DATA_DST_PORT 5702
#define INOVA_SRC_PORT 5948
#define INOVA_DST_PORT 23000
#define GSMTAP_SRC_PORT 45801
#define GSMTAP_DST_PORT 4729
#define MOBILE_SRC_PORT 20789
//#define MOBILE_SRC_PORT_ALT 20789
#define MOBILE_DST_PORT 19789
#define LOOP_SRC_PORT 9999
#define LOCAL_HOST "127.0.0.1"

int OpenClockSocket();
int OpenControlSocket();
int OpenDataSocket();
int OpenInovaSocket();
int OpenGSMTAPSocket();
int OpenMobileSocket();

int ReceiveFromClockSocket(int clock_fd);
int ReceiveFromControlSocket(int ctrl_fd);
int ReceiveFromDataSocket(int data_fd);
int ReceiveFromInovaSocket(int inova_fd);
int ReceiveFromGSMTAPSocket(int gsmtap_fd, int mobile_fd, int data_fd);
int ReceiveFromMobileSocket(int mobile_fd, int data_fd);

int SendToClockSocket(int ClkCmd, int clock_fd);
int SendToControlSocket(int CtrlCmdResp,  int ctrl_fd);
//int SendToDataSocket(struct gsmtap_hdr *gsmtap_rach, int data_fd, int size);
int SendToInovaSocket(int inova_fd);
int SendToGSMTAPSocket(int gsmtap_fd);

//int SendToL1SAPSocket(struct gsm_bts_trx, struct osmo_phsap_prim, int)

#endif	/* SOCKET_H */

