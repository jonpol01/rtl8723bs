/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef _RTW_RECV_H_
#define _RTW_RECV_H_

	#ifdef CONFIG_SINGLE_RECV_BUF
		#define NR_RECVBUFF (1)
	#else
		#define NR_RECVBUFF (8)
	#endif //CONFIG_SINGLE_RECV_BUF

	#define NR_PREALLOC_RECV_SKB (8)

#define NR_RECVFRAME 256

#define RXFRAME_ALIGN	8
#define RXFRAME_ALIGN_SZ	(1<<RXFRAME_ALIGN)

#define DRVINFO_SZ	4 // unit is 8bytes

#define MAX_RXFRAME_CNT	512
#define MAX_RX_NUMBLKS		(32)
#define RECVFRAME_HDR_ALIGN 128


#define PHY_RSSI_SLID_WIN_MAX				100
#define PHY_LINKQUALITY_SLID_WIN_MAX		20


#define SNAP_SIZE sizeof(struct ieee80211_snap_hdr)

#define RX_MPDU_QUEUE				0
#define RX_CMD_QUEUE				1
#define RX_MAX_QUEUE				2

#define MAX_SUBFRAME_COUNT	64
extern u8 rtw_rfc1042_header[];
/* Bridge-Tunnel header (for EtherTypes ETH_P_AARP and ETH_P_IPX) */
extern u8 rtw_bridge_tunnel_header[];

//for Rx reordering buffer control
struct recv_reorder_ctrl
{
	_adapter	*padapter;
	u8 enable;
	u16 indicate_seq;//=wstart_b, init_value=0xffff
	u16 wend_b;
	u8 wsize_b;
	_queue pending_recvframe_queue;
	_timer reordering_ctrl_timer;
};

struct	stainfo_rxcache	{
	u16	tid_rxseq[16];
/*
	unsigned short	tid0_rxseq;
	unsigned short	tid1_rxseq;
	unsigned short	tid2_rxseq;
	unsigned short	tid3_rxseq;
	unsigned short	tid4_rxseq;
	unsigned short	tid5_rxseq;
	unsigned short	tid6_rxseq;
	unsigned short	tid7_rxseq;
	unsigned short	tid8_rxseq;
	unsigned short	tid9_rxseq;
	unsigned short	tid10_rxseq;
	unsigned short	tid11_rxseq;
	unsigned short	tid12_rxseq;
	unsigned short	tid13_rxseq;
	unsigned short	tid14_rxseq;
	unsigned short	tid15_rxseq;
*/
};


struct smooth_rssi_data {
	u32	elements[100];	//array to store values
	u32	index;			//index to current array to store
	u32	total_num;		//num of valid elements
	u32	total_val;		//sum of valid elements
};

struct signal_stat {
	u8	update_req;		//used to indicate
	u8	avg_val;		//avg of valid elements
	u32	total_num;		//num of valid elements
	u32	total_val;		//sum of valid elements
};
/*
typedef struct _ODM_Phy_Status_Info_
{
	//
	// Be care, if you want to add any element please insert between
	// RxPWDBAll & SignalStrength.
	//
	u1Byte		RxPWDBAll;

	u1Byte		SignalQuality;			// in 0-100 index.
	s8		RxMIMOSignalQuality[4];	//per-path's EVM
	u1Byte		RxMIMOEVMdbm[4];		//per-path's EVM dbm

	u1Byte		RxMIMOSignalStrength[4];// in 0~100 index

	u2Byte		Cfo_short[4];			// per-path's Cfo_short
	u2Byte		Cfo_tail[4];			// per-path's Cfo_tail

	s8		RxPower;				// in dBm Translate from PWdB
	s8		RecvSignalPower;		// Real power in dBm for this packet, no beautification and aggregation. Keep this raw info to be used for the other procedures.
	u1Byte		BTRxRSSIPercentage;
	u1Byte		SignalStrength;			// in 0-100 index.

	u1Byte		RxPwr[4];				//per-path's pwdb

	u1Byte		RxSNR[4];				//per-path's SNR
	u1Byte		BandWidth;
	u1Byte		btCoexPwrAdjust;
}ODM_PHY_INFO_T,*PODM_PHY_INFO_T;
*/

struct phy_info
{
	u8		RxPWDBAll;

	u8		SignalQuality;	 // in 0-100 index.
	s8		RxMIMOSignalQuality[4];	//per-path's EVM
	u8		RxMIMOEVMdbm[4];		//per-path's EVM dbm

	u8		RxMIMOSignalStrength[4];// in 0~100 index

