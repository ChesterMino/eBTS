#include <stdio.h>  //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/un.h>
#include <signal.h>
#include <poll.h>
#include <stropts.h>
#include <errno.h>

#include "eBTS.h"
#include "eSockets.h"
#include "eMessages.h"

int SendClockCommand(int clock_fd);
void CompareClockCommand(const char *ClkCmd);

int SendClockCommand(int clock_fd)
{
   const char ClkCmd[] = "IND CLOCK 2715648";
   sleep(1);
   SendToClockSocket(&ClkCmd , clock_fd);  
   return 0;  
}

int CompareControlCommand (int CtrlCmd, int ctrl_fd)
{
    
    //original commandy su v OsmoTRX drivery v Transceiver.cpp - riadok 600
    char CtrlCmdResp[128];
    CtrlCmdResp[0]= '\0';
    int i;
    
   
    if(strcmp(CtrlCmd,"CMD POWEROFF")==0){
        sprintf(CtrlCmdResp, "RSP POWEROFF 0");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    
    else if(strcmp(CtrlCmd,"CMD POWERON")==0){
        sprintf(CtrlCmdResp, "RSP POWERON 0");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETMAXDLY")==0){
        sprintf(CtrlCmdResp, "RSP SETMAXDLY 0 1");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETMAXDLY 1")==0){
        sprintf(CtrlCmdResp, "RSP SETMAXDLY 0 1");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETRXGAIN 0")==0){
        sprintf(CtrlCmdResp, "RSP SETRXGAIN 0 10");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETRXGAIN 47")==0){
        sprintf(CtrlCmdResp, "RSP SETRXGAIN 0 47");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD NOISELEV")==0){
        sprintf(CtrlCmdResp, "RSP NOISELEV 0 5"); 
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 0")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 10");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 10")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 10");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 9")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 9");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 8")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 8");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 7")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 7");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 6")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 6");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 5")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 5");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 4")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 4");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 3")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 3");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 2")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 2");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETPOWER 1")==0){
        sprintf(CtrlCmdResp, "RSP SETPOWER 0 1");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD ADJPOWER")==0){
        sprintf(CtrlCmdResp, "RSP ADJPOWER 0 11");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD RXTUNE 1781600")==0){
        sprintf(CtrlCmdResp, "RSP RXTUNE 0 900200");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD RXTUNE 900200")==0){
        sprintf(CtrlCmdResp, "RSP RXTUNE 0 900200");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD TXTUNE 1876600")==0){
        sprintf(CtrlCmdResp, "RSP TXTUNE 0 945200");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD TXTUNE 945200")==0){
        sprintf(CtrlCmdResp, "RSP TXTUNE 0 945200");
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETTSC 2")==0){
        sprintf(CtrlCmdResp, "RSP SETTSC 0 2"); //to cislo na mieste 10 treba zistit co tam ma byt
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETTSC 7")==0){
        sprintf(CtrlCmdResp, "RSP SETTSC 0 7"); //to cislo na mieste 10 treba zistit co tam ma byt
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETBSIC 63")==0){
        sprintf(CtrlCmdResp, "RSP SETBSIC 0 63"); //to cislo na mieste 10 treba zistit co tam ma byt
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 0 5")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 5 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 1 1")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 2 1")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 3 1")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 4 1")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 5 1")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 6 0")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 6 1")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 6 13")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 0"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 7 0")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 1"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 7 1")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 1"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else if(strcmp(CtrlCmd,"CMD SETSLOT 7 13")==0){
        sprintf(CtrlCmdResp, "RSP SETSLOT 0 1 1"); //8 a 1 su: timeslot a corrCode - will see co to bude robit
        printf("Sending response on: %s command with response: %s .\n",CtrlCmd, CtrlCmdResp);
        SendToControlSocket(&CtrlCmdResp, ctrl_fd);
    }
    else{
        printf("Unrecognized command: %s\n", CtrlCmd);
        sprintf(&CtrlCmdResp, "Unrecognized command: %s .\n",CtrlCmd);
        //SendToControlSocket(CtrlCmdResp, ctrl_fd);   
    } 
    
    return 0;
    
}

