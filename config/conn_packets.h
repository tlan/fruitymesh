////////////////////////////////////////////////////////////////////////////////
// /****************************************************************************
// **
// ** Copyright (C) 2015-2019 M-Way Solutions GmbH
// ** Contact: https://www.blureange.io/licensing
// **
// ** This file is part of the Bluerange/FruityMesh implementation
// **
// ** $BR_BEGIN_LICENSE:GPL-EXCEPT$
// ** Commercial License Usage
// ** Licensees holding valid commercial Bluerange licenses may use this file in
// ** accordance with the commercial license agreement provided with the
// ** Software or, alternatively, in accordance with the terms contained in
// ** a written agreement between them and M-Way Solutions GmbH.
// ** For licensing terms and conditions see https://www.bluerange.io/terms-conditions. For further
// ** information use the contact form at https://www.bluerange.io/contact.
// **
// ** GNU General Public License Usage
// ** Alternatively, this file may be used under the terms of the GNU
// ** General Public License version 3 as published by the Free Software
// ** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
// ** included in the packaging of this file. Please review the following
// ** information to ensure the GNU General Public License requirements will
// ** be met: https://www.gnu.org/licenses/gpl-3.0.html.
// **
// ** $BR_END_LICENSE$
// **
// ****************************************************************************/
////////////////////////////////////////////////////////////////////////////////
/*
 * This file contains the structs that are used for packets that are sent
 * over standard BLE connections, such as the mesh-handshake and other packets
 */

#pragma once

#include <types.h>

//Start packing all these structures
//These are packed so that they can be transmitted savely over the air
//Smaller datatypes could be implemented with bitfields?
//Sizeof operator is not to be trusted because of padding
// Pay attention to http://www.keil.com/support/man/docs/armccref/armccref_Babjddhe.htm

#pragma pack(push)
#pragma pack(1)


//########## Message types ###############################################
//First 15 types may be taken by advertising message types

#define MESSAGE_TYPE_SPLIT_WRITE_CMD 16 //Used if a WRITE_CMD message is split
#define MESSAGE_TYPE_SPLIT_WRITE_CMD_END 17 //Used if a WRITE_CMD message is split

//Mesh clustering and handshake: Protocol defined
#define MESSAGE_TYPE_CLUSTER_WELCOME 20 //The initial message after a connection setup (Sent between two nodes)
#define MESSAGE_TYPE_CLUSTER_ACK_1 21 //Both sides must acknowledge the handshake (Sent between two nodes)
#define MESSAGE_TYPE_CLUSTER_ACK_2 22 //Second ack (Sent between two nodes)
#define MESSAGE_TYPE_CLUSTER_INFO_UPDATE 23 //When the cluster size changes, this message is used (Sent to all nodes)
#define MESSAGE_TYPE_RECONNECT 24 //Sent while trying to reestablish a connection

//Custom Connection encryption handshake
#define MESSAGE_TYPE_ENCRYPT_CUSTOM_START 25
#define MESSAGE_TYPE_ENCRYPT_CUSTOM_ANONCE 26
#define MESSAGE_TYPE_ENCRYPT_CUSTOM_SNONCE 27
#define MESSAGE_TYPE_ENCRYPT_CUSTOM_DONE 28

//Others
#define MESSAGE_TYPE_UPDATE_TIMESTAMP 30 //Used to enable timestamp distribution over the mesh
#define MESSAGE_TYPE_UPDATE_CONNECTION_INTERVAL 31 //Intructs a node to use a different connection interval
#define MESSAGE_TYPE_ASSET_V2 32

//Module messages: Protocol defined (yet unfinished)
//MODULE_CONFIG: Used for many different messages that set and get the module config
//MODULE_TRIGGER_ACTION: trigger some custom module action
//MODULE_ACTION_RESPONSE: Response on a triggered action
//MODULE_GENERAL: A message, generated by the module not as a response to an action
#define MESSAGE_TYPE_MODULE_CONFIG 50
#define MESSAGE_TYPE_MODULE_TRIGGER_ACTION 51
#define MESSAGE_TYPE_MODULE_ACTION_RESPONSE 52
#define MESSAGE_TYPE_MODULE_GENERAL 53
#define MESSAGE_TYPE_MODULE_RAW_DATA 54
#define MESSAGE_TYPE_MODULE_RAW_DATA_LIGHT 55

