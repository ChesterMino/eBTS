#ifndef L1_IF_H_TRX
#define L1_IF_H_TRX

//#include "/home/dp/Diplomka/osmo-bts/src/osmo-bts-trx/l1_if.h"

//int CreateL1SAPMessage(struct gsmtap_hdr *gsmtap_msg, struct l1 *l1msg, enum trx_chan_type chan);
//int HandleReceivedMobileMessage (struct gsmtap_hdr *gsmtap_msg, ubit_t *bits, int data_fd);
//int ReceivedL1Message(struct l1 *l1msg);

uint8_t chantype_gsmtap2rsl(uint8_t gsmtap_chantype, uint8_t link_id);

#define GSMTAP_CHANNEL_TCH_H 0x0a;
#define GSMTAP_CHANNEL_SDCCH4 0x07;
#define GSMTAP_CHANNEL_SDCCH8 0x08;
#define GSMTAP_CHANNEL_BCCH 0x01;
#define GSMTAP_CHANNEL_RACH 0x03;
#define GSMTAP_CHANNEL_PCH 0x05

#define RSL_CHAN_Bm_ACCHs 0x08;
#define RSL_CHAN_Lm_ACCHs 0x10;
#define RSL_CHAN_SDCCH4_ACCH 0x20;
#define RSL_CHAN_SDCCH8_ACCH 0x40;
#define RSL_CHAN_BCCH 0x80;
#define RSL_CHAN_RACH 0x88;
#define RSL_CHAN_PCH_AGCH 0x90;

#endif /* L1_IF_H_TRX */
