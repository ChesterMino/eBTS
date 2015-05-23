/* 
 * File:   main.c
 * Author: dp
 *
 * Created on December 30, 2014, 9:45 PM
 */

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


void die(char *msg)
{
   perror(msg);
   exit(1);
}


int SocketsHandler(int clock_file_desc, int ctrl_file_desc, int data_file_desc, int mobile_file_desc, int gsmtap_file_desc, int inova_file_desc)
{
    unsigned int poll_timeout = 500;
    struct pollfd fds[6];
    int p_ret, i;
   
    
    fds[0].fd = clock_file_desc;
    fds[1].fd = ctrl_file_desc;
    fds[2].fd = data_file_desc;
    fds[3].fd = inova_file_desc;
    fds[4].fd = gsmtap_file_desc;
    fds[5].fd = mobile_file_desc;
    
    fds[0].events = POLLIN|POLLPRI;
    fds[1].events = POLLIN|POLLPRI;
    fds[2].events = POLLIN|POLLPRI;
    fds[3].events = POLLIN|POLLPRI;
    fds[4].events = POLLIN|POLLPRI;
    fds[5].events = POLLIN|POLLPRI;
    
    
    p_ret = poll(fds,5,poll_timeout);
    
    if (p_ret >= 0)
    {
        for (i=0; i<5; i++)
        {
            if(((fds[i].revents&POLLIN) == POLLIN) || ((fds[i].revents&POLLPRI) == POLLPRI))
            {
                if(i == 0)
                {
                    printf("Checking clock socket.\n");
                    ReceiveFromClockSocket(clock_file_desc);
                }
                if(i == 1)
                {
                    printf("Checking control socket.\n");
                    ReceiveFromControlSocket(ctrl_file_desc);
                }
                if(i == 2)
                {
                    printf("Checking data socket.\n");
                    ReceiveFromDataSocket(data_file_desc);
                }
                if(i == 3)
                {
                    printf("Checking Inova socket.\n");
                    ReceiveFromInovaSocket(inova_file_desc);  
                }
                if(i == 4)
                {
                    printf("Checking GSMTAP socket.\n");
                    ReceiveFromGSMTAPSocket(gsmtap_file_desc, mobile_file_desc, data_file_desc);
                }
                if(i == 5)
                {
                    printf("Checking Mobile socket.\n");
                    ReceiveFromMobileSocket(mobile_file_desc, data_file_desc);
                }
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    printf("Starting eBTS.\n");
    
    clock_fd = OpenClockSocket(); 
    ctrl_fd = OpenControlSocket();
    data_fd = OpenDataSocket();
    inova_fd = OpenInovaSocket();
    gsmtap_fd = OpenGSMTAPSocket();
    mobile_fd = OpenMobileSocket();
 
    while(1)
    {
        /*main loop*/
        SendClockCommand(clock_fd);
        SocketsHandler(clock_fd, ctrl_fd, data_fd, mobile_fd, gsmtap_fd, inova_fd);
     
    }  
    
    close(clock_fd);
    close(ctrl_fd);
    close(data_fd);
    close(mobile_fd);
    close(inova_fd);
    close(gsmtap_fd);
    
    return 0;
}