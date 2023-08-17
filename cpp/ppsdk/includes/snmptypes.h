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
  \brief (S)imple (N)etwork (M)anagement (P)rotocol type description.

  This file gives the basic typedefs for:
  - The SNMP protocol
  \verbatim
  +---------+---------------------------------+
  | Message | PDU = (P)rotocol (D)ata (U)nit  |
  | Header  |                                 |
  +---------+---------------------------------+
  \endverbatim
  - The PDU
  \verbatim
  +------+-------+------+-----+ +-------+-------------+-------+---
  | PDU  |Request|Error |Error| |OID,   |OID,         |OID,   |...
  | type |  ID   |Status|Index| |payload|p a y l o a d|payload|...
  +------+-------+------+-----+ +-------+-------------+-------+---
  \endverbatim


  \par Note:
  These are pseudo-SNMP definitions that are proprietary to Septentrio. They
  match the SNMP build-up of the messages but are optimised amongst others
  to match native byte order of our receivers.

  \par Origin:
  General

  \par Author:
  Freddy Voorspoels
  \par Backup:
  Philipe Jacobs

  \par Copyright:
  (c) 2006 Septentrio Satellite Navigation nv/sa, Belgium

*/

#ifndef SNMPTYPES_H
#define SNMPTYPES_H 1                  /*!< To avoid multiple inclusions */


/* Includes ==(needed for self-contained / -consistent)======================*/

#include "ssntypes.h"

/* Declarations =============================================================*/

/* Constants & Macros -------------------------------------------------------*/

#define SNMP_VERSION1  1      /*!< Septentrio's 1st version of the interface */

#define SNMP_SET      'S'
#define SNMP_GET      'G'
#define SNMP_RESP     'R'


#define SNMPERROR_NONE       0   /*!< No error */
#define SNMPERROR_MSGTYPE    1   /*!< message of unknown type received */
#define SNMPERROR_OID        2   /*!< no OID or OID doesn't exist */
#define SNMPERROR_SETACTION  3   /*!< SET Action not available for this OID */
#define SNMPERROR_GETACTION  4   /*!< GET Action not available for this OID */
#define SNMPERROR_SIZE       5   /*!< Buffer size not correct for this OID */
#define SNMPERROR_VALUE      6   /*!< Value not within syntax for this OID */
#define SNMPERROR_EXE        7   /*!< Couldn't execute callback for this OID */
#define SNMPERROR_AUTH       8   /*!< Not authorized for this OID */
#define SNMPERROR_ENCRYPT    9   /*!< Encryption failed */
#define SNMPERROR_NOTREADY   10  /*!< Encryption failed */

#define NR_OF_SNMPERROR     (SNMPERROR_NOTREADY+1)


#define SNMP_MAX_SIZE        2048 /*!< Maximum allowed size for SNMP messages*/
#define SNMP_NBR_CMD_NO_INCR 3    /*!< Total number of commands that should not increment  cmdCount*/

/* Types --------------------------------------------------------------------*/
#pragma pack(push, 4)

/**
 * \brief SNMP Message Header.
 * The SNMP Message header is mainly used for synchronisation.
 */
typedef struct snmpHeader_s
{
  char           preamble[2];  /*!< { '$', '&' } */
  uint8_t        version;      /*!< Proprietary version */
  uint8_t        checksum;     /*!< modulo 2 checksum = XOR (header excluded)*/
  uint16_t       length;       /*!< Length of message (header not included) */
  /** The community field is used for access permissions.  We define it to
  always be two characters.  The second character is always a zero terminator.
  The first character gives the authentication level.  The levels are defined
  in ::snmpAuth_t */
  char           community[2];
} snmpHeader_t;


/**
 * \brief SNMP (P)rotocol (D)ata (U)nit header.
 * The PDU is a data-container for type of action and reserved room for reply status.
 */
typedef struct snmpPDUHeader_s
{
  char           type;         /*!< 'S'=Set, 'G'=Get, 'R'=Response */
  uint8_t        requestID;    /*!< sequence-number of request */
  uint8_t        errorStatus;  /*!< error occured */
  uint8_t        errorIndex;   /*!< at xth variable binding */
} snmpPDUHeader_t;

/**
 * \brief SNMP (O)bject (ID)entification of variable binding.
 * The OID gives size and OID of the variable binding.
 */
typedef struct snmpOID_s
{
  uint8_t        size;           /*!< size of payload */
  uint8_t        appl;           /*!< Application (eg IO, Navigation) */
  uint8_t        group;          /*!< CMD group */
  uint8_t        command;        /*!< CMD */
  uint8_t        arg_tableEntry; /*!< Argument or table entry (case of table)*/
  uint8_t        ind_tableArg;   /*!< 0 or Table Argument */
  uint8_t        tableInd;       /*!< index in table */
  uint8_t        nil;            /*!< always 0 */
} snmpOID_t;

typedef struct
{
  uint8_t appl; /*!< Application (eg IO, Navigation) */
  uint8_t group; /*!< CMD group */
  uint8_t command; /*!< CMD */
} excludesnmpOID_t;

/**
 * \brief SNMP 4Byte variable binding (OID included).
 * This variable binding is only useful for FInt32 and Enum32.
 */
typedef struct snmpBinding4_s
{
  snmpOID_t      oid;         /*!< OID of size 4 byte binding */
  int32_t        payload;     /*!< int32_t payload for FInt32, Enum32 */
} snmpBinding4_t;             /*   BitS and Str really have variable binding */


/** Values for the SNMP authorization level byte.

 The SNMP header contains two community bytes, the first of which defines
 authorization level and is set by the port that generates the SNMP command.
 This type defines the different values of the authorization level.

 \todo This type should also include the file authorization level (read/write),
 so it can be checked for commands like exeRemoveFile.  However, that is only
 useful when per-command authorization is implemented.
*/
typedef enum snmpAuth_e
{
  snmpAuthUndef = 0,       /*!< Authentication level is not defined. */
  snmpAuthNone,            /*!< No access permitted. */
  snmpAuthViewer,          /*!< Viewing is allowed, modification is not. */
  snmpAuthUser             /*!< Full access. */
} snmpAuth_t;

typedef enum
{
  portCom,
  portUsb,
  portIp,
  portWeb,
  portFtp,
  portFake,
  portNtrip,
  portIps,
  portBt,
  portUhf,
  portIpr,
  portDc,
  portOtg
} portType_t;

#pragma pack(pop)

/* External Variables/Structs -----------------------------------------------*/

/* External Procedures ------------------------------------------------------*/




#endif                                 /* SNMPTYPES_H */
/* END OF HEADER FILE =======================================================*/