	u16		Cfo_short[4];			// per-path's Cfo_short
	u16		Cfo_tail[4];			// per-path's Cfo_tail

	s8		RxPower; // in dBm Translate from PWdB
	s8		RecvSignalPower;// Real power in dBm for this packet, no beautification and aggregation. Keep this raw info to be used for the other procedures.
	u8		BTRxRSSIPercentage;
	u8		SignalStrength; // in 0-100 index.

	s8		RxPwr[4];				//per-path's pwdb
	u8		RxSNR[4];				//per-path's SNR
	u8		BandWidth;
	u8		btCoexPwrAdjust;
};

#ifdef DBG_RX_SIGNAL_DISPLAY_RAW_DATA
struct rx_raw_rssi
{
	u8 data_rate;
	u8 pwdball;
	s8 pwr_all;

	u8 mimo_singal_strength[4];// in 0~100 index
	u8 mimo_singal_quality[4];

	s8 ofdm_pwr[4];
	u8 ofdm_snr[4];

};
#endif

struct rx_pkt_attrib	{
	u16	pkt_len;
	u8	physt;
	u8	drvinfo_sz;
	u8	shift_sz;
	u8	hdrlen; //the WLAN Header Len
	u8	to_fr_ds;
	u8	amsdu;
	u8	qos;
	u8	priority;
	u8	pw_save;
	u8	mdata;
	u16	seq_num;
	u8	frag_num;
	u8	mfrag;
	u8	order;
	u8	privacy; //in frame_ctrl field
	u8	bdecrypted;
	u8	encrypt; //when 0 indicate no encrypt. when non-zero, indicate the encrypt algorith
	u8	iv_len;
	u8	icv_len;
	u8	crc_err;
	u8	icv_err;

	u16	eth_type;

	u8	dst[ETH_ALEN];
	u8	src[ETH_ALEN];
	u8	ta[ETH_ALEN];
	u8	ra[ETH_ALEN];
	u8	bssid[ETH_ALEN];

	u8	ack_policy;

//#ifdef CONFIG_TCP_CSUM_OFFLOAD_RX
	u8	tcpchk_valid; // 0: invalid, 1: valid
	u8	ip_chkrpt; //0: incorrect, 1: correct
	u8	tcp_chkrpt; //0: incorrect, 1: correct
//#endif
	u8	key_index;

	u8	data_rate;
	u8	sgi;
	u8	pkt_rpt_type;
	u32	MacIDValidEntry[2];	// 64 bits present 64 entry.

/*
	u8	signal_qual;
	s8	rx_mimo_signal_qual[2];
	u8	signal_strength;
	u32	RxPWDBAll;
	s32	RecvSignalPower;
*/
	struct phy_info phy_info;
};


//These definition is used for Rx packet reordering.
#define SN_LESS(a, b)		(((a-b)&0x800)!=0)
#define SN_EQUAL(a, b)	(a == b)
//#define REORDER_WIN_SIZE	128
//#define REORDER_ENTRY_NUM	128
#define REORDER_WAIT_TIME	(50) // (ms)

#define RECVBUFF_ALIGN_SZ 8

#define RXDESC_SIZE	24
#define RXDESC_OFFSET RXDESC_SIZE

struct recv_stat
{
	unsigned int rxdw0;

	unsigned int rxdw1;

	unsigned int rxdw2;

	unsigned int rxdw3;

#ifndef BUF_DESC_ARCH
	unsigned int rxdw4;

	unsigned int rxdw5;

#endif //if BUF_DESC_ARCH is defined, rx_buf_desc occupy 4 double words
};

#define EOR BIT(30)

/*
accesser of recv_priv: rtw_recv_entry(dispatch / passive level); recv_thread(passive) ; returnpkt(dispatch)
; halt(passive) ;

using enter_critical section to protect
*/
struct recv_priv
{
	_lock	lock;

	//_queue	blk_strms[MAX_RX_NUMBLKS];    // keeping the block ack frame until return ack
	_queue	free_recv_queue;
	_queue	recv_pending_queue;
	_queue	uc_swdec_pending_queue;


	u8 *pallocated_frame_buf;
	u8 *precv_frame_buf;

	uint free_recvframe_cnt;

	_adapter	*adapter;

	u32	bIsAnyNonBEPkts;
	u64	rx_bytes;
	u64	rx_pkts;
	u64	rx_drop;

	uint  rx_icv_err;
	uint  rx_largepacket_crcerr;
	uint  rx_smallpacket_crcerr;
	uint  rx_middlepacket_crcerr;

