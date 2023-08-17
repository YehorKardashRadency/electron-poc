/**
 *  \file     ssnppengine.h
 *  \ingroup  SSNPPEngine
 *  \brief    API of the SSN Post Processing Engine
 *
 *  \par Copyright:
 *    (c) 2006 - 2008 Septentrio Satellite Navigation NV/SA, Belgium
 *
 *  \note All functions in this module require a valid SSN license
 *
 *  The Post Processing Engine is the core of the Post Processing SDK.\n
 *  Its main functionality is the computation of a PVT solution.
 */
#ifndef SSNPPENGINE_H
/** To avoid multiple inclusions */
#define SSNPPENGINE_H 1

/* Includes ==(needed for self-contained / -consistent)=======================*/
#include "sbfdef.h"       /* SBF definition */
#include "ssnerror.h"     /* SSN error module */
#include "ssnhandle.h"    /* SSN safe handle */
#include "ssnsdk.h"       /* SSN SDK module */
#include "ssnsbfstream.h" /* SBF stream module */
#include "ssntypes.h"     /* SSN types */

#include <stddef.h>       /* size_t */

#if 0

#include "ssn_sigilstruct.h"     /* generated RTCM3 SIGIL definition */

#else /* TEMPORARY      ======================================================*/

#ifndef SSNSIGILSTRUCT_H
#define SSNSIGILSTRUCT_H 1

#pragma pack(push, 4)

typedef struct ssnRTCM3_SIGIL_1_s
{
  uint8_t        Preamble;
  uint8_t        Reserved;
  uint16_t       Message_Length;
  uint16_t       Message_Number;
  uint16_t       SSN_ID;
  uint32_t       TOW;
  uint16_t       WNc;
  uint16_t       Status;
  uint8_t        Bit_0;
  uint8_t        Bit_1;
  uint8_t        Bit_2;
  uint8_t        Bit_14;
  uint8_t        Bit_15;
  int64_t        X;
  int64_t        Y;
  int64_t        Z;
  uint8_t        Datum;
  int32_t        Vx;
  int32_t        Vy;
  int32_t        Vz;
  uint16_t       DTOW;
  int32_t        DeltaX;
  int32_t        DeltaY;
  int32_t        DeltaZ;
  uint8_t        CRC[3];
} ssnRTCM3_SIGIL_1_t;

typedef struct ssnRTCM3_SIGIL_2_s
{
  uint8_t        Preamble;
  uint8_t        Reserved;
  uint16_t       Message_Length;
  uint16_t       Message_Number;
  uint16_t       SSN_ID;
  uint32_t       TOW;
  uint16_t       WNc;
  uint16_t       Status;
  uint8_t        Bit_0;
  uint8_t        Bit_1;
  uint8_t        Bit_2;
  uint32_t       Sigma_xx;
  uint32_t       Sigma_yy;
  uint32_t       Sigma_zz;
  int32_t        Rho_xy;
  int32_t        Rho_xz;
  int32_t        Rho_yz;
  uint32_t       Sigma_VxVx;
  uint32_t       Sigma_VyVy;
  uint32_t       Sigma_VzVz;
  int32_t        Rho_VxVy;
  int32_t        Rho_VxVz;
  int32_t        Rho_VyVz;
  uint32_t       Sigma_DeltaXDeltaX;
  uint32_t       Sigma_DeltaYDeltaY;
  uint32_t       Sigma_DeltaZDeltaZ;
  int32_t        Rho_DeltaXDeltaY;
  int32_t        Rho_DeltaXDeltaZ;
  int32_t        Rho_DeltaYDeltaZ;
  uint8_t        CRC[3];
} ssnRTCM3_SIGIL_2_t;

#pragma pack(pop)

#endif

#if 1 /* depricated types, enums, ... ======================*/

#define ssnRTCM3_ELC_1_s                  ssnRTCM3_SIGIL_1_s
#define ssnRTCM3_ELC_1_t                  ssnRTCM3_SIGIL_1_t
#define ssnRTCM3_ELC_2_s                  ssnRTCM3_SIGIL_2_s
#define ssnRTCM3_ELC_2_t                  ssnRTCM3_SIGIL_2_t

