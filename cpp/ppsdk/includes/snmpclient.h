/*******************************************************************************
**                    Septentrio Satellite Navigation N.V                     **
**  ************************************************************************  **
**  ************************ COPYRIGHT INFORMATION *************************  **
**  This program contains proprietary information which is a trade secret of  **
**  Septentrio N.V. and also is protected as an unpublished work under        **
**  applicable copyright laws. Recipient is to retain this program in         **
**  confidence and is not permitted to use or make copies thereof other than  **
**  as permitted in a written agreement with Septentrio N.V.                  **
**  All rights reserved. Company confidential.                                **
**  ************************************************************************  **
*******************************************************************************/

/*!

  \file
  \ingroup SNMPMIB_SNMP
  \brief (S)imple (N)etwork (M)anagement (P)rotocol client.

  This file contains the functionality to handle
  - set and get requests from a client point of view
  - handle replies

  \par Origin:
  General

  \par Author:
  Freddy Voorspoels
  \par Backup:
  Philipe Jacobs

  \par Copyright:
  (c) 2006 Septentrio Satellite Navigation nv/sa, Belgium

*/

#ifndef SNMPCLIENT_H
#define SNMPCLIENT_H 1                 /*!< To avoid multiple inclusions */

/* Includes ==(needed for self-contained / -consistent)======================*/

#include "ssntypes.h"
#include "snmptypes.h"

#include <stddef.h>       /* size_t */

#ifdef __cplusplus
extern "C" {
#endif

/* Declarations =============================================================*/

/* Constants & Macros -------------------------------------------------------*/

/* Types --------------------------------------------------------------------*/

/* External Variables/Structs -----------------------------------------------*/

/* External Procedures ------------------------------------------------------*/

/*! Initialise header of message to empty message
  \param authlvl Authorization level
  \param *message [out] Initialise message header.

  \pre
    - message may not be NULL
    - (size of message must be large enough)
  \post
    - none
  \return
    - number of bytes added

  SNMP_initMessageHeader() initialises message header
*/
int32_t FW_EXPORT SNMP_initMessageHeader (
  snmpAuth_t authlvl,
  /*@out@*/ uint8_t *message
 );



/*! Add PDU header to message
  \param  type      [in]       type of message either SNMP_SET or SNMP_GET
  \param  requestID [in]       sequence number for message
  \param *message   [in/out]   snmp message

  \pre
    - message may not be NULL
    - type must use SNMP_SET or SNMP_GET
    - messageheader should be initialised through SNMP_initMessageHeader()
    - (size of message must be large enough)
  \post
    - none
  \return
    - number of bytes added

  SNMP_addPDUHeader() add (P)rotocol (D)ata (U)nit header to already
  initialised message
 */
int32_t FW_EXPORT SNMP_addPDUHeader (
            char     type,
            uint8_t  requestID,
  /*@out@*/ uint8_t *message
 );



/*! Add next variable binding to snmp message
  \param *oid     [in]     Object IDentification of variable binding
  \param *val     [in]     Value of variable binding
  \param *message [in/out] snmp message

  \pre
    - oid may not be NULL
    - val may not be NULL
    - message may not be NULL
    - PDU heading heading must be present
    - length of value must be available in oid
    - (size of message must be large enough to add variable binding)
  \post
    - none
  \return
    - number of bytes added

  SNMP_addVarBinding() add variable binding to already existing PDU
 */
int32_t FW_EXPORT SNMP_addVarBinding (
                  snmpOID_t *oid,
            const uint8_t   *val,
  /*@out@*/       uint8_t   *message
 );

/*! Add next variable binding to snmp message in a memory safe way
  \param *oid        [in]     Object IDentification of variable binding
  \param *val        [in]     Value of variable binding
  \param *message    [in/out] snmp message
  \param messageSize [in/out] snmp message size

  \return
    - number of bytes added
 */
int32_t FW_EXPORT SNMP_addVarBindingSafe (
                  snmpOID_t  *oid,
            const uint8_t    *val,
                  uint8_t    *message,
            const size_t      messageSize);

/*---------------------------------------------------------------------------*/
/*! Get message header out of snmp message
  \param *message  [in]   snmp message
  \param *header   [out]  message header retrieved from message

  \pre
    - message may not be NULL
    - header  may not be NULL
    - message must be snmp message
  \post
    - none
  \return
    - offset to PDU Header
    - -1 if the message is not a valid snmp message

  SNMP_getMessageHeader() get message header out of the SNMP message
 */
int32_t FW_EXPORT SNMP_getMessageHeader (
            uint8_t      *message,
  /*@out@*/ snmpHeader_t *header
 );



/*! Get PDU Header out of snmp message
  \param *message   [in]   snmp message
  \param *pduHeader [out]  PDU header retrieved from the snmp message

  \pre
    - message may not be NULL
    - pduHeader may not be NULL
    - snmp message must contain PDU header
  \post
    - none
  \return
    - position of next variable binding
    - -1 if no variable binding available (which shouldn't be the case!)

  SNMP_getPDUHeader() get PDU header out of snmp message.
 */
int32_t FW_EXPORT SNMP_getPDUHeader (
            uint8_t         *message,
  /*@out@*/ snmpPDUHeader_t *pduHeader
 );



/*! Get variable binding out of snmp message
  \param *message   [in]   snmp message
  \param  offset    [in]   offset in message of variable binding
  \param *oid       [out]  oid of retrieved variable binding
  \param *val       [val]  retrieved value

  \pre
    - oid may not be NULL
    - val may not be NULL
    - message may not be NULL
    - offset must be past end of pdu header
    - snmp message must contain PDU
  \post
    - none
  \return
    - position of next variable binding
    - -1 if last variable binding was already read in previous get.

  SNMP_getVarBinding() get variable binding at offset out of snmp message
 */
int32_t FW_EXPORT SNMP_getVarBinding (
            uint8_t   *message,
            int32_t    offset,
  /*@out@*/ snmpOID_t *oid,
  /*@out@*/ uint8_t   *val
 );

#ifdef __cplusplus
}
#endif

#endif                                 /* SNMPCLIENT_H */
/* END OF HEADER FILE =======================================================*/