//Request a listing of all modules and receive this list
#define MESSAGE_TYPE_MODULES_GET_LIST 56
#define MESSAGE_TYPE_MODULES_LIST 57

//Legacy messages: should be removed
#define MESSAGE_TYPE_ADVINFO 60

//Other packets: User space (IDs 80 - 110)
#define MESSAGE_TYPE_DATA_1 80
#define MESSAGE_TYPE_DATA_2 81

#define MESSAGE_TYPE_CLC_DATA 83


//########## Message structs and sizes ###############################################

//If hasMoreParts is set to true, the next message will only contain 1 byte hasMoreParts + messageType
//and all remaining 19 bytes are used for transferring data, the last message of a split message does not have this flag
//activated
#define SIZEOF_CONN_PACKET_HEADER 5
typedef struct
{
	u8 messageType;
	NodeId sender;
	NodeId receiver;
}connPacketHeader;
STATIC_ASSERT_SIZE(connPacketHeader, 5);


//Used for new message splitting
//Each split packet uses this header (first one, subsequent ones)
//First byte must be identical in with connPacketHeader
#define SIZEOF_CONN_PACKET_SPLIT_HEADER 2
typedef struct
{
	u8 splitMessageType;
	u8 splitCounter;
}connPacketSplitHeader;
STATIC_ASSERT_SIZE(connPacketSplitHeader, 2);

//CLUSTER_WELCOME
#define SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_WELCOME 11
#define SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_WELCOME_WITH_NETWORK_ID 13
typedef struct
{
	ClusterId clusterId;
	ClusterSize clusterSize;
	u16 meshWriteHandle;
	ClusterSize hopsToSink;
	u8 preferredConnectionInterval;
	NetworkId networkId;
}connPacketPayloadClusterWelcome;
STATIC_ASSERT_SIZE(connPacketPayloadClusterWelcome, 13);

#define SIZEOF_CONN_PACKET_CLUSTER_WELCOME (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_WELCOME)
#define SIZEOF_CONN_PACKET_CLUSTER_WELCOME_WITH_NETWORK_ID (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_WELCOME_WITH_NETWORK_ID)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadClusterWelcome payload;
}connPacketClusterWelcome;
STATIC_ASSERT_SIZE(connPacketClusterWelcome, 18);


//CLUSTER_ACK_1
#define SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_ACK_1 3
typedef struct
{
	ClusterSize hopsToSink;
	u8 preferredConnectionInterval;
}connPacketPayloadClusterAck1;
STATIC_ASSERT_SIZE(connPacketPayloadClusterAck1, 3);

#define SIZEOF_CONN_PACKET_CLUSTER_ACK_1 (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_ACK_1)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadClusterAck1 payload;
}connPacketClusterAck1;
STATIC_ASSERT_SIZE(connPacketClusterAck1, 8);


//CLUSTER_ACK_2
#define SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_ACK_2 8
typedef struct
{
	ClusterId clusterId;
	ClusterSize clusterSize;
	ClusterSize hopsToSink;
}connPacketPayloadClusterAck2;
STATIC_ASSERT_SIZE(connPacketPayloadClusterAck2, 8);

#define SIZEOF_CONN_PACKET_CLUSTER_ACK_2 (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_ACK_2)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadClusterAck2 payload;
}connPacketClusterAck2;
STATIC_ASSERT_SIZE(connPacketClusterAck2, 13);