#define ssn_ppengine_elcfeedback_s        ssn_ppengine_sigilfeedback_s
#define ssn_ppengine_elcfeedback_t        ssn_ppengine_sigilfeedback_t

#define ssn_ppengine_elcreturn_t          ssn_ppengine_sigilreturn_t
#define elcEr_Stop                        sigilEr_Stop
#define elcEr_Escape                      sigilEr_Escape
#define elcEr_FatalError                  sigilEr_FatalError
#define elcEr_ELCMaxEnties                sigilEr_SIGILMaxEnties
#define elcEv_ResetNavFilter              sigilEv_ResetNavFilter

#define ssn_ppengine_pvtelccb_t           ssn_ppengine_pvtsigilcb_t
#define SSNPPEngine_setELCCallBackonPVT   SSNPPEngine_setSIGILCallBackonPVT

#endif /*======================================= depricated */

#endif /*========================================================= TEMPORARY */

/* Declarations ==============================================================*/

/* Constants & Macros --------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/
#pragma pack(push, 4)

/** Post processing engine handle */
typedef ssn_hhandle_t ssn_hppengine_t;

/**
 * \brief Representation of the static solution with all its components.
 */
typedef struct ssn_ppengine_validsolution_s
{
  bool                  pvtIsValid;       /**< Valid PVT data available */
  bool                  utcIsValid;       /**< Valid UTC data available */

  ReceiverTime_1_0_t    receiverTime;     /**< Receivertime      (pvtIsValid &&) utcIsValid */
  PVTCartesian_2_2_t    pvtCartesian;     /**< PVTCartesian      pvtIsValid */
  PVTGeodetic_2_2_t     pvtGeodetic;      /**< PVTGeodetic       pvtIsValid */
  PosCovCartesian_1_0_t posCovCartesian;  /**< PosCovCartesian   pvtIsValid */
  PosCovGeodetic_1_0_t  posCovGeodetic;   /**< PosCovGeodetic    pvtIsValid */
  VelCovCartesian_1_0_t velCovCartesian;  /**< VelCovCartesian   pvtIsValid */
  VelCovGeodetic_1_0_t  velCovGeodetic;   /**< VelCovGeodetic    pvtIsValid */
  DOP_2_0_t             dop;              /**< DOP               pvtIsValid */
  PVTSatCartesian_1_1_t pvtSatCartesian;  /**< PVTSatCartesian   pvtIsValid */
  PVTResiduals_2_1_t    pvtResiduals;     /**< PVTResiduals      pvtIsValid */
  RAIMStatistics_2_0_t  raimStatistics;   /**< RAIMStatistics    pvtIsValic */
  GeoCorrections_1_0_t  geoCorrections;   /**< GEOCorrections    pvtIsValid */
  BaseLine_1_0_t        baseLine;         /**< BaseLine          pvtIsValid */
  GPSUtc_1_0_t          gpsUTC;           /**< GPSUtc            utcIsValid */
  EndOfPVT_1_0_t        endOfPvt;         /**< EndOfPVT          pvtIsValid */
} ssn_ppengine_validsolution_t;

/**
 * \brief SIGIL feedback through RTCM3 type messages.
 */
typedef struct ssn_ppengine_sigilfeedback_s
{
  bool                sigil1Valid;
  ssnRTCM3_SIGIL_1_t  sigil1DeltaPV;
  bool                sigil2Valid;
  ssnRTCM3_SIGIL_2_t  sigil2Correlation;
} ssn_ppengine_sigilfeedback_t;

/** Error/Event notification through SIGIL callback return value */
typedef enum
{
  sigilEr_Stop            =    -1, /* Normal interruption of calculations by SIGIL */
  sigilEr_Escape          =    -2, /* Escape mechanism triggered by client         */
  sigilEr_FatalError      =    -3, /* Fatal error in SIGIL stop calculation        */
  sigilEr_SIGILMaxEnties  =    -4, /* Not enough entries reserved in SIGIL buffer  */

  sigilEv_ResetNavFilter  = -1000, /* SIGIL asks for reset of GNSS nav filter      */
} ssn_ppengine_sigilreturn_t;