	struct tasklet_struct irq_prepare_beacon_tasklet;
	struct tasklet_struct recv_tasklet;
	struct sk_buff_head free_recv_skb_queue;
	struct sk_buff_head rx_skb_queue;
#ifdef CONFIG_RX_INDICATE_QUEUE
	struct task rx_indicate_tasklet;
	struct ifqueue rx_indicate_queue;
#endif	// CONFIG_RX_INDICATE_QUEUE

	u8 *pallocated_recv_buf;
	u8 *precv_buf;    // 4 alignment
	_queue	free_recv_buf_queue;
	u32	free_recv_buf_queue_cnt;

	_queue	recv_buf_pending_queue;

	//For display the phy informatiom
	u8 is_signal_dbg;	// for debug
	u8 signal_strength_dbg;	// for debug

	u8 signal_strength;
	u8 signal_qual;
	s8 rssi;	//translate_percentage_to_dbm(ptarget_wlan->network.PhyInfo.SignalStrength);
	#ifdef DBG_RX_SIGNAL_DISPLAY_RAW_DATA
	struct rx_raw_rssi raw_rssi_info;
	#endif
	//s8 rxpwdb;
	s16 noise;
	//int RxSNRdB[2];
	//s8 RxRssi[2];
	//int FalseAlmCnt_all;


	_timer signal_stat_timer;
	u32 signal_stat_sampling_interval;
	//u32 signal_stat_converging_constant;
	struct signal_stat signal_qual_data;
	struct signal_stat signal_strength_data;
};

#define rtw_set_signal_stat_timer(recvpriv) _set_timer(&(recvpriv)->signal_stat_timer, (recvpriv)->signal_stat_sampling_interval)

struct sta_recv_priv {

	_lock	lock;
	sint	option;

	//_queue	blk_strms[MAX_RX_NUMBLKS];
	_queue defrag_q;	 //keeping the fragment frame until defrag

	struct	stainfo_rxcache rxcache;

	//uint	sta_rx_bytes;
	//uint	sta_rx_pkts;
	//uint	sta_rx_fail;

};


struct recv_buf
{
	_list list;

	_lock recvbuf_lock;

	u32	ref_cnt;

	PADAPTER adapter;

	u8	*pbuf;
	u8	*pallocated_buf;

	u32	len;
	u8	*phead;
	u8	*pdata;
	u8	*ptail;
	u8	*pend;

	_pkt	*pskb;
	u8	reuse;
};


/*
	head  ----->

		data  ----->

			payload

		tail  ----->


	end   ----->

	len = (unsigned int )(tail - data);

*/
struct recv_frame_hdr
{
	_list	list;
#ifndef CONFIG_BSD_RX_USE_MBUF
	struct sk_buff	 *pkt;
	struct sk_buff	 *pkt_newalloc;
#else // CONFIG_BSD_RX_USE_MBUF
	_pkt	*pkt;
	_pkt *pkt_newalloc;
#endif // CONFIG_BSD_RX_USE_MBUF

	_adapter  *adapter;

	u8 fragcnt;

	int frame_tag;

	struct rx_pkt_attrib attrib;

	uint  len;
	u8 *rx_head;
	u8 *rx_data; __aligned(sizeof(u16))
	u8 *rx_tail;
	u8 *rx_end;

	void *precvbuf;


	//
	struct sta_info *psta;

	//for A-MPDU Rx reordering buffer control
	struct recv_reorder_ctrl *preorder_ctrl;
};


union recv_frame{

	union{
		_list list;
		struct recv_frame_hdr hdr;
		uint mem[RECVFRAME_HDR_ALIGN>>2];
	}u;

	//uint mem[MAX_RXSZ>>2];

};

typedef enum _RX_PACKET_TYPE{
	NORMAL_RX,//Normal rx packet
	TX_REPORT1,//CCX
	TX_REPORT2,//TX RPT
	HIS_REPORT,// USB HISR RPT
	C2H_PACKET
}RX_PACKET_TYPE, *PRX_PACKET_TYPE;

extern union recv_frame *_rtw_alloc_recvframe (_queue *pfree_recv_queue);  //get a free recv_frame from pfree_recv_queue
extern union recv_frame *rtw_alloc_recvframe (_queue *pfree_recv_queue);  //get a free recv_frame from pfree_recv_queue
extern int	 rtw_free_recvframe(union recv_frame *precvframe, _queue *pfree_recv_queue);

#define rtw_dequeue_recvframe(queue) rtw_alloc_recvframe(queue)
extern int _rtw_enqueue_recvframe(union recv_frame *precvframe, _queue *queue);
extern int rtw_enqueue_recvframe(union recv_frame *precvframe, _queue *queue);

