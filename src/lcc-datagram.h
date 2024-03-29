/* SPDX-License-Identifier: GPL-2.0 */
#ifndef LIBLCC_DATAGRAM_H
#define LIBLCC_DATAGRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lcc-common.h"

struct lcc_datagram_context* lcc_datagram_context_new(struct lcc_context* parent);

struct lcc_context* lcc_datagram_context_parent(struct lcc_datagram_context* ctx);

/**
 * Set a function that will be called during datagram transfers.
 * This needs to be setup before doing something that requires datagrams, for example
 * reading the CDI or memory.
 *
 * @param ctx
 * @param incoming_datagram
 * @return
 */
int lcc_datagram_context_set_datagram_functions(struct lcc_datagram_context* ctx,
                                       lcc_incoming_datagram_fn incoming_datagram,
                                       lcc_datagram_received_ok_fn datagram_ok,
                                       lcc_datagram_rejected_fn datagram_rejected);

/**
 * Load and send a datagram packet to another node.
 *
 * @param ctx
 * @param alias
 * @param data
 * @param data_len
 * @return
 */
int lcc_datagram_load_and_send(struct lcc_datagram_context* ctx,
                               uint16_t alias,
                               void* data,
                               int data_len);

/**
 * When we receive a datagram, call this function to respond back
 * to the sending node that we received the datagram OK.
 *
 * @param ctx
 * @param alias
 * @return
 */
int lcc_datagram_respond_rxok(struct lcc_datagram_context* ctx,
                              uint16_t alias,
                              int flags);

/**
 * When we receive a datagram, call this function to respond back
 * to the sending node that we rejected the datagram.
 *
 * @param ctx
 * @param alias
 * @param error_code The error code to send back(see LCC_ERRCODE family of macros)
 * @param optional_info Optional info to send back, max of 64 bytes of data.
 * @return
 */
int lcc_datagram_respond_rejected(struct lcc_datagram_context* ctx,
                                  uint16_t alias,
                                  uint16_t error_code,
                                  const char* optional_info);

/**
 * Check to see if a datagram transfer is currently in progress.
 *
 * @param ctx
 * @return
 */
int lcc_datagram_transfer_in_progress(struct lcc_datagram_context* ctx);

#ifdef __cplusplus
} /* extern C */
#endif

#endif