/** Post processing option flags. */
typedef enum
{
  SSNPPENGINE_OPTIONS_USENAVANY           = 0x0001, /**< Use all available navigation data blocks */
  SSNPPENGINE_OPTIONS_USENAVRAW           = 0x0002, /**< Use RAW navigation data */
  SSNPPENGINE_OPTIONS_USENAVDEC           = 0x0004, /**< Use decoded navigation data */
  SSNPPENGINE_OPTIONS_EXECMDS             = 0x0008, /**< Execute command SBF blocks */
  SSNPPENGINE_OPTIONS_ABORTCMDERR         = 0x0010, /**< Abort when a command fails */
  SSNPPENGINE_OPTIONS_PROCESS_BACKWARDS   = 0x0020, /**< Seek backwards in input SBF file */
  SSNPPENGINE_OPTIONS_DISABLE_NAV_PRELOAD = 0x0040, /**< Disable pre-loading of all navigation blocks from input files */
  SSNPPENGINE_OPTIONS_COMPATIBILITY       = 0x0080, /**< Comptibility mode with receiver (disable optimizations) */
  SSNPPENGINE_OPTIONS_SERIALIZE DEPRECATED_ENUM("Setting this option has no effect anymore")
                                          = 0x0100, /**< \deprecated  Setting this option has no effect anymore.
                                                         The functionality of serializing the PPEngine database
                                                         is now automatically done by the PPSDK. */
  SSNPPENGINE_OPTIONS_DESERIALIZE DEPRECATED_ENUM("Setting this option has no effect anymore")
                                          = 0x0200,  /**< \deprecated  Setting this option has no effect anymore.
                                                         The functionality of deserializing the PPEngine database
                                                         is now automatically done by the PPSDK. */
  SSNPPENGINE_OPTIONS_FAST                = 0x0400, /**< Fast processing, skips, if possible, some steps
                                                         that are used to improve PVT availability and accuracy.
                                                         Note that this functionality is experimental and may change
                                                         in the future"*/
} ssn_ppengine_options_t;

/** Post processing engine progress callback function list */
typedef enum
{
  SSNPPENGINE_PROGRESSCB_FLIST_NONE         = 0x00000000, /**< None */
  SSNPPENGINE_PROGRESSCB_FLIST_CALCULATEPVT = 0x00000001, /**< SSNPPEngine_calculatePVT() */

  SSNPPENGINE_PROGRESSCB_FLIST_ALL          = 0x7FFFFFFF, /**< All */
} ssn_ppengine_progresscb_flist_t;

/**
 *  \brief  Post Processing engine progress callback function
 *
 *  \param  fitem       [in]  Function ID
 *  \param  percentage  [in]  Current progress percentage
 *
 *  A callback function used by the PVT computation function to indicate the
 *  current progress percentage.
 *
 *  \return void
 */
typedef void (*ssn_ppengine_progresscb_t)(ssn_ppengine_progresscb_flist_t fitem, float percentage);

/**
*  \brief  Post Processing engine progress with user data pointer callback function
*
*  \param  fitem       [in]  Function ID
*  \param  percentage  [in]  Current progress percentage
*  \param  userData    [in]  User Data pointer
*
*  A callback function used by the PVT computation function to indicate the
*  current progress percentage.
*
*  \return void
*/
typedef void(*ssn_ppengine_userdata_progresscb_t)(ssn_ppengine_progresscb_flist_t fitem, float percentage, void *userData);

/**
 *  \brief  Post processing engine command callback function
 *
 *  \param  message [in] Command reply message
 *
 *  A callback function used by the PVT computation function to report the
 *  result of a command which might be executed during the PVT computation.
 *
 *  \return void
 */
typedef void (*ssn_ppengine_cmdcb_t)(const char *message);