extern void rtw_free_recvframe_queue(_queue *pframequeue,  _queue *pfree_recv_queue);
u32 rtw_free_uc_swdec_pending_queue(_adapter *adapter);

sint rtw_enqueue_recvbuf_to_head(struct recv_buf *precvbuf, _queue *queue);
sint rtw_enqueue_recvbuf(struct recv_buf *precvbuf, _queue *queue);
struct recv_buf *rtw_dequeue_recvbuf (_queue *queue);

void rtw_reordering_ctrl_timeout_handler(void *pcontext);

__inline static u8 *get_rxmem(union recv_frame *precvframe)
{
	//always return rx_head...
	if(precvframe==NULL)
		return NULL;

	return precvframe->u.hdr.rx_head;
}

__inline static u8 *get_recvframe_data(union recv_frame *precvframe)
{

	//alwasy return rx_data
	if(precvframe==NULL)
		return NULL;

	return precvframe->u.hdr.rx_data;

}

__inline static u8 *recvframe_pull(union recv_frame *precvframe, sint sz)
{
	// rx_data += sz; move rx_data sz bytes  hereafter

	//used for extract sz bytes from rx_data, update rx_data and return the updated rx_data to the caller


	if(precvframe==NULL)
		return NULL;


	precvframe->u.hdr.rx_data += sz;

	if(precvframe->u.hdr.rx_data > precvframe->u.hdr.rx_tail)
	{
		precvframe->u.hdr.rx_data -= sz;
		return NULL;
	}

	precvframe->u.hdr.len -=sz;

	return precvframe->u.hdr.rx_data;

}

__inline static u8 *recvframe_put(union recv_frame *precvframe, sint sz)
{
	// rx_tai += sz; move rx_tail sz bytes  hereafter

	//used for append sz bytes from ptr to rx_tail, update rx_tail and return the updated rx_tail to the caller
	//after putting, rx_tail must be still larger than rx_end.
	unsigned char * prev_rx_tail;

	if(precvframe==NULL)
		return NULL;

	prev_rx_tail = precvframe->u.hdr.rx_tail;

	precvframe->u.hdr.rx_tail += sz;

	if(precvframe->u.hdr.rx_tail > precvframe->u.hdr.rx_end)
	{
		precvframe->u.hdr.rx_tail = prev_rx_tail;
		return NULL;
	}

	precvframe->u.hdr.len +=sz;

	return precvframe->u.hdr.rx_tail;

}



__inline static u8 *recvframe_pull_tail(union recv_frame *precvframe, sint sz)
{
	// rmv data from rx_tail (by yitsen)

	//used for extract sz bytes from rx_end, update rx_end and return the updated rx_end to the caller
	//after pulling, rx_end must be still larger than rx_data.

	if(precvframe==NULL)
		return NULL;

	precvframe->u.hdr.rx_tail -= sz;

	if(precvframe->u.hdr.rx_tail < precvframe->u.hdr.rx_data)
	{
		precvframe->u.hdr.rx_tail += sz;
		return NULL;
	}

	precvframe->u.hdr.len -=sz;

	return precvframe->u.hdr.rx_tail;

}

__inline static union recv_frame *rxmem_to_recvframe(u8 *rxmem)
{
	//due to the design of 2048 bytes alignment of recv_frame, we can reference the union recv_frame
	//from any given member of recv_frame.
	// rxmem indicates the any member/address in recv_frame

	return (union recv_frame*)(((SIZE_PTR)rxmem >> RXFRAME_ALIGN) << RXFRAME_ALIGN);

}

__inline static sint get_recvframe_len(union recv_frame *precvframe)
{
	return precvframe->u.hdr.len;
}


__inline static s32 translate_percentage_to_dbm(u32 SignalStrengthIndex)
{
	s32	SignalPower; // in dBm.

#ifdef CONFIG_SKIP_SIGNAL_SCALE_MAPPING
	// Translate to dBm (x=y-100)
	SignalPower = SignalStrengthIndex - 100;
#else
	// Translate to dBm (x=0.5y-95).
	SignalPower = (s32)((SignalStrengthIndex + 1) >> 1);
	SignalPower -= 95;
#endif

	return SignalPower;
}


struct sta_info;

extern void _rtw_init_sta_recv_priv(struct sta_recv_priv *psta_recvpriv);

extern void  mgt_dispatcher(_adapter *padapter, union recv_frame *precv_frame);

#endif
