#include <stdio.h>  //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/un.h>
#include <signal.h>
#include <poll.h>
#include <stropts.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>

#include "eBTS.h"
#include "eSockets.h"
#include "eL1.h"
#include "eMessages.h"

#include <osmocom/gsm/protocol/gsm_04_08.h>
#include <osmocom/core/gsmtap.h>
#include <osmocom/core/gsmtap_util.h>

//int HandleReceivedMobileMessage (struct gsmtap_hdr *gsmtap_msg, ubit_t *bits, int data_fd);

int HandleReceivedMobileMessage (int mobile_fd, unsigned char *recv_buf, int size);

int HandleReceivedMobileMessage (int mobile_fd, unsigned char *recv_buf, int size)
{
    struct gsmtap_hdr *gsmtap_msg= malloc(sizeof(struct gsmtap_hdr));
    struct gsmtap_hdr *gsmtap_mobile= malloc(sizeof(struct gsmtap_hdr));
 
    uint8_t tn, bid, rssi, toa, chan_type, link_id = 0;
    uint32_t fn;
    uint8_t buf[154];
    
    memcpy(gsmtap_msg, recv_buf, sizeof(struct gsmtap_hdr));
    //memcpy(bits, recv_buf+sizeof(struct gsmtap_hdr), size-sizeof(struct gsmtap_hdr));
    
    printf("GSMTAP message:         \n");
    printf("-version:     %" SCNd8 "\n"
	   "-hdr_len:     %" SCNd8 "\n"
	   "-type:        %" SCNd8 "\n"
	   "-timeslot:    %" SCNd8 "\n"
	   "-arfcn:       %" PRIu16"\n"
	   "-signal_dbm:  %" SCNd8 "\n"
	   "-snr_db:      %" SCNd8 "\n"
	   "-frame_number:%" PRIu32"\n"
	   "-sub_type:    %" SCNd8 "\n"
	   "-antenna_nr:  %" SCNd8 "\n"
	   "-sub_slot:    %" SCNd8 "\n"
	   "-res:         %" SCNd8 "\n",

	   gsmtap_msg->version,
	   gsmtap_msg->hdr_len,
	   gsmtap_msg->type,
	   gsmtap_msg->timeslot,
	   gsmtap_msg->arfcn,
	   gsmtap_msg->signal_dbm,
	   gsmtap_msg->snr_db,
	   gsmtap_msg->frame_number,
	   gsmtap_msg->sub_type,
	   gsmtap_msg->antenna_nr,
	   gsmtap_msg->sub_slot,
	   gsmtap_msg->res);

    bid = 0; // moze byt aj 1,2,3
    rssi = 0;
    toa = 0;
    fn = gsmtap_msg->frame_number;
    link_id = (gsmtap_msg->sub_type & 0xF0);
    tn = gsmtap_msg->timeslot;
    
    //chan_type = 0x03;//(gsmtap_msg->sub_type & 0x0F >> 4 );
    //chan = chantype_gsmtap2rsl(chan_type, link_id);
    
    gsmtap_mobile->version = gsmtap_msg->version;
    gsmtap_mobile->hdr_len = gsmtap_msg->hdr_len;
    gsmtap_mobile->type = gsmtap_msg->type;
    gsmtap_mobile->timeslot = gsmtap_msg->timeslot;
    gsmtap_mobile->arfcn = gsmtap_msg->arfcn;
    gsmtap_mobile->signal_dbm = gsmtap_msg->signal_dbm;
    gsmtap_mobile->snr_db = gsmtap_msg->snr_db;
    gsmtap_mobile->frame_number = gsmtap_msg->frame_number;
    gsmtap_mobile->sub_type = gsmtap_msg->sub_type;
    gsmtap_mobile->antenna_nr = gsmtap_msg->antenna_nr;
    gsmtap_mobile->sub_slot = gsmtap_msg->sub_slot;
    gsmtap_mobile->res = gsmtap_msg->res;
    
    //size = sizeof(struct gsmtap_hdr);
    SendToMobileSocket(mobile_fd, gsmtap_mobile, size);
    return 0;
}
/*
int HandleReceivedMobileMessage (struct gsmtap_hdr *gsmtap_msg, ubit_t *bits, int data_fd)
{
    uint8_t buf[154];
    uint8_t tn, bid, rssi, toa, chan_type, link_id = 0;
    uint32_t fn;
    
    printf("GSMTAP message:         \n");
    printf("-version:     %" SCNd8 "\n"
	   "-hdr_len:     %" SCNd8 "TThT\n"
	   "-type:        %" SCNd8 "\n"
	   "-timeslot:    %" SCNd8 "\n"
	   "-arfcn:       %" PRIu16"\n"
	   "-signal_dbm:  %" SCNd8 "\n"
	   "-snr_db:      %" SCNd8 "\n"
	   "-frame_number:%" PRIu32"\n"
	   "-sub_type:    %" SCNd8 "\n"
	   "-antenna_nr:  %" SCNd8 "\n"
	   "-sub_slot:    %" SCNd8 "\n"
	   "-res:         %" SCNd8 "\n",

	   gsmtap_msg->version,
	   gsmtap_msg->hdr_len,
	   gsmtap_msg->type,
	   gsmtap_msg->timeslot,
	   gsmtap_msg->arfcn,
	   gsmtap_msg->signal_dbm,
	   gsmtap_msg->snr_db,
	   gsmtap_msg->frame_number,
	   gsmtap_msg->sub_type,
	   gsmtap_msg->antenna_nr,
	   gsmtap_msg->sub_slot,
	   gsmtap_msg->res);

    bid = 0; // moze byt aj 1,2,3
    rssi = 0;
    toa = 0;
    fn = gsmtap_msg->frame_number;
    link_id = (gsmtap_msg->sub_type & 0xF0);
    tn = gsmtap_msg->timeslot;
    chan_type = (gsmtap_msg->sub_type & 0x0F >> 4 );
    //chan = chantype_gsmtap2rsl(chan_type, link_id);

    buf[0] = tn;
    buf[1] = (fn >> 24) & 0xff;
    buf[2] = (fn >> 16) & 0xff;
    buf[3] = (fn >>  8) & 0xff;
    buf[4] = (fn >>  0) & 0xff;
    buf[5] = gsmtap_msg->signal_dbm;
    buf[6] = rssi;
    buf[7] = toa;
    
    memcpy(buf + 8, bits, 146);

    SendToDataSocket(buf, data_fd);
    return 0;
}
*/
uint8_t chantype_gsmtap2rsl(uint8_t gsmtap_chantype, uint8_t link_id)
{
	uint8_t ret = GSMTAP_CHANNEL_UNKNOWN;

	switch (gsmtap_chantype) {
	case GSMTAP_CHANNEL_TCH_F:
		ret = RSL_CHAN_Bm_ACCHs;
		break;
	case GSMTAP_CHANNEL_TCH_H:
		ret = RSL_CHAN_Lm_ACCHs;
		break;
	case GSMTAP_CHANNEL_SDCCH4:
		ret = RSL_CHAN_SDCCH4_ACCH;
		break;
	case GSMTAP_CHANNEL_SDCCH8:
		ret = RSL_CHAN_SDCCH8_ACCH;
		break;
	case GSMTAP_CHANNEL_BCCH:
		ret = RSL_CHAN_BCCH;
		break;
	case GSMTAP_CHANNEL_RACH:
		ret = RSL_CHAN_RACH;
		break;
	case GSMTAP_CHANNEL_PCH:
		/* it could also be AGCH... */
		ret = RSL_CHAN_PCH_AGCH;
		break;
	}

	if (link_id & 0x40)
		ret |= GSMTAP_CHANNEL_ACCH;

	return ret;
}