/**
 *  \brief  Post processing engine SIGIL callback function
 *
 *  \param  pvtSIGILHandle              [in/out] handle at disposal of callback, may be NULL
 *  \param  pvtCurrentPVTIn             [in]     Position data at current PVT epoch
 *  \param  pvtInterval_ms              [in]     Expected PVT interval
 *  \param  pvtSIGILOutputBuffer        [out]    SIGIL feedback for upcomming interval
 *  \param  pvtSIGILOutputBufferEntries [in]     maximum number of entries in output buffer
 *
 *  A callback function used by the PVT computation function in order to get feedback for
 *  the Enhanced Loosely Coupled PVT calculation.
 *  Purpose is that SIGIL feedback is recalculated making use of the previous postprocessed
 *  enhanced position.
 *
 *  \return int number of entries returned (may be 0) or ssn_ppengine_sigilreturn_t error
 */
typedef int (*ssn_ppengine_pvtsigilcb_t)(
  void                         *pvtSIGILHandle,
  ssn_ppengine_validsolution_t *pvtCurrentPVTIn,
  int                           pvtInterval_ms,
  ssn_ppengine_sigilfeedback_t *pvtSIGILOutputBuffer,
  size_t                        pvtSIGILOutputBufferEntries
                  );

#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

/* Public Variables/Structs --------------------------------------------------*/

/* Public Procedures ---------------------------------------------------------*/

/**
 *  \brief  Open a new post processing engine handle
 *
 *  \param  ssnsdkhandle    [in]  The SSN SDK handle
 *  \param  ppenginehandle  [out] The new post processing engine handle
 *
 *  \pre  \p ssnsdkhandle is not \p NULL
 *  \pre  \p ppenginehandle is not \p NULL
 *
 *  \note When an error occurs in one of the functions all opened handles
 *        should be closed by calling their \p close() function to free any
 *        allocated memory and to cleanup the handle.
 *
 *  Create a new post processing engine handle.\n
 *  When this function is called, even if somewhere an error occurs, the post
 *  processing engine handle always needs to be closed by calling \p SSNPPEngine_close().
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_open(ssn_hsdk_t       ssnsdkhandle,
                 ssn_hppengine_t *ppenginehandle);

/**
 *  \brief  Close a post processing engine handle
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle to close
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *
 *  Close a post processing engine handle and free the allocated memory.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_close(ssn_hppengine_t ppenginehandle);

/**
 *  \brief  Get the version info of the entire PP-SDK
 *
 *  Return the name and the version information of the entire post processing
 *  software development kit and all the internal modules.
 *
 *  \return Returns the PP-SDK version information
 */
FW_EXPORT /*@null@*/ const char*
SSNPPEngine_getVersionInfo();