//CLUSTER_INFO_UPDATE
#define SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_INFO_UPDATE 9
typedef struct
{
	ClusterId newClusterId;
	ClusterSize clusterSizeChange;
	ClusterSize hopsToSink;
	u8 connectionMasterBitHandover : 1; //Used to hand over the connection master bit
	u8 counter : 1; //A very small counter to protect against duplicate clusterUpdates
	u8 reserved : 6;
	
}connPacketPayloadClusterInfoUpdate;
STATIC_ASSERT_SIZE(connPacketPayloadClusterInfoUpdate, 9);

#define SIZEOF_CONN_PACKET_CLUSTER_INFO_UPDATE (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_CLUSTER_INFO_UPDATE)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadClusterInfoUpdate payload;
}connPacketClusterInfoUpdate;
STATIC_ASSERT_SIZE(connPacketClusterInfoUpdate, 14);


//CLUSTER_RECONNECT
#define SIZEOF_CONN_PACKET_PAYLOAD_RECONNECT 0
typedef struct
{

}connPacketPayloadReconnect;
STATIC_ASSERT_SIZE(connPacketPayloadReconnect, 1);

#define SIZEOF_CONN_PACKET_RECONNECT (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_RECONNECT)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadReconnect payload;
}connPacketReconnect;
STATIC_ASSERT_SIZE(connPacketReconnect, 6);


//Packets for CUSTOM ENC Handshake

#define SIZEOF_CONN_PACKET_ENCRYPT_CUSTOM_START (SIZEOF_CONN_PACKET_HEADER + 6)
typedef struct
{
	connPacketHeader header;
	u8 version;
	u32 fmKeyId;
	u8 tunnelType : 2;
	u8 reserved : 6;

}connPacketEncryptCustomStart;
STATIC_ASSERT_SIZE(connPacketEncryptCustomStart, 11);

#define SIZEOF_CONN_PACKET_ENCRYPT_CUSTOM_ANONCE (SIZEOF_CONN_PACKET_HEADER + 8)
typedef struct
{
	connPacketHeader header;
	u32 anonce[2];

}connPacketEncryptCustomANonce;
STATIC_ASSERT_SIZE(connPacketEncryptCustomANonce, 13);

#define SIZEOF_CONN_PACKET_ENCRYPT_CUSTOM_SNONCE (SIZEOF_CONN_PACKET_HEADER + 8)
typedef struct
{
	connPacketHeader header;
	u32 snonce[2];

}connPacketEncryptCustomSNonce;
STATIC_ASSERT_SIZE(connPacketEncryptCustomSNonce, 13);

#define SIZEOF_CONN_PACKET_ENCRYPT_CUSTOM_DONE (SIZEOF_CONN_PACKET_HEADER + 1)
typedef struct
{
	connPacketHeader header;
	u8 status;

}connPacketEncryptCustomDone;
STATIC_ASSERT_SIZE(connPacketEncryptCustomDone, 6);


//DATA_PACKET
#define SIZEOF_CONN_PACKET_PAYLOAD_DATA_1 (MAX_DATA_SIZE_PER_WRITE - SIZEOF_CONN_PACKET_HEADER)
typedef struct
{
	u8 length;
	u8 data[SIZEOF_CONN_PACKET_PAYLOAD_DATA_1 - 1];
	
}connPacketPayloadData1;
STATIC_ASSERT_SIZE(connPacketPayloadData1, 15);

#define SIZEOF_CONN_PACKET_DATA_1 (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_DATA_1)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadData1 payload;
}connPacketData1;
STATIC_ASSERT_SIZE(connPacketData1, 20);




//DATA_2_PACKET
#define SIZEOF_CONN_PACKET_PAYLOAD_DATA_2 (MAX_DATA_SIZE_PER_WRITE - SIZEOF_CONN_PACKET_HEADER)
typedef struct
{
	u8 length;
	u8 data[SIZEOF_CONN_PACKET_PAYLOAD_DATA_2 - 1];

}connPacketPayloadData2;
STATIC_ASSERT_SIZE(connPacketPayloadData2, 15);

