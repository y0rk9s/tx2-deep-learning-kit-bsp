/*
 * Copyright (c) 2016 NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef LINUX_TEGRA_IVC_RPC_COMMON_H
#define LINUX_TEGRA_IVC_RPC_COMMON_H

#if defined(__KERNEL__)
#include <linux/types.h>
#include <linux/compiler.h>
#else
#include <stdint.h>
#ifndef __packed
#define __packed __attribute__((packed))
#endif
#endif

/*
 * IVC frame:
 *
 * Each RPC request IVC frame has following information
 * - RPC request signature: Signature that tells this message is
 *   an IVC/RPC request message.
 * - sequence number: 32 bit. This distinguishes each message. Can be wrapped
 *   around.
 * - flags: 32 bit.
 * - request ID: 32 bit. Unique ID that identify the request type.
 * - request length: 32 bit. Length of payload in bytes.
 * - request body: Payload of variable length.
 *
 * RPC response IVC frame has following information.
 * - RPC response signature: Signature that tells this message is
 *   an IVC/RPC reponse message.
 * - sequence number: Same as request message.
 * - return code: Return code of IVC/RPC operation. Negative for errors.
 * - return data: Additional data provided by the responder.
 * - timestamps: Timestamp when the request message is received and when the
 *   reponse message is scheduled.
 * - response ID: Response message type.
 * - reponse length: Length of payload in bytes.
 * - response body: Payload of variable length.
 */

/*
 * Signatures
 */

#define TEGRA_IVC_RPC_REQ_SIGN			0x5152564EU
#define TEGRA_IVC_RPC_RSP_SIGN			0x5252564EU

/*
 * Common message
 */

/* response message without additional payload */
#define TEGRA_IVC_RPC_RSP_RET_CODE		0x7fffffffU

/* RPC debug messages
 *
 * NODATA: Expect RSP_RET_CODE as response message
 * DATA: Expect RSP_TEST_DATA_ACK as response message
 * ACK: Expect the target to respond to the message
 * NACK: Expect the target not to respond (times out)
 */
#define TEGRA_IVC_RPC_REQ_TEST_NODATA_ACK	0x7ffffe00U
#define TEGRA_IVC_RPC_REQ_TEST_NODATA_NACK	0x7ffffe01U
#define TEGRA_IVC_RPC_REQ_TEST_DATA_ACK		0x7ffffe02U
#define TEGRA_IVC_RPC_REQ_TEST_DATA_NACK	0x7ffffe03U

#define TEGRA_IVC_RPC_RSP_TEST_DATA_ACK		0x7ffffe02U

/* return code */
#define TEGRA_IVC_RPC_ERR_RANGE_INIT_BEGIN	(-1024)
#define TEGRA_IVC_RPC_ERR_RANGE_INIT_END	(-2047)
#define TEGRA_IVC_RPC_ERR_RANGE_RSP_BEGIN	(-2048)
#define TEGRA_IVC_RPC_ERR_RANGE_RSP_END		(-3071)
#define TEGRA_IVC_RPC_ERR_RANGE_USER_BEGIN	(-4096)

/* error codes generated by target */
#define TEGRA_IVC_RPC_ERR_RSP_UNKNOWN_REQ \
	(TEGRA_IVC_RPC_ERR_RANGE_RSP_BEGIN - 0) /* Unknwon request - RPC */
#define TEGRA_IVC_RPC_ERR_RSP_UNKNOWN_REQ_NON_RPC \
	(TEGRA_IVC_RPC_ERR_RANGE_RSP_BEGIN - 1) /* Unknwon request - Non RPC */
#define TEGRA_IVC_RPC_ERR_RSP_PARAM \
	(TEGRA_IVC_RPC_ERR_RANGE_RSP_BEGIN - 2) /* Invalid parameter */
#define TEGRA_IVC_RPC_ERR_RSP_MEMORY \
	(TEGRA_IVC_RPC_ERR_RANGE_RSP_BEGIN - 3) /* Out of memory */
#define TEGRA_IVC_RPC_ERR_RSP_NODEV \
	(TEGRA_IVC_RPC_ERR_RANGE_RSP_BEGIN - 4) /* No device */
#define TEGRA_IVC_RPC_ERR_RSP_IO \
	(TEGRA_IVC_RPC_ERR_RANGE_RSP_BEGIN - 5) /* I/O error */

/*
 * Message structure
 *
 * ..._header structures have RPC headers without payload.
 * ..._frame structures have an additional field for payload.
 * ..._frame structures should not be used to allocate memory block
 * in the memory. Use only pointers to ..._frame structures.
 */

#define TEGRA_IVC_RPC_MSG_HEADER_MAX		32U
#define TEGRA_IVC_RPC_MSG_PAYLOAD_MAX		0x400U

#define TEGRA_IVC_RPC_CAST_PAYLOAD(type, rpc_msg) \
	((type *) (rpc_msg->payload8))
#define TEGRA_IVC_RPC_CAST_CPAYLOAD(type, rpc_msg) \
	((const type *) (rpc_msg->payload8))

struct tegra_ivc_rpc_request_header {
	uint32_t rpc_req_sign;
	uint32_t seq_num;
	uint32_t flags;
	uint32_t reserved;
	uint32_t request_id;
	uint32_t request_len;
} __packed;

struct tegra_ivc_rpc_request_frame {
	struct tegra_ivc_rpc_request_header hdr;
	union {
		uint8_t payload8[TEGRA_IVC_RPC_MSG_PAYLOAD_MAX];
		uint32_t payload32[TEGRA_IVC_RPC_MSG_PAYLOAD_MAX / 4];
	};
} __packed;

struct tegra_ivc_rpc_response_header {
	uint32_t rpc_rsp_sign;
	uint32_t seq_num;
	int32_t ret_code;
	uint32_t ret_data;
	uint32_t tstamp_req_received;
	uint32_t tstamp_rsp_sent;
	uint32_t response_id;
	uint32_t response_len;
} __packed;

struct tegra_ivc_rpc_response_frame {
	struct tegra_ivc_rpc_response_header hdr;
	union {
		uint8_t payload8[TEGRA_IVC_RPC_MSG_PAYLOAD_MAX];
		uint32_t payload32[TEGRA_IVC_RPC_MSG_PAYLOAD_MAX / 4];
	};
} __packed;

#endif /* LINUX_TEGRA_IVC_RPC_COMMON_H */