/**
 *  \brief  Validate a post processing engine handle
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle to validate
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *
 *  Check if a post processing engine handle is valid and can be used to perform
 *  PVT calculations.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_validate(ssn_hppengine_t  ppenginehandle);

/**
 *  \brief  Send an ASCII command to the post processing engine
 *
 *  \param  ppenginehandle  [in]      The post processing engine handle
 *  \param  asciicommand    [in]      The ASCII command
 *  \param  buffersize      [in/out]  The size of the reply string
 *  \param  replystring     [out]     The reply string
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *
 *  \note This function uses the so called "double-call" mechanism. Call this
 *        function twice, passing \p NULL as the reply string the first time to
 *        calculate the amount of memory that needs to be allocated to fit the
 *        reply string. It is recommended to set buffersize to the size of the
 *        allocated memory before the second call.
 *  \note If a buffer big enough is passed to the function the first call, the
 *        command will be executed and the reply string will be stored in the
 *        buffer.
 *  \note If a command is preceeded by a \p # sign it will be treated as a
 *        comment and the command will not be executed. The \p buffersize
 *        variable will be set to \p 0 and the \p replystring variable will be
 *        set to \p NULL.
 *
 *  The output message the command generates will be stored into the replyString.\n\n
 *  Note that this function will not clear any previous content of the replyString array.
 *  It will append the result to the array. It is the responsability of the user of this
 *  function to clear the array. If this is not done, each time the replyString is output
 *  it will also contain the result of all the previous commands.\n
 *  The reason for this behaviour is the implementation of the
 *  SSNPPEngine_sendFileCommands() function. This function will browse through a text
 *  file reading all the commands line per line and feed them to the
 *  SSNPPEngine_sendAsciiCommand() function.
 *
 *  \par Example:
\code
int   buffersize_1 = 0;
int   buffersize_2 = 0;
char *replystring;

error = PpEngine_sendAsciiCommand(ppenginehandle, "test_1", &buffersize_1, NULL);
error = PpEngine_sendAsciiCommand(ppenginehandle, "test_2", &buffersize_2, NULL);
replystring = (char*)malloc((size_t)(buffersize_1 + buffersize_2 + 2)); // +2 to store '\0'.
buffersize_1 += buffersize_2;

error = SSNPPEngine_sendAsciiCommand(ppenginehandle, "test_1", &buffersize_1, replystring);
//  replyString will contain:
//    $R? test_1: Invalid Command!
error = SSNPPEngine_sendAsciiCommand(ppenginehandle, "test_2", &buffersize_1, replystring);
//  replyString will contain:
//    $R? test_1: Invalid Command!
//    $R? test_2: Invalid Command!
\endcode
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_sendAsciiCommand(ssn_hppengine_t  ppenginehandle,
                             const char      *asciicommand,
                             size_t          *buffersize,
                             char            *replystring);

/**
 *  \brief  Send an ASCII text file with ASCII commands
 *
 *  \param  ppenginehandle  [in]      The post processing handle
 *  \param  filename        [in]      The name of the file containing the commands
 *  \param  buffersize      [in/out]  The size of the reply buffer
 *  \param  replystring     [out]     The reply string
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *  \pre  \p filename is not \p NULL
 *
 *  \note This function uses the so called "double-call" mechanism. Call this
 *        function twice, passing \p NULL as the reply string the first time to
 *        calculate the amount of memory that needs to be allocated to fit the
 *        reply string. It is recommended to set buffersize to the size of the
 *        allocated memory before the second call.
 *       The second call will execute the ASCII commands.
 *  \note If a command it preceeded by a \p # sign it will be treated as a
 *        comment and the command will not be executed.
 *
 *  Send and process an ASCII text file with ASCII commands.
 *
 *  \par Example
\code
int   buffersize = 0;
char  *replystring;

error = SSMPPEngine_sendFileCommands(ppenginehandle, "my_commands.txt", &buffersize, NULL);
replystring = (char*)malloc((size_t)(buffersize + 2)); // +2 to store '\0'
error = SSNPPEngine_sendFileCommands(ppenginehandle, "my_commands.txt", &buffersize, replystring);
\endcode
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_sendFileCommands(ssn_hppengine_t  ppenginehandle,
                             const char      *filename,
                             size_t          *buffersize,
                             char            *replystring);

/**
 *  \brief  Send an SNMP' command
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  snmp            [in]  The SNMP' command
 *  \param  result          [out] The SNMP' result
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *  \pre  \p snmp is not \p NULL
 *
 *  \post \p result contains the binary reply
 *
 *  The SNMP' interface used by the post processing engine is a binary Septentrio
 *  proprietary interface that is loosely based on SNMP' (Simple Network
 *  Management Protocol).\n
 *  The SNMP' interface has the following advantages:
 *    - Smaller footprint needed.
 *    - Less lines of code equals less % CPU time.
 *    - Applications that are already network managed can easily be modified or
 *      adapted to act as an SNMP' proxy-server.
 *
 *  SNMP' messages are limited to a maximum size of 2kByte. Each message consists
 *  of:
 *    - Message Header: contains data needed for synchronization of the binary
 *      data stream.
 *    - PDU (Protocol Data Unit): Contains the actual message in:
 *        - PDU Header: contains type of messages + eventual errors.
 *        - A number of variable bindings: Each variable binding represents an
 *          entry in the MIB. Each entry is identified by the OID (ObjectID)
 *          followed by a variable size buffer containing the actual data.
 *
 *  Within one SNMP' message any number (from 1 till 255) of variable bindings in
 *  any order can be used as long as the total length of the SNMP' message does
 *  not exceed the maximum size.
 *
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_sendSnmpCommand(ssn_hppengine_t   ppenginehandle,
                            uint8_t          *snmp,
                            uint8_t          *result);

/**
 *  \brief  Get the MIB description
 *
 *  \param  ppenginehandle  [in]      The post processing engine handle
 *  \param  buffersize      [in/out]  The size of the buffer
 *  \param  description     [out]     The MIB description
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *  \pre  \p buffersize is not \p NULL
 *
 *  \post \p description contains the MIB description in ASCII format
 *
 *  \note The result of this function will be appended to the \p description
 *        buffer. It is the responsibility of the user to make sure this buffer
 *        has enough free space.
 *  \note This function uses the so called "double-call" mechanism. Call this
 *        function twice, passing \p NULL as the reply string the first time to
 *        calculate the amount of memory that needs to be allocated to fit the
 *        reply string. It is recommended to set buffersize to the size of the
 *        allocated memory before the second call.
 *
 *  The post processing engine configuration is stored in a database called MIB
 *  (Management Information Base). There is a one to one relationship between
 *  the formal MIB description and the ASCII command line interface for all exe,
 *  get and set-commands. Contrary to the SNMP' format the actual MIB description
 *  used is fully SNMPv2 compliant.
 *
 *  \par Example:
\code
uint16_t  buffersize;
char     *replystring;

error = SSNPPEngine_getMIBDescription(ppenginehandle,
                                   &buffersize,
                                   NULL);

replystring = (char*)malloc((size_t)(buffersize + 1));  // +1 to make sure it's big enough
memset(replystring, 0, (size_t)(buffersize + 1));       // Make sure it's clear.

error = SSNPPEngine_getMIBDescription(ppenginehandle,
                                      &buffersize,
                                      replystring);
free(replystring); // Make sure to free the allocated memory.
\endcode
 *
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *         \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *             the function was executed successfully
 *         \li an error code describing the error
 *            (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_getMIBDescription(ssn_hppengine_t   ppenginehandle,
                              size_t           *buffersize,
                              char             *description);

/**
 *  \brief  Change the post processing engine measurement encoding and PVT
 *          computation/encoding interval
 *
 *  \param  ppenginehandle  [in/out]  The post processing engine handle
 *  \param  intmeas         [in]      The measurement encoding interval
 *  \param  intpvt          [in]      The PVT computation/encoding interval
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *
 *  \note This function allows the user to limit the Measurement ecoding
 *        and PVT computation/encoding to save CPU power. The \p intmeas
 *        and \p intpvt interval can affect the output rate of the Measurement
 *        and PVT SBF blocks as configured by the \p SendSBFOutput command
 *        since the \p SendSBFOutput intervals are always a subsampling of
 *        the encoding intervals.
 *  \note The set intervals are always checked against the intervals specified
 *        by the license.
 *  \note The intervals set in this function result in a subsampling of the
 *        measurements in the input file at the specified interval. So in
 *        case the input measurement interval is lower than the requested ones
 *        or in case there is no common denominator the resulting interval
 *        will be different from the requested ones. e.g.:
 *        <ul>
 *          <li> Input interval 5 sec, requested interval 1 sec: result = 5 sec interval</li>
 *          <li> Input interval 6 sec, requested interval 5 sec: result = 30 sec interval</li>
 *        </ul>
 *
 *  By default he SSNPPEngine_calculatePVT() function will use all SBF blocks
 *  present in an SBF file. This function allows one to set the interval when to
 *  encode measurement data and when to compute a PVT and encode PVT data.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_setInputInterval(ssn_hppengine_t          ppenginehandle,
                             ssn_sbfstream_interval_t intmeas,
                             ssn_sbfstream_interval_t intpvt);

/**
 *  \brief  Get the post processing engine measurement encoding and PVT
 *          computation/encoding interval
 *
 *  \param  ppenginehandle  [in]  The post processing handle
 *  \param  intmeas         [out] The measurement blocks encoding interval
 *  \param  intpvt          [out] The the pvt blocks computation/encoding interval
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *
 *  Get the interval in milli-seconds for the measurement encoding and pvt computation/encoding.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_getInputInterval(ssn_hppengine_t  ppenginehandle,
                             uint16_t        *intmeas,
                             uint16_t        *intpvt);

/**
 *  \brief  Calculate the PVT position
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  sbfstreamhandle [in]  The input SBF stream
 *  \param  options         [in]  Post processing engine options
 *  \param  cmdcb           [in]  The command reply callback
 *  \param  sbfstroutput    [out] The output SBF stream
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *  \pre  \p sbfstrinput is not \p NULL
 *  \pre  \p sbfstroutput is not \p NULL
 *
 *  \post \p sbfstroutput contains the SBF blocks generated by the PVT
 *        calculation functionality
 *
 *  \note Not all blocks are used when calculating a PVT. If they are requested
 *        as output they will be copied from the input SBF stream without any
 *        modifications made to them.
 *  \note If both \p PPENGINE_USENAVRAW and \p PPENGINE_USENAVDEC are set the
 *        \p PPENGINE_USENAVDEC will have a higher priority.
 *        If one of the options is set but no valid SBF blocks can be found of
 *        that type it will result in an invalid PVT.
 *  \note The SBF stream used to calculate the PVT will not be modified.
 *  \note Set the callback parameters to \p NULL if they should not be used.
 *
 *  The PVT calculation function will use the navigation and measurement SBF
 *  blocks to compute a PVT, taking into account the settings which have been
 *  applied when sending ASCII and/or SNMP' commands.
 *
 *  SBF supports two types of navigation data:
 *    \li RAW navigation data
 *    \li decoded navigation data
 *
 *  Both types are supported by the post processing engine however only one type
 *  can be used when calculating a PVT.
 *  By default the post processing engine will try to determine which type is
 *  available in the SBF file, favoring decoded navigation data above RAW
 *  navigation data if both are present.
 *
 *  An SBF file can also contain SBF blocks with SNMP' commands. These can be
 *  executed by the post processing engine at runtime by setting the
 *  corresponding option.
 *
 *  If no PVT can be calculated the function will return an error.
 *  If SSO command has not been set then PPSDK will output by default select GUI+Commands as blocks in the sbfstroutput (interval onchange).
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_calculatePVT(ssn_hppengine_t            ppenginehandle,
                         ssn_hsbfstream_t           sbfstreamhandle,
                         ssn_ppengine_options_t     options,
                         ssn_ppengine_cmdcb_t       cmdcb,
                         ssn_hsbfstream_t           sbfstroutput);

/**
 *  \brief  Get the last valid solution
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  validsolution   [out] The last valid solution
 *
 *  \pre  \p ppenginehandle is not \p NULL
 *
 *  \post \p validsolution contains the last valid solution
 *
 *  Get the last valid solution after a PVT calculation.
 *  \note Closing the PPEngine handle will clear the data. Save data first if required.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_getLastValidSolution(ssn_hppengine_t                ppenginehandle,
                                 ssn_ppengine_validsolution_t  *validsolution);

/**
 *  \brief  Set the leap second to use
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  leapsecond      [in]  The leap second to use
 *
 *  Set the leap second to use during post processing of the Rover file.
 *  If this is set the processing function will not look for an existing GPSUTC block or use a
 *  fallback table for prediction. If set to -128, then Leap seconds will be used only when
 *  UTC blocks are encountered in the SBF file.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_setLeapSecond(ssn_hppengine_t ppenginehandle,
                          int8_t         leapsecond);

/**
 *  \brief  Whether or not to get only one leap second
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  getonlyonce     [in]  Whether or not to get it only once
 *
 *  If the leap second has not been set by the user or the SBF file does not
 *  contain a GPSUTC SBF block the leap second will be computed using a table.
 *  By default the leap second to use is only computed once before processing.
 *  Pass \p false if the leap second should be detected for every block in the
 *  SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_getOnlyOneLeapSecond(ssn_hppengine_t  ppenginehandle,
                                 bool             getonlyonce);

/**
 *  \brief  Set or reset the callback function
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  callback        [in]  The callback function or \p NULL
 *
 *  Set the progress callback function which should be used to report the
 *  current progress. Pass \p NULL to reset the currently selected progress
 *  callback function.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_pcSetCallback(ssn_hppengine_t           ppenginehandle,
                          ssn_ppengine_progresscb_t callback);

/**
*  \brief  Set or reset the callback function with a userdata pointer
*
*  \param  ppenginehandle  [in]  The post processing engine handle
*  \param  callback        [in]  The callback function or \p NULL
*  \param  userdata        [in]  The pointer that should be returned with the callback or \p NULL
*
*  Set the progress callback function which should be used to report the
*  current progress. Pass \p NULL to reset the currently selected progress
*  callback function. The passed userdata pointer is returned as third argument of the callback function
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
*          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
*              the function was executed successfully
*          \li an error code describing the error
*             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNPPEngine_pcSetUserDataCallback(ssn_hppengine_t                     ppenginehandle,
                                  ssn_ppengine_userdata_progresscb_t  callback,
                                  void                               *userdata);

/**
 *  \brief  Subscribe a function to the progress callback
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  function        [in]  The ID of the function
 *
 *  Subscribe a function to report its progress using the specified callback
 *  function. Pass \p SSNPPENGINE_PROGRESSCB_FLIST_NONE to reset any subscribed
 *  function.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_pcSubscribe(ssn_hppengine_t                 ppenginehandle,
                        ssn_ppengine_progresscb_flist_t function);

/**
 *  \brief  Unsubscribe a previously subscribed function
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  function        [in]  The ID of the function
 *
 *  Unsubscribe a previously subscribed function from reporting its progress
 *  using the previously selected progress callback function.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_pcUnsubscribe(ssn_hppengine_t                 ppenginehandle,
                          ssn_ppengine_progresscb_flist_t function);

/**
 *  \brief  Check whether a given function is subscribed
 *
 *  \param  ppenginehandle  [in]  The post processing engine handle
 *  \param  function        [in]  The ID of the function
 *  \param  issubscribed    [out] True or false
 *
 *  Check whether a given function has been subscribed to report its progress
 *  using the previously selected progress callback function.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNPPEngine_pcIsSubscribed(ssn_hppengine_t                  ppenginehandle,
                           ssn_ppengine_progresscb_flist_t  function,
                           bool                            *issubscribed);

/**
 *  \brief  register SIGIL callback function on PVT calculations
 *
 *  \param  ppengine                       [in]  The post processing engine handle
 *  \param  pvtSIGILCallBack               [in]  The Callback function
 *  \param  pvtSIGILOutputBuffer           [in]  Preallocated buffer for the SIGIL feedback
 *  \param  pvtSIGILOutputMaxBufferEntries [in]  Number of entries allocated in buffer
 *  \param  pvtSIGILHandle                 [in]  Private handle for the callback (may be NULL)
 *
 *  Register the SIGIL callback function together with its prealocated data sets.
 *
 *  \return void
 */