#define SIZEOF_CONN_PACKET_DATA_2 (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_DATA_2)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadData1 payload;
}connPacketData2;
STATIC_ASSERT_SIZE(connPacketData2, 20);


//DATA_3_PACKET
#define SIZEOF_CONN_PACKET_PAYLOAD_DATA_3 (MAX_DATA_SIZE_PER_WRITE - SIZEOF_CONN_PACKET_HEADER)
typedef struct
{
	u8 len;
	u8 data[SIZEOF_CONN_PACKET_PAYLOAD_DATA_3-1];

}connPacketPayloadData3;
STATIC_ASSERT_SIZE(connPacketPayloadData3, 15);

#define SIZEOF_CONN_PACKET_DATA_3 (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_DATA_3)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadData3 payload;
}connPacketData3;
STATIC_ASSERT_SIZE(connPacketData3, 20);



//CLC_DATA_PACKET
#define SIZEOF_CONN_PACKET_PAYLOAD_CLC_DATA (MAX_DATA_SIZE_PER_WRITE - SIZEOF_CONN_PACKET_HEADER)
typedef struct
{
	u8 data[SIZEOF_CONN_PACKET_PAYLOAD_CLC_DATA];

}connPacketPayloadClcData;
STATIC_ASSERT_SIZE(connPacketPayloadClcData, 15);

#define SIZEOF_CONN_PACKET_CLC_DATA (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_CLC_DATA)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadClcData payload;
}connPacketDataClcData;
STATIC_ASSERT_SIZE(connPacketDataClcData, 20);


//Timestamp synchronization packet
#define SIZEOF_CONN_PACKET_UPDATE_TIMESTAMP (SIZEOF_CONN_PACKET_HEADER + 6)
typedef struct
{
	connPacketHeader header;
	u32 timestampSec;
	u16 remainderTicks;
}connPacketUpdateTimestamp;
STATIC_ASSERT_SIZE(connPacketUpdateTimestamp, 11);

//Used to tell nodes to update their connection interval settings
#define SIZEOF_CONN_PACKET_UPDATE_CONNECTION_INTERVAL (SIZEOF_CONN_PACKET_HEADER + 2)
typedef struct
{
	connPacketHeader header;
	u16 newInterval;
}connPacketUpdateConnectionInterval;
STATIC_ASSERT_SIZE(connPacketUpdateConnectionInterval, 7);

//This message is used for different module request message types
#define SIZEOF_CONN_PACKET_MODULE (SIZEOF_CONN_PACKET_HEADER + 3) //This size does not include the data reagion which is variable, add the used data region size to this size
typedef struct
{
	connPacketHeader header;
	u8 moduleId;
	u8 requestHandle; //Set to 0 if this packet does not need to be identified for reliability (Used to implement end-to-end acknowledged requests)
	u8 actionType;
	u8 data[MAX_DATA_SIZE_PER_WRITE - SIZEOF_CONN_PACKET_HEADER - 4]; //Data can be larger and will be transmitted in subsequent packets

}connPacketModule;
STATIC_ASSERT_SIZE(connPacketModule, 19);


//ADVINFO_PACKET
#define SIZEOF_CONN_PACKET_PAYLOAD_ADV_INFO 9
typedef struct
{
	u8 peerAddress[6];
	u16 inverseRssiSum;
	u8 packetCount;

}connPacketPayloadAdvInfo;
STATIC_ASSERT_SIZE(connPacketPayloadAdvInfo, 9);

//ADV_INFO
//This packet is used to distribute receied advertising messages in the mesh
//if the packet has passed the filterung
#define SIZEOF_CONN_PACKET_ADV_INFO (SIZEOF_CONN_PACKET_HEADER + SIZEOF_CONN_PACKET_PAYLOAD_ADV_INFO)
typedef struct
{
	connPacketHeader header;
	connPacketPayloadAdvInfo payload;
}connPacketAdvInfo;
STATIC_ASSERT_SIZE(connPacketAdvInfo, 14);




//End Packing
#pragma pack(pop)