FW_EXPORT void
SSNPPEngine_setSIGILCallBackonPVT(ssn_hppengine_t                ppengine,
                                  ssn_ppengine_pvtsigilcb_t      pvtSIGILCallBack,
                                  ssn_ppengine_sigilfeedback_t  *pvtSIGILOutputBuffer,
                                  size_t                         pvtSIGILOutputMaxBufferEntries,
                                  void                          *pvtSIGILHandle);

/**
 *  \brief add pointer to escape variable to monitor escape
 *
 *  \param  ppengine   [in]  The post processing engine handle
 *  \param  pescape    [in]  The pointer to the esc value
 *
 *  When a pointer different from NULL is used the calculations will stop as soon
 *  as value equals true.
 */
FW_EXPORT void
SSNPPEngine_setEscapePointer(ssn_hppengine_t               ppengine,
                             bool                         *pescape);

/**
 *  \brief check if ppengine was escaped
 *
 *  \param  ppengine [in]  The post processing handle
 *
 *  \return Returns true if stream was escaped.
 */
FW_EXPORT bool
SSNPPEngine_isEscaped(ssn_hppengine_t ppengine);


/**
 *  \brief set name for database to be used for (de)serialization
 *
 *  \param  name  [in]  The pathmname for the db (maximum length 255)
 *
 *  \return void.
 */
FW_EXPORT void
SSNPPengine_setDBName( const char *name );

/**
 *  \brief Reset the asserts and errors warning counters
 *
 *  \return void.
 */
FW_EXPORT void
SSNPPengine_ResetWarningCounters();

#ifdef __cplusplus
}
#endif

#endif
/* END OF HEADER FILE ========================================================*/
