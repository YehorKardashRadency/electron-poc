/**
 *  \file     ssnsbfstream.h
 *  \ingroup  SSNSBFStream
 *  \brief    API of the SBF stream module, which provides easy manipulation of SBF files.
 *
 *  \par Copyright:
 *    (c) 2006 - 2008 Septentrio Satellite Navigation NV/SA, Belgium
 *
 *  \note Modifications made to an SBF stream will \b NOT modify the original
 *        SBF file used to open the SBF stream handle.
 *  \note None of the SBF stream module functions require a valid SSN license
 *        unless otherwise noted in the function description. A valid SSN
 *        SSN license handle is required to open an SBF stream handle.
 *
 *  The SBF stream module provides an easy way to read, write and manipulate an
 *  SBF stream by inserting, appending and removing SBF blocks.
 */

#ifndef SSNSBFSTREAM_H
/** To avoid multiple inclusions */
#define SSNSBFSTREAM_H 1

/* Includes ==(needed for self-contained / -consistent)=======================*/

#include "sbfdef.h"         /* SBF definitions */
#include "ssnerror.h"       /* SSN error module */
#include "ssnhandle.h"      /* SSN safe handle */
#include "ssnsdk.h"         /* SSN SDK module */
#include "ssntypes.h"       /* SSN types */

#ifdef __cplusplus
extern "C" {
#endif

/* Declarations ==============================================================*/

/* Constants & Macros --------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/** SBF stream handle */
typedef ssn_hhandle_t ssn_hsbfstream_t;

/** SBF stream merge options */
typedef enum
{
  SSNSBFSTREAM_MERGEOPTION_NONE           = 0x00000000, /**< No selection (no blocks will be included) */
  SSNSBFSTREAM_MERGEOPTION_ALL            = 0x01000000, /**< Merge all types */
  SSNSBFSTREAM_MERGEOPTION_DISCNAVAPP     = 0x02000000, /**< Discard navigation applicability (all nav blocks will be included) */

  SSNSBFSTREAM_MERGEOPTION_MEASUREMENTS   = 0x00000001, /**< Include all measurement blocks */
  SSNSBFSTREAM_MERGEOPTION_NAVPAGES       = 0x00000002, /**< Include all navigation pages */
  SSNSBFSTREAM_MERGEOPTION_GPSDECODED     = 0x00000004, /**< Include all GPS decoded messages */
  SSNSBFSTREAM_MERGEOPTION_GLODECODED     = 0x00000008, /**< Include all GLONASS decoded messages */
  SSNSBFSTREAM_MERGEOPTION_GALDECODED     = 0x00000010, /**< Include all Galileo decoded messages */
  SSNSBFSTREAM_MERGEOPTION_GEODECODED     = 0x00000020, /**< Include all SBAS decoded messages */
  SSNSBFSTREAM_MERGEOPTION_PVT            = 0x00000040, /**< Include all PVT blocks */
  SSNSBFSTREAM_MERGEOPTION_ATTITUDE       = 0x00000080, /**< Include all attitude blocks */
  SSNSBFSTREAM_MERGEOPTION_RECEIVERTIME   = 0x00000100, /**< Include all receiver time blocks */
  SSNSBFSTREAM_MERGEOPTION_EXTEVENT       = 0x00000200, /**< Include all external event blocks */
  SSNSBFSTREAM_MERGEOPTION_DIFFCORR       = 0x00000400, /**< Include all differenatial corrections blocks */
  SSNSBFSTREAM_MERGEOPTION_STATUS         = 0x00000800, /**< Include all status blocks */
  SSNSBFSTREAM_MERGEOPTION_MISC           = 0x00001000, /**< Include all miscellaneous blocks */
  SSNSBFSTREAM_MERGEOPTION_EXTSENSORMEAS  = 0x00002000, /**< Include all external sensor blocks */
  SSNSBFSTREAM_MERGEOPTION_INTEGRATEDPVT  = 0x00004000, /**< Include all integrated PVT blocks */
  SSNSBFSTREAM_MERGEOPTION_TUR            = 0x00008000, /**< Include all TUR specific blocks */
  SSNSBFSTREAM_MERGEOPTION_BDSDECODED     = 0x00010000, /**< Include all BDS decoded messages */
  SSNSBFSTREAM_MERGEOPTION_QZSDECODED     = 0x00020000, /**< Include all QZSS decoded messages */
  SSNSBFSTREAM_MERGEOPTION_LBAND          = 0x00040000, /**< Include all L-Band Demodulator messages */
  SSNSBFSTREAM_MERGEOPTION_PPGISRX        = 0x00080000, /**< Include all PinPoint-GIS RX messages */
} ssn_sbfstream_mergeoption_t;

/** SBF stream crop options */
typedef enum
{
  SSNSBFSTREAM_CROPOPTION_DEFAULT         = 0x00000001, /**< Default options. */
  SSNSBFSTREAM_CROPOPTION_DISCARDNAVAPP   = 0x00000002, /**< Do not take into account the navigation applicability. */
  SSNSBFSTREAM_CROPOPTION_DISCARDINVALID  = 0x00000004  /**< Do not include SBF blocks with invalid time stamp. */
} ssn_sbfstream_cropoption_t;

/** Processing interval in milli-seconds */
typedef enum
{
  SSNSBFSTREAM_INTERVAL_00010     = 10,     /**< 10 milli-seconds. */
  SSNSBFSTREAM_INTERVAL_00020     = 20,     /**< 20 milli-seconds. */
  SSNSBFSTREAM_INTERVAL_00050     = 50,     /**< 50 milli-seconds. */
  SSNSBFSTREAM_INTERVAL_00100     = 100,    /**< 100 milli-seconds. */
  SSNSBFSTREAM_INTERVAL_00200     = 200,    /**< 200 milli-seconds. */
  SSNSBFSTREAM_INTERVAL_00500     = 500,    /**< 500 milli-seconds. */
  SSNSBFSTREAM_INTERVAL_01000     = 1000,   /**< 1 second. */
  SSNSBFSTREAM_INTERVAL_02000     = 2000,   /**< 2 seconds. */
  SSNSBFSTREAM_INTERVAL_03000     = 3000,   /**< 3 seconds. */
  SSNSBFSTREAM_INTERVAL_04000     = 4000,   /**< 4 seconds. */
  SSNSBFSTREAM_INTERVAL_05000     = 5000,   /**< 5 seconds. */
  SSNSBFSTREAM_INTERVAL_06000     = 6000,   /**< 6 seconds. */
  SSNSBFSTREAM_INTERVAL_10000     = 10000,  /**< 10 seconds. */
  SSNSBFSTREAM_INTERVAL_15000     = 15000,  /**< 15 seconds. */
  SSNSBFSTREAM_INTERVAL_20000     = 20000,  /**< 20 seconds. */
  SSNSBFSTREAM_INTERVAL_30000     = 30000,  /**< 30 seconds. */
  SSNSBFSTREAM_INTERVAL_ONCHANGE  = 1       /**< On change. */
} ssn_sbfstream_interval_t;

/** RTCM versions. */
typedef enum
{
  SSNSBFSTREAM_RTCM_DEFAULT = 1, /**< Use default RTCM version. */
  SSNSBFSTREAM_RTCM_2       = 2, /**< RTCM version 2 */
  SSNSBFSTREAM_RTCM_3       = 4  /**< RTCM version 3 */
} ssn_sbfstream_rtcmversion_t;

/** RTCM message ID's. */
typedef enum
{
  SSNSBFSTREAM_RTCMV2_MESSAGE_DEFAULT  = 0x00000002, /**< Default RTCMv2 messages */
  SSNSBFSTREAM_RTCMV2_MESSAGE_ALL      DEPRECATED_ENUM("This value is deprecated and will be removed in a future version.")      
                                       = 0x00000002, /**< All RTCMv2 messages (deprecated) */
  SSNSBFSTREAM_RTCMV2_MESSAGE_DGPS_RTK = 0x00200010, /**< RTCMv2 DGPS+RTK messages */

  SSNSBFSTREAM_RTCMV2_MESSAGE_1        = 0x00000004, /**< RTCMv2 message  1    : Differential GPS Correction */
  SSNSBFSTREAM_RTCMV2_MESSAGE_3        = 0x00000008, /**< RTCMv2 message  3    : GPS Reference Station Parameters */
  SSNSBFSTREAM_RTCMV2_MESSAGE_18AND19  = 0x00000010, /**< RTCMv2 message 18+19 : RTK Uncorrected Carrier Phases (18) and Pseudoranges (19) */
  SSNSBFSTREAM_RTCMV2_MESSAGE_22       = 0x00000020, /**< RTCMv2 message 22    : Extended Reference Station Parameters */
  SSNSBFSTREAM_RTCMV2_MESSAGE_23AND24  = 0x00200000, /**< RTCMv2 message 23+24 : Antenna Descriptor and Reference Station ARP parameter */

  /*** !!RTCM VERSION 2 AND VERSION 3 CANNOT BE COMBINED!! ***/
  /*** HENCE THE BITFIELDS ABOVE AND BELOW CAN BE THE SAME ***/

  SSNSBFSTREAM_RTCMV3_MESSAGE_DEFAULT  = 0x00000001, /**< Default RTCMv3 messages */
  SSNSBFSTREAM_RTCMV3_MESSAGE_ALL      DEPRECATED_ENUM("This value is deprecated and will be removed in a future version.")     
                                       = 0x00000001, /**< All RTCMv3 messages (deprecated) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_LEGACY   = 0x06902280, /**< RTCMv3 Legacy messages */

  SSNSBFSTREAM_RTCMV3_MESSAGE_1003     = 0x00000040, /**< RTCMv3 message 1003 : GPS Basic RTK, L1&L2 Observables */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1004     = 0x00000080, /**< RTCMv3 message 1004 : GPS Extended RTK, L1&L2 Observables */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1005     = 0x00000100, /**< RTCMv3 message 1005 : Stationary RTK Reference Station ARP */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1006     = 0x00000200, /**< RTCMv3 message 1006 : Stationary RTK Reference Station ARP With Antenna Height */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1009     = 0x00000400, /**< RTCMv3 message 1009 : (deprecated) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1010     = 0x00000800, /**< RTCMv3 message 1010 : (deprecated) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1011     = 0x00001000, /**< RTCMv3 message 1011 : GLONASS basic RTK, L1 & L2 */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1012     = 0x00002000, /**< RTCMv3 message 1012 : GLONASS extended RTK, L1 & L2 */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1014     = 0x00004000, /**< RTCMv3 message 1014 : (not supported) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1021     = 0x00008000, /**< RTCMv3 message 1021 : (not supported) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1015     = 0x00010000, /**< RTCMv3 message 1015 : (not supported) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1022     = 0x00020000, /**< RTCMv3 message 1022 : (not supported) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1016     = 0x00040000, /**< RTCMv3 message 1016 : (not supported) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1023     = 0x00080000, /**< RTCMv3 message 1023 : (not supported) */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1007     = 0x00100000, /**< RTCMv3 message 1007 : Antenna Descriptor */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1084     = 0x00400000, /**< RTCMv3 message 1084 : GLONASS MSM4 */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1124     = 0x00800000, /**< RTCMv3 message 1124 : BeiDou MSM4 */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1074     = 0x01000000, /**< RTCMv3 message 1074 : GPS MSM4 */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1094     = 0x02000000, /**< RTCMv3 message 1094 : Galileo MSM4 */
  SSNSBFSTREAM_RTCMV3_MESSAGE_1033     = 0x04000000, /**< RTCMv3 message 1033 : Receiver and Antenna Descriptors */
} ssn_sbfstream_rtcmmessage_t;

/** SBF stream reference options. */
typedef enum
{
  SSNSBFSTREAM_REFOPTION_DEFAULT                        = 0x00000001, /**< Default options (nothing set). */
  SSNSBFSTREAM_REFOPTION_REMOVEDIFFCORR                 = 0x00000002, /**< Remove DIFFCORR blocks already present. */
  SSNSBFSTREAM_REFOPTION_USEROVER                       = 0x00000004, /**< Use rover station (only applies to DGPS). */
  SSNSBFSTREAM_REFOPTION_USEBASE                        = 0x00000008, /**< Use base station (only applies to DGPS). */
  SSNSBFSTREAM_REFOPTION_MOVINGBASE                     = 0x00000010, /**< Indicate that reference stream is a moving base */
  SSNSBFSTREAM_REFOPTION_DISABLE_NAV_PRELOAD            = 0x00000020, /**< Disable pre-loading of all navigation blocks from input files */
  SSNSBFSTREAM_REFOPTION_DISABLE_ROVER_BASE_NAV_SHARING = 0x00000040  /**< If unset, base can use the nav data from the rover; and rover
                                                                        can use the nav data from the base */
} ssn_sbfstream_refoption_t;

/** SBF stream open options */
typedef enum
{
  SSNSBFSTREAM_OPENOPTION_READONLY  = 0,  /**< Open SBF stream for read only */
  SSNSBFSTREAM_OPENOPTION_READWRITE       /**< Open SBF stream for read-write */
} ssn_sbfstream_openoption_t;

/** SBF stream progress callback function list */
typedef enum
{
  SSNSBFSTREAM_PROGRESSCB_FLIST_NONE                    = 0x00000000, /**< None */
  SSNSBFSTREAM_PROGRESSCB_FLIST_LOADFILE                = 0x00000001, /**< SSNSBFStream_loadFile() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_COPYFILE                = 0x00000002, /**< SSNSBFStream_copy() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_WRITEFILE               = 0x00000004, /**< SSNSBFStream_writeToFile() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_APPENDSTREAM            = 0x00000008, /**< SSNSBFStream_appendStreamBlocks() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_REMOVEBLOCKS            = 0x00000010, /**< SSNSBFStream_removeBlocks() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_REMOVEBLOCKBYTIME       = 0x00000020, /**< SSNSBFStream_removeBlockByTime() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_TRANSLATECOMMANDS       = 0x00000040, /**< SSNSBFStream_translateCommands() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_INSERTENDOF             = 0x00000080, /**< SSNSBFStream_insertEndOfBlocks() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_GETNUMBEROFBLOCKS       = 0x00000100, /**< SSNSBFStream_getNumberOfBlocks() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_GETSTREAMINTERVAL       = 0x00000200, /**< SSNSBFStream_getStreamInterval() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_CROPGNSS                = 0x00000400, /**< SSNSBFStream_cropGNSS() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_CROPTOW                 = 0x00000800, /**< SSNSBFStream_cropTOW() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_FILTERGNSS              = 0x00001000, /**< SSNSBFStream_filterGNSS() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_FILTERTOW               = 0x00002000, /**< SSNSBFStream_filterTOW() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_FILTERID                = 0x00004000, /**< SSNSBFStream_filterID() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_SAMPLE                  = 0x00008000, /**< SSNSBFStream_sample() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_GETCOMMONEPOCHINTERVAL  = 0x00010000, /**< SSNSBFStream_getCommonEpochInterval() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_INSERTREFERENCESTREAM   = 0x00020000, /**< SSNSBFStream_insertReferenceStream() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_MERGE                   = 0x00040000, /**< SSNSBFStream_merge() */

  SSNSBFSTREAM_PROGRESSCB_FLIST_SBFANALYZE_GETPVTMODEPERCENTAGES  = 0x01000000, /**< SSNSBFAnalyze_getPVTModePercentages() */
  SSNSBFSTREAM_PROGRESSCB_FLIST_SBFANALYZE_GETPVTERRORPERCENTAGES = 0x02000000, /**< SSNSBFAnalyze_getPVTErrorPercentages() */

  SSNSBFSTREAM_PROGRESSCB_FLIST_ALL                     = 0x7FFFFFFF  /**< All */
} ssn_sbfstream_progresscb_flist_t;

/**
 *  \brief  SBF stream progress callback function
 *
 *  \param fitem      [in]  Defines the function name which called this callback function
 *  \param percentage [in]  Current progress percentage.
 *
 *  A callback function used by SBF stream functions which might take a long
 *  time to process to indicate the current progress percentage.
 *
 *  \return void
 */
typedef void (*ssn_sbfstream_progresscb_t)(ssn_sbfstream_progresscb_flist_t fitem, float percentage);

/**
*  \brief  SBF stream progress callback function with data pointer
*
*  \param fitem      [in]  Defines the function name which called this callback function
*  \param percentage [in]  Current progress percentage.
*  \param userdata   [in]  User Data pointer
*
*  A callback function used by SBF stream functions which might take a long
*  time to process to indicate the current progress percentage.
*
*  \return void
*/
typedef void(*ssn_sbfstream_userdata_progresscb_t)(ssn_sbfstream_progresscb_flist_t fitem, float percentage, void* userdata);

/* Public Variables/Structs --------------------------------------------------*/

/* Public Procedures ---------------------------------------------------------*/

/**
 *  \brief  Open an SBF stream
 *
 *  \param  ssnsdkhandle      [in]  The SSN SDK handle
 *  \param  sbfstreamhandle   [out] The SBF stream handle which will hold the SBF data
 *
 *  \note Not all SBF stream functions require a valid SDK license. The validity
 *        of the SDK license handle will only be checked in the functions that
 *        require it.
 *  \note When an error occurs in one of the functions all opened handles
 *        should be closed by calling their \p close() function to free any
 *        allocated memory and to cleanup the handle.
 *
 *  Open and initialize an empty SBF stream handle.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_open(ssn_hsdk_t        ssnsdkhandle,
                  ssn_hsbfstream_t *sbfstreamhandle);

/**
 *  \brief  Load an SBF file into the SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  filename        [in]  The name of the SBF file
 *  \param  openoptions     [in]  SBF stream open options
 *
 *  Read in an existing file to be used as the SBF stream handle object.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_loadFile(ssn_hsbfstream_t            sbfstreamhandle,
                      char                       *filename,
                      ssn_sbfstream_openoption_t  openoptions);

/**
 *  \brief  Close an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle to close
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  Close the SBF stream.\n
 *  Close the working copy of the original SBF file and free the allocated
 *  memory.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_close(ssn_hsbfstream_t sbfstreamhandle);

/**
 *  \brief  Validate an SBF stream handle
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle to validate
 *
 *  Check if an SBF stream handle is valid and can be used.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_validate(ssn_hsbfstream_t sbfstreamhandle);

/**
 *  \brief  Delete the contents of an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle to clean
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post \p sbfstreamhandle points to an empty SBF stream
 *
 *  It is sometimes convenient to use one SBF stream handle for multiple operations.
 *  Since it would be time and resource consuming to close and create a new SBF stream
 *  each time, it is possible to clean an existing SBF stream.
 *  The SBF stream will be empty after cleanup and data can be stored into it.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_clean(ssn_hsbfstream_t sbfstreamhandle);

/**
 *  \brief  Copy the contents of one SBF stream into another SBF stream
 *
 *  \param  sbfstreamsource [in]  The SBF stream that holds the data to be copied
 *  \param  sbfstreamtarget [out] The SBF stream where the data will be copied into
 *
 *  \note The target SBF stream should either be a newly created and empty SBF
 *        stream or, if it is an existing handle, be cleaned with
 *        \p SbfStream_clean() before it is passed to this function.
 *
 *  \pre  \p sbfstreamsource should not be \p NULL
 *  \pre  \p sbfstreamtarget should not be \p NULL
 *
 *  \post \p sbfstreamtarget should be identical to \p sbfstreamsource
 *
 *  Copy the contents of one SBF stream into another SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_copy(ssn_hsbfstream_t  sbfstreamsource,
                  ssn_hsbfstream_t  sbfstreamtarget);

/**
 *  \brief  Crop an SBF stream between two GNSS timestamps
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream to crop
 *  \param  gnssstart       [in]      The GNSS time stamp (in seconds) from where to start
 *  \param  gnssend         [in]      The GNSS time stamp (in seconds) where to end
 *  \param  cropoption      [in]      SBF stream crop options
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post \p sbfstreamhandle contains the SBF blocks between epoch \p gnssstart
 *        and the first occurrence of \p gnssend
 *
 *  Crop an SBF stream between two GNSS timestamps.\n
 *  If gnssstart is set to its "do-not-use" value (\p F64_NOTVALID) cropping will
 *  start from the beginning of the SBF stream.\n
 *  If gnssend is set to its "do-not-use" value (\p F64_NOTVALID) cropping will end
 *  at the end of the SBF stream.
 *
\verbatim
+-------+-------+-------+-------+-------+
| GNSS1 | GNSS2 | GNSS3 | GNSS1 | GNSS2 |
+-------+-------+-------+-------+-------+
\endverbatim
*
*  When cropped between \p GNSS1 and \p GNSS2 only the first occurrences of
 *  \p GNSS1 and \p GNSS2 will be included.
 *
 *  By default navigation data is checked for the time of applicability.
 *  If a navigation block is present before \p gnssstart or after \p gnssend  and 
 *  it is applicable on the cropped section, the block will be included in the 
 *  resulting SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_cropGNSS(ssn_hsbfstream_t            sbfstreamhandle,
                      double                      gnssstart,
                      double                      gnssend,
                      ssn_sbfstream_cropoption_t  cropoption);

/**
 *  \brief  Crop an SBF stream using the TOW values
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream to crop
 *  \param  towstart        [in]      The TOW (in seconds) from where to start
 *  \param  wncstart        [in]      The WNc value that belongs to the TOW from where to start
 *  \param  towend          [in]      The TOW (in seconds) where to end
 *  \param  wncend          [in]      The WNc value that belongs to the TOW where to end
 *  \param  cropoption      [in]      SBF stream crop options
 *
 *  \note By default, the navigation data will be checked for its applicability.
 *  \note When \p SSNSBFStream_cropGNSS() will be called the progress callback
 *        ID of \p SSNSBFStream_cropGNSS() has to be enabled to request progress
 *        output.
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p tostart is not \p NULL
 *  \pre  \p towend is not \p NULL
 *
 *  \post \p sbfstreamhandle contains the SBF blocks with a TOW value between
 *        epoch \p towstart and \p towend
 *
 *  Crop an SBF stream using the TOW values. If both the TOW and WNc values are
 *  specified, the GNSS timestamp will be calculated and \p SSNSBFStream_cropGNSS()
 *  will be used.
 *  If the WNc values are set to their "do-not-use" values (\p U16_NOTVALID) only the
 *  TOW values will be used.
 *
\verbatim
+------+------+------+------+------+
| TOW1 | TOW2 | TOW3 | TOW1 | TOW2 |
+------+------+------+------+------+
\endverbatim
*
*  Only the first occurrence of TOW1 until TOW2 will be included.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_cropTOW(ssn_hsbfstream_t           sbfstreamhandle,
                     uint32_t                   towstart,
                     uint16_t                   wncstart,
                     uint32_t                   towend,
                     uint16_t                   wncend,
                     ssn_sbfstream_cropoption_t cropoption);

/**
 *  \brief  Filter an SBF stream on all blocks between two GNSS times
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream handle
 *  \param  gnssstart       [in]      The GNSS time stamp (in seconds) from where to start
 *  \param  gnssend         [in]      The GNSS time stamp (in seconds) where to end
 *  \param  cropoption      [in]      SBF crop options
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p gnssstart and \p gnssend are not \p F64_NOTVALID
 *
 *  \post \p sbfstreamhandle contains only the SBF blocks wihin the given GNSS
 *        interval
 *
 *  Filter an SBF stream to include all the SBF blocks within a given GNSS
 *  interval.
 *
\verbatim
|--x1--x2--x3--x1--x2--x4--|
\endverbatim
*
*  If \p gnssstart equals \p x1 and \p gnssend equals \p x2 then the resulting
 *  SBF stream will contain both sections, unlike \p SbfStream_cropGNSS() which
 *  will only include the first interval.
 *
 *  By default navigation data is checked for the  applicability.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_filterGNSS(ssn_hsbfstream_t            sbfstreamhandle,
                        double                      gnssstart,
                        double                      gnssend,
                        ssn_sbfstream_cropoption_t  cropoption);

/**
 *  \brief  Filter an SBF stream on all blocks between two TOW values
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream to filter
 *  \param  towstart        [in]      TOW (in seconds) from where to start
 *  \param  wncstart        [in]      WNc from where to start
 *  \param  towend          [in]      TOW (in seconds) where to end
 *  \param  wncend          [in]      WNc where to end
 *  \param  cropoption      [in]      SBF stream crop options
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  Both \p towstart and \p towend are not \p U32_NOTVALID
 *
 *  \post \p sbfstreamhandle contains the filtered SBF stream
 *
 *  Filter an SBF stream to include all blocks from a given start TOW value to
 *  a given end TOW value. If both WNc values are provided the GNSS time stamp
 *  will be computed and \p SbfStream_filterGNSS() will be called.
 *
\verbatim
|--x1--x2--x3--x1--x2--x4--|
\endverbatim
*
*  If \p x1 and \p x2 are provided as TOW values, both sections will be
 *  included in the resulting SBF stream, unlike \p SbfStream_cropTOW() where
 *  only the first section will be included.
 *
 *  By default navigation data is check for the applicability.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_filterTOW(ssn_hsbfstream_t           sbfstreamhandle,
                       uint32_t                   towstart,
                       uint16_t                   wncstart,
                       uint32_t                   towend,
                       uint16_t                   wncend,
                       ssn_sbfstream_cropoption_t cropoption);

/**
 *  \brief  Filter an SBF stream on SBF id
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream handle
 *  \param  sbfid           [in]      The SBF id to filter on
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  Filter an SBF stream so it only contains the given SBF id. All other blocks
 *  will be removed from the stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_filterID(ssn_hsbfstream_t  sbfstreamhandle,
                      SBFID_t           sbfid);

/**
 *  \brief  Move the stream pointer to the end of an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream to forward
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post The file-position indicator shall be placed at the end of the SBF
 *        stream
 *
 *  Forward the file-position indicator to the end of the SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_forward(ssn_hsbfstream_t sbfstreamhandle);

/**
 *  \brief  Move the stream pointer to the beginning of an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream to rewind
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post The file-position indicator shall be placed at the beginning of the
 *        SBF stream
 *
 *  Rewind an SBF stream so operations performed will be started from the
 *  beginning of the SBF stream
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_rewind(ssn_hsbfstream_t sbfstreamhandle);

/**
 *  \brief  Wait on next block
 *
 *  \param  sbfstreamhandle [in]  The SBF stream
 *  \param  wait            [in]  Whether to wait or not
 *  \param  factor          [in]  Waiting interval factor
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  This function is related to \p SbfStream_getNextBlock() and
 *  \p SbfStream_getNextBlockByID(). By default, these functions return a new
 *  SBF block when requested.\n
 *  Setting the \p wait variable to \p true will make these functions
 *  wait when sending the next SBF block.
 *
 *  The time to wait is the time between the current epoch and the previous
 *  epoch subtracted with the processing time between the current function
 *  call and the previous function call.
 *
 *  The \p factor value is used to speed up the waiting process. To play an SBF
 *  stream at the recording speed, set the factor to \p 1.0. The \p factor value
 *  is limited from \p 0.1 to \p 100.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_waitOnNextBlock(ssn_hsbfstream_t sbfstreamhandle,
                             bool             wait,
                             double           factor);

/**
 *  \brief  Set the offset to get the next block
 *
 *  \param  sbfstreamhandle [in]  The SBF stream
 *  \param  offset          [in]  The offset to get the next block
 *
 *  This function  makes that each time offset number of blocks are skipped
 *  when using the functions to get a block from the SBF stream.
 *  The result is that not the next block will be returned but the x'th+1 next
 *  block when the offset is set to x.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_setNextBlockOffset(ssn_hsbfstream_t  sbfstreamhandle,
                                uint8_t           offset);

/**
 *  \brief  Get the size of an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream
 *  \param  size            [out] The size of the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post \p size contains the length of the SBF stream
 *
 *  Get the size of an SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getSize(ssn_hsbfstream_t   sbfstreamhandle,
                     uint32_t          *size);

/**
 *  \brief  Get the current position in the SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream
 *  \param  position        [out] The position in the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post \p position contains the current value of the file-position indicator
 *        in the SBF stream
 *
 *  This function works more or less like the ISO-C function "ftell()" and will
 *  return the current value of the file-position indicator in the current SBF
 *  stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getPosition(ssn_hsbfstream_t   sbfstreamhandle,
                         uint32_t          *position);

/**
 *  \brief  Sets the current position in the SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream
 *  \param  position        [out] The position in the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t 
SSNSBFStream_setPosition(ssn_hsbfstream_t  sbfstreamhandle,
                         uint32_t          position);

/**
 *  \brief  Save the current position in an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle from which the position needs to be saved
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \note If a position is saved and modifications are made to the SBF stream
 *        before restoring the position it is likely that the saved position
 *        will no longer be correct.
 *
 *  Save the current value of the file-position indicator in the SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_positionSave(ssn_hsbfstream_t sbfstreamhandle);

/**
 *  \brief  Restore a previously saved position in an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream where to restore a previously saved position
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  Restore the previously saved file-position indicator in the SBF stream.
 *
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_positionRestore(ssn_hsbfstream_t sbfstreamhandle);

/**
 *  \brief  Get the number of blocks that occur for a specified SBF block ID
 *
 *  \param  sbfstreamhandle [in]  The SBF stream to analyze
 *  \param  sbfid           [in]  The ID of the SBF block to check for
 *  \param  rewind          [in]  Start counting from the beginning of the stream
 *  \param  nbrofblocks     [out] The total number of blocks
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post \p nbrofblocks contains the number of valid SBF blocks present in the
 *        SBF stream
 *
 *  Analyze an SBF stream and count the number of times an SBF block with a
 *  specified SBF block ID occurs.
 *  If all the blocks have to be taken into account, use \p sbfid_ALL.
 *  If \p rewind is set to \p true all the blocks in the SBF stream will be
 *  counted, otherwise only the blocks that follow the current position in the
 *  SBF stream will be taken into account.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getNumberOfBlocks(ssn_hsbfstream_t   sbfstreamhandle,
                               SBFID_t            sbfid,
                               bool               rewind,
                               int               *nbrofblocks);


/**
*  \brief  Get the position of the first occurrence for a specified SBF block ID
*
*  \param  sbfstreamhandle [in]  The SBF stream to analyze
*  \param  sbfid           [in]  The ID of the SBF block to the get the first occurrence of
*  \param  position        [out] The first position of the block or U64_NOTVALID if the block is not found
*
*  \pre  \p sbfstreamhandle is not \p NULL
*
*  \post \p position contains the first position of the block or U64_NOTVALID if the block is not found
*
*  Analyze an SBF stream and find the first occurrence of an SBF block.
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNSBFStream_getFirstOccurenceOfBlock(ssn_hsbfstream_t   sbfstreamhandle,
                                      SBFID_t            sbfid,
                                      uint64_t          *position);


/**
 *  \brief  Check the validity of an SBF block
 *
 *  \param  sbfstreamhandle [in]  The SBF stream the block belongs to
 *  \param  voidblock       [in]  The SBF block
 *  \param  validity        [out] The validity
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *
 *  \post \p validity contains \p true or \p false
 *
 *  The header of an SBF block contains a CRC value. This value is checked
 *  against the expected CRC value for the block.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_checkBlockValidity(ssn_hsbfstream_t  sbfstreamhandle,
                                VoidBlock_t      *voidblock,
                                bool             *validity);

/**
 *  \brief  Compute the GNSS timestamp of an SBF block
 *
 *  \param  sbfstreamhandle [in]  The SBF stream the SBF block belongs to
 *  \param   voidblock      [in]  The SBF block to compute the GNSS time from
 *  \param  gnsstime        [out] The GNSS timestamp (in seconds) of the SBF block
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *
 *  \post \p gnsstime contains the GNSS timestamp of the SBF block
 *
 *  \note For navigation data, the returned GNSS time stamp is the start of the
 *        block applicability.
 *
 *  Compute the GNSS timestamp of an SBF block.
 *  As stated in the SBF definition, SBF blocks contain a timestamp. For most
 *  SBF blocks this is stored in the TOW and WNc fields. From these two values
 *  a more general GNSS timestamp can be calculated.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_computeGNSSTime(ssn_hsbfstream_t   sbfstreamhandle,
                             VoidBlock_t       *voidblock,
                             double            *gnsstime);

/**
 *  \brief  Get the lowest and highest GNSS time value
 *
 *  \param  sbfstreamhandle [in]  The SBF stream to analyze
 *  \param  gnsslow         [out] The lowest GNSS time (in seconds) present in the SBF stream
 *  \param  gnsshigh        [out] The highest GNSS time (in seconds) present in the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post \p gnsslow contains the lowest GNSS time in the SBF stream
 *  \post \p gnsshigh contains the highest GNSS time in the SBF stream
 *
 *  Compute the lowest and highest GNSS time (in seconds) present in the SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getStreamInterval(ssn_hsbfstream_t   sbfstreamhandle,
                               double            *gnsslow,
                               double            *gnsshigh);

/**
 *  \brief  Get the lowest and highest GNSS time value of the measurements blocks
 *
 *  \param  sbfstreamhandle [in]  The SBF stream to analyze
 *  \param  gnsslow         [out] The lowest GNSS time (in seconds) present in the SBF stream
 *  \param  gnsshigh        [out] The highest GNSS time (in seconds) present in the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post \p gnsslow contains the lowest GNSS time in the SBF stream
 *  \post \p gnsshigh contains the highest GNSS time in the SBF stream
 *
 *  Compute the lowest and highest GNSS time (in seconds) of the measurement blocks present in the
 *  SBF stream by reading the start and end of the file.
 *
 *  \note this function assumes that the time is increasing in the file
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getStreamMeasurementsInterval(ssn_hsbfstream_t   sbfstreamhandle,
                                           double            *gnsslow,
                                           double            *gnsshigh);


/**
 *  \brief  Append an SBF block at the end of an SBF stream
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream where the block needs to be appended to
 *  \param  voidblock       [in]      The SBF block that needs to be appended to the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *
 *  \post The \p voidblock has been appended to the \p sbfstreamhandle
 *
 *  Append an SBF block at the end of an SBF stream (CRC is validated for the appended block).
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_appendBlock(ssn_hsbfstream_t   sbfstreamhandle,
                         VoidBlock_t       *voidblock);
/**
 *  \brief  Append a group made of many SBF block at the end of an SBF stream
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream where the block needs to be appended to
 *  \param  data            [in]      The SBF block that needs to be appended to the SBF stream
 *  \param  length          [in]      Length of the data to be added (in bytes)
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p data is not \p NULL
 *
 *  \post The \p data has been appended to the \p sbfstreamhandle
 *
 *  Append SBF blocks at the end of an SBF stream. NO checks are made, blindly copy the data at the end of the stream !!
 *  Used internally in the encoder for PPSDK
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_appendManyBlocks(ssn_hsbfstream_t   sbfstreamhandle,
			      void *data, int length);

/**
 *  \brief  Append SBF blocks with a specified ID from one SBF stream to another SBF stream
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream where the other SBF stream needs to be appended to
 *  \param  sbfstreamappend [in]      The SBF stream that needs to be appended to another SBF stream
 *  \param  sbfid           [in]      The ID of the SBF blocks that need to be appended
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p sbfstreamappend is not \p NULL
 *
 *  \post All the SBF blocks with ID \p sbfid from SBF stream \p sbfstreamappend
 *        are appended to \p sbfstreamhandle
 *
 *  Append SBF blocks with a specified ID from one SBF stream to another SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_appendStreamBlocks(ssn_hsbfstream_t  sbfstreamhandle,
                                ssn_hsbfstream_t  sbfstreamappend,
                                SBFID_t           sbfid);

/**
 *  \brief  Remove all SBF blocks with a specified SBF ID
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream where the SBF blocks need to be removed from
 *  \param  sbfid           [in]      The ID of the SBF blocks (w.o. revision) that needs to be removed from the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \post All the SBF blocks with ID \p sbfid have been removed from
 *        \p sbfstreamhandle
 *
 *  Remove all SBF blocks with the specified SBF ID from an SBF stream
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_removeBlocks(ssn_hsbfstream_t  sbfstreamhandle,
                          SBFID_t           sbfid);

/**
 *  \brief  Remove all SBF blocks with a specified SBF ID and GNSS time
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream where the SBF blocks need to be removed from
 *  \param  sbfid           [in]      The ID of the SBF blocks that need to be removed from the SBF stream
 *  \param  gnsstime        [in]      The GNSS time (in seconds) of the SBF blocks that need to be removed
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p gnsstime is not \p NULL
 *
 *  \post All SBF blocks with ID \p sbfid and GNSS timestamp \p gnsstime have been
 *        removed from \p sbfstreamhandle
 *
 *  Remove all the SBF blocks with the specified SBF block ID and GNSS time from
 *  an SBF stream. If \p sbfid_ALL is specified as the SBF block ID all the blocks
 *  with the specified GNSS time will be removed from the SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_removeBlockByTime(ssn_hsbfstream_t sbfstreamhandle,
                               SBFID_t          sbfid,
                               double           gnsstime);

/**
 *  \brief  Insert an SBF block at a specified GNSS time
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream where the SBF block has to be inserted into
 *  \param  gnsstime        [in]      The GNSS time (in seconds) where the block should be inserted
 *  \param  voidblock       [in]      The SBF block that needs to be inserted
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p gnsstime is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *
 *  \post \p sbfstreamhandle will contain \p voidblock at GNSS time \p gnsstime
 *
 *  Insert an SBF block at a specified GNSS time.\n
 *  The SBF block will be inserted before the first SBF block that has a GNSS
 *  time larger than the specified one.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_insertBlock(ssn_hsbfstream_t   sbfstreamhandle,
                         double             gnsstime,
                         VoidBlock_t       *voidblock);

/**
 *  \brief  Get the next SBF block from an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream that holds the SBF blocks
 *  \param  voidblock       [out] The next SBF block from the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *  \pre  \p voidblock is large enough to contain the next SBF block.
 *        When unsure about the size of this SBF block, it is recommended
 *        to use MAX_SBFSIZE (see sbfdef.h).
 *
 *  \post \p voidblock contains the next SBF block from the SBF stream
 *
 *  \note If an invalid SBF block is encountered (invalid CRC value) the next
 *        valid block will be returned. The function
 *        SSNSBFStream_getNextBlockCRCCheck() will return a warning if an
 *        invalid SBF block has been encountered.
 *
 *  Get the next SBF block from an SBF stream
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getNextBlock(ssn_hsbfstream_t  sbfstreamhandle,
                          VoidBlock_t      *voidblock);
/**
 *  \brief  Get the previous SBF block from an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream that holds the SBF blocks
 *  \param  voidblock       [out] The previous SBF block from the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *  \pre  \p voidblock is large enough to contain the previous SBF block.
 *        When unsure about the size of this SBF block, it is recommended
 *        to use MAX_SBFSIZE (see sbfdef.h).
 *
 *  \post \p voidblock contains the previous SBF block from the SBF stream
 *
 *  \note If an invalid SBF block is encountered (invalid CRC value) the
 *        previous valid block will be returned. The function
 *        SSNSBFStream_getNextBlockCRCCheck() will return a warning if an
 *        invalid SBF block has been encountered.
 *
 *  Get the previous SBF block from an SBF stream
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getPrevBlock(ssn_hsbfstream_t  sbfstreamhandle,
                          VoidBlock_t      *voidblock);


/**
 *  \brief  Get the next SBF block from an SBF stream and notify on CRC error
 *
 *  \param  sbfstreamhandle [in]  The SBF stream that holds the SBF blocks
 *  \param  voidblock       [out] The next SBF block from the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *  \pre  \p voidblock is large enough to contain the next SBF block.
 *        When unsure about the size of this SBF block, it is recommended
 *        to use MAX_SBFSIZE (see sbfdef.h).
 *
 *  \post \p voidblock contains the next SBF block from the SBF stream
 *
 *  Get the next SBF block from an SBF stream but return a warning if an
 *  invalid SBF block had been encountered. The \p voidblock variable will
 *  however contain the <em>next valid SBF block</em>.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getNextBlockCRCCheck(ssn_hsbfstream_t  sbfstreamhandle,
                                  VoidBlock_t      *voidblock);

/**
 *  \brief  Get the next SBF block with a specified ID from an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream that holds the SBF blocks
 *  \param  sbfid           [in]  The ID of the next SBF block to fetch
 *  \param  voidblock       [out] The next SBF block from the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *  \pre  \p voidblock is large enough to contain the next SBF block with ID \p sbfid.
 *        When unsure about the size of this SBF block, it is recommended
 *        to use MAX_SBFSIZE (see sbfdef.h).
 *
 *  \post \p voidblock contains the next SBF block with ID \p sbfid from the SBF
 *        stream
 *
 *  Get the next SBF block with a specified SBF block ID from an SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getNextBlockByID(ssn_hsbfstream_t  sbfstreamhandle,
                              SBFID_t           sbfid,
                              VoidBlock_t      *voidblock);

/**
 *  \brief  Get the previous SBF block with a specified ID from an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream that holds the SBF blocks
 *  \param  sbfid           [in]  The ID of the previous SBF block to fetch
 *  \param  voidblock       [out] The previous SBF block from the SBF stream
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *  \pre  \p voidblock is large enough to contain the previous SBF block with ID \p sbfid.
 *        When unsure about the size of this SBF block, it is recommended
 *        to use MAX_SBFSIZE (see sbfdef.h).
 *
 *  \post \p voidblock contains the previous SBF block with ID \p sbfid from the SBF
 *        stream
 *
 *  Get the previous SBF block with a specified SBF block ID from an SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getPrevBlockByID(ssn_hsbfstream_t  sbfstreamhandle,
                              SBFID_t           sbfid,
                              VoidBlock_t      *voidblock);

/**
 *  \brief  Get the next SBF block at a given GNSS time
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  gnsstime        [in]  GNSS time of the requested SBF block (in seconds)
 *  \param  voidblock       [out] The SBF block
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p voidblock is not \p NULL
 *  \pre  \p voidblock is large enough to contain the next SBF block.
 *        When unsure about the size of this SBF block, it is recommended
 *        to use MAX_SBFSIZE (see sbfdef.h).
 *
 *  Get the next SBF block from an SBF stream where the GNSS time stamp equals
 *  the given GNSS time stamp or the first block after the given GNSS time stamp
 *  if no block is present with the given GNSS time stamp.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getNextBlockByGNSSTime(ssn_hsbfstream_t  sbfstreamhandle,
                                    double            gnsstime,
                                    VoidBlock_t      *voidblock);

/**
 *  \brief  Sample an SBF stream
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream to filter
 *  \param  interval        [in]      The processing rate
 *  \param  relative        [in]      Use absolute time or relative time.
 *
 *  \note When the \p relative parameter is set to \p true the interval between
 *        the first two valid \p MeasEpoch SBF blocks will be computed. This
 *        will then be used to change the interval comparison.
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p interval is not \p NULL
 *
 *  \post All SBF blocks who are not within the specified \p interval are removed
 *        from the SBF stream
 *
 *  Sample an SBF stream and remove all the SBF blocks that do not match the
 *  specified processing interval.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_sample(ssn_hsbfstream_t          sbfstreamhandle,
                    ssn_sbfstream_interval_t  interval,
                    bool                      relative);

/**
 *  \brief  Merge the contents of two SBF streams
 *
 *  \param  sbfstream_1     [in]  The first SBF stream
 *  \param  sbfstream_2     [in]  The second SBF stream
 *  \param  mergeoption_1   [in]  Merge options for the first SBF stream
 *  \param  mergeoption_2   [in]  Merge options for the second SBF stream
 *  \param  sbfstreammerged [out] The SBF stream holding the merged result
 *
 *  \pre  \p sbfstream_1 is not \p NULL
 *  \pre  \p sbfstream_2 is not \p NULL
 *
 *  \post \p sbfstreammerged contains data from both \p sbfstream_1 and \p sbfstream_2
 *
 *  Merge the contents of two SBF stream using the data specified by the merge
 *  options. sbfstream_1 and sbfstream_2 are rewind before operation.
 *  sbfstreammerged is rewind after operation.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_merge(ssn_hsbfstream_t             sbfstream_1,
                   ssn_hsbfstream_t             sbfstream_2,
                   ssn_sbfstream_mergeoption_t  mergeoption_1,
                   ssn_sbfstream_mergeoption_t  mergeoption_2,
                   ssn_hsbfstream_t             sbfstreammerged);

/**
 *  \brief  Insert an ASCII command into an SBF stream
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  gnsstime        [in]  The GNSS time where to insert the ASCII command
 *  \param  asciicommand    [in]  The ASCII command string
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p gnsstime is not \p F64_NOTVALID
 *  \pre  \p asciicommand is not \p NULL
 *
 *  \post An SBF block containing the ASCII command will be inserted into the SBF
 *        stream
 *
 *  Convert an ASCII command into an SNMP command and create an SBF commands
 *  block containing the command. The SBF block will then be inserted into the
 *  SBF stream at the given GNSS time.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_insertCommandOverTime(ssn_hsbfstream_t   sbfstreamhandle,
                                   double             gnsstime,
                                   char              *asciicommand);

/**
 *  \brief  Insert ASCII commands contained in a file at a given time
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream handle
 *  \param  filename        [in]      The name of the ASCII text file containing the commands
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p filename is not \p NULL
 *
 *  \post \p sbfstreamhandle contains SBF command blocks with the converted ASCII
 *        commands
 *
 *  Convert ASCII commands stored in an ASCII text file into SBF command blocks
 *  and insert them at the given GNSS time (seconds).
 *
 *  \par File Layout
 *    The ASCII text file will contain the GNSS time in seconds, followed by a
 *    space (" "), followed by the ASCII command.
 *    Every ASCII command must be preceded by the GNSS time. For Example:
\verbatim
80045567.2 sso, stream1, FIL1, pvtgeodetic+diffcorr, onchange
80045567.2 snu, GPSL1CA
80045601.4 sso, stream1, FIL1, GUI, onchange
\endverbatim
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_insertFileCommandOverTime(ssn_hsbfstream_t   sbfstreamhandle,
                                       char              *filename);

/**
 *  \brief  Set reference antenna data
 *
 *  \param  sbfstreamhandle [in/out]  An SBF stream
 *  \param  anttype         [in]      IGS name of antenna type
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *
 *  \note If anttype == NULL 
 *
 *  Override the anttype which will be used by the
 *  \p SSNSBFStream_insertReferenceStream() function as such it has to be
 *  called before the insertion.\n
 *  By default these values will be retrieved from a Receiver Status SBF
 *  block unless otherwise specified.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_setReferenceAntenna(ssn_hsbfstream_t  sbfstreamhandle,
                                 const char       *anttype);

/**
 *  \brief  Get reference antenna
 *
 *  \param  sbfstreamhandle [in]  SBF stream handle
 *  \param  anttype         [out] IGS name of antenna type
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p anttype is not \p NULL
 *
 *  Get the current reference antenna. If no reference antenna is set
 *  the value of anttype will be empty string.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getReferenceAntenna(ssn_hsbfstream_t  sbfstreamhandle,
                                 char             *anttype);


/**
*  \brief  Set reference marker position data
*
*  \param  sbfstreamhandle [in/out]  An SBF stream
*  \param  x               [in]      X coordinate
*  \param  y               [in]      Y coordinate
*  \param  z               [in]      Z coordinate
*
*  \pre  \p sbfstreamhandle is not \p NULL
*
*  \note We assume the datum format used is WGS84.
*  \note The X, Y and Z coordinates are expected to be Cartesian.
*
*  Override the X, Y and Z marker position coordinate which will be used by the
*  \p SSNSBFStream_insertReferenceStream() function as such it has to be
*  called before the insertion.\n
*  By default these values will be retrieved from a Cartesian or Geodetic SBF
*  block unless otherwise specified.
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNSBFStream_setReferencePosition(ssn_hsbfstream_t  sbfstreamhandle,
                                  double             x,
                                  double             y,
                                  double             z);

/**
*  \brief  Get reference marker position
*
*  \param  sbfstreamhandle [in]  SBF stream handle
*  \param  x               [out] X value
*  \param  y               [out] Y value
*  \param  z               [out] Z value
*
*  \pre  \p sbfstreamhandle is not \p NULL
*
*  \note We assume the datum format used is WGS84.
*
*  Get the current reference marker position. If no valid reference position is set
*  the value of \p x, \p y and \p z will be \p F64_NOTVALID.
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNSBFStream_getReferencePosition(ssn_hsbfstream_t  sbfstreamhandle,
                                  double           *x,
                                  double           *y,
                                  double           *z);

/**
*  \brief  Set reference antenna offset
*
*  \param  sbfstreamhandle [in/out]  An SBF stream
*  \param  e               [in]      East offset component
*  \param  n               [in]      North offset component
*  \param  u               [in]      Up offset component
*
*  \pre  \p sbfstreamhandle is not \p NULL
*
*  Override the E, N and Up antenna offset components which will be used by the
*  \p SSNSBFStream_insertReferenceStream() function to calculate the ARP.
*  This function has to be called before the insertion.\n
*  If this function is not called the values will be retrieved from a ReceiverSetup SBF
*  block unless the the reference position is set manually with
*  \p SSNSBFStream_setReferencePosition in which case they are set to 0.
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
*/

FW_EXPORT ssn_error_t
SSNSBFStream_setReferenceAntennaOffset(ssn_hsbfstream_t  sbfstreamhandle,
                                       double             e,
                                       double             n,
                                       double             u);

/**
*  \brief  Get reference antenna offset
*
*  \param  sbfstreamhandle [in]  SBF stream handle
*  \param  e               [out] East offset component
*  \param  n               [out] North offset component
*  \param  u               [out] Up offset component
*
*  \pre  \p sbfstreamhandle is not \p NULL
*
*  Get the current reference antenna offset. If no valid reference antenna offset is set
*  the value of \p e, \p n and \p u will be \p F64_NOTVALID.
*
\return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNSBFStream_getReferenceAntennaOffset(ssn_hsbfstream_t  sbfstreamhandle,
                                       double           *e,
                                       double           *n,
                                       double           *u);

/**
 *  \brief  Insert a reference SBF stream
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream
 *  \param  referencestream [in]      The SBF stream containing the reference data
 *  \param  referenceid     [in]      The reference ID to identify the reference data
 *  \param  version         [in]      RTCM version
 *  \param  messages        [in]      RTCM messages
 *  \param  options         [in]      RTCM related options
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p referencestream is not \p NULL
 *
 *  \post \p sbfstreamhandle will include RTCM data generated from
 *        \p referencestream
 *
 *  \note By default RTCMv3 messages will be created.
 *  \note This function requires a valid SSN license handle.
 *
 *  When including a reference SBF stream into another SBF stream, the reference
 *  position data is required. This can either be stored in the SBF blocks
 *  PVTCartesian or PVTGeodetic (which are created when converting RINEX data
 *  into SBF data) or the position data can be set by the user via the
 *  \p SSNSBFStream_setReferencePosition() function. If this is set by the user the
 *  position data in a \p PVTGeodetic or \p PVTCartesian SBF block will be ignored.
 *
 *  In both request of DGPS and/or RTK messages the PVT for the measurements in the referencestream
 *  are re-computed when calling this function. This is done so that the proper Differential Corrections 
 *  can be inserted to obtain DGPS/RTK solution. Note however that not all measurements in the referencestream 
 *  are re-computed but only those within a range of 5 minutes before and 5 minutes after 
 *  of the common epochs between the referencestream and the original sbfstreamhandle stream.
 *
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_insertReferenceStream(ssn_hsbfstream_t             sbfstreamhandle,
                                   ssn_hsbfstream_t             referencestream,
                                   int32_t                      referenceid,
                                   ssn_sbfstream_rtcmversion_t  version,
                                   ssn_sbfstream_rtcmmessage_t  messages,
                                   ssn_sbfstream_refoption_t    options);

/**
 *  \brief  Write the contents of an SBF stream to an SBF file
 *
 *  \param  sbfstreamhandle [in]  The SBF stream
 *  \param  filename        [in]  The name of the SBF file where the SBF stream contents needs to be saved into
 *
 *  \pre  \p sbfstreamhandle is not \p NULL
 *  \pre  \p filename is not \p NULL
 *
 *  \post The contents of \p sbfstreamhandle has been written into a binary file
 *
 *  Write the contents of an SBF stream to an SBF file.\n
 *  Any modifications or manipulations done to an SBF stream can be saved when
 *  using this function.\n
 *  If a file with the same name already exists, that file will be overwritten.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_writeToFile(ssn_hsbfstream_t   sbfstreamhandle,
                         char              *filename);

/**
 *  \brief  Get the most common delta between epochs
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  sbfid           [in]  The SBF id to search for
 *  \param  interval        [out] The most common epoch interval
 *
 *  \note Only the first 100 different delta possibilities are taken into
 *        account.
 *
 *  This function searches for the most common delta (difference between two
 *  epochs of SBF blocks with the given SBF id).
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getCommonEpochInterval(ssn_hsbfstream_t  sbfstreamhandle,
                                    SBFID_t           sbfid,
                                    double           *interval);

/**
 *  \brief  Get the next missing epoch for a given SBF ID.
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle.
 *  \param  sbfid           [in]  The SBF id to check.
 *  \param  interval        [in]  The most common epoch interval.
 *  \param  gnsstime        [out] The GNSS time of a missing epoch.
 *
 *  This function searches for the next missing epoch of a given SBF id given the most common interval.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getNextMissingEpoch(ssn_hsbfstream_t   sbfstreamhandle,
                                 SBFID_t            sbfid,
                                 double             interval,
                                 double            *gnsstime);

/**
 *  \brief  Insert an EndOf block
 *
 *  \param  sbfstreamhandle [in] The SBF stream handle
 *
 *  Insert EndOf SBF blocks at the end of each epoch containing PVT, Measurement or Attitude data.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_insertEndOfBlocks(ssn_hsbfstream_t sbfstreamhandle);

/**
 *  \brief  Translate the commands present in an SBF file
 *
 *  \param  sbfstreamhandle [in/out]  The SBF stream handle
 *  \param  asn1filename    [in]      Name of the ASN.1 file
 *  \param  buffersize      [in/out]  Size of the \p replystring buffer
 *  \param  replystring     [out]     The reply message
 *
 *  \note This function uses the so called "double-call" mechanism. When the
 *        function is called the first time, pass \p NULL as the \p replystring
 *        parameter to obtain the number of bytes that need to be allocated to
 *        store the reply string.
 *        It is recommended to set buffersize to the size of the allocated memory
 *        before the second call.
 *
 *  Translate the commands present in the SBF command block in an SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_translateCommands(ssn_hsbfstream_t   sbfstreamhandle,
                               const char        *asn1filename,
                               size_t            *buffersize,
                               char              *replystring);

/**
 *  \brief  Get the next common epoch section
 *
 *  \param  sbfstream1    [in]  Handle to the first SBF stream
 *  \param  sbfstream2    [in]  Handle to the second SBF stream
 *  \param  gnsstimestart [out] Start of the section (GNSS time in seconds)
 *  \param  gnsstimeend   [out] End of the section (GNSS time in seconds)
 *  \param  commonepochs  [out] Number of common epochs in this section
 *
 *  Get the next section where common MeasEpoch 2.0 blocks occur.
 *  Note that it is possible this function reaches the end of an SBF stream
 *  whilst a valid section has been found. Check the \p commonepochs variable.
 *
 *  \par Example
\code
error = SSNSBFStream_getNextCommonEpochSection(
          sbfstream1, sbfstream2, &start, &end, &ce);
while (SSNERROR_GETCODE(error) == SSNERROR_WARNING_OK) {
  // Print result
  fprintf(stdout, "Section from %lf to %lf (%d common epochs),
          start, end, (int)ce);

  // Search for next section
  error = SSNSBFStream_getNextCommonEpochSection(
            sbfstream1, sbfstream2, &start, &end, &ce);
}

// It is possible a section was found but and "END OF STREAM" occurred
// So we need to check the "ce" variable.
if (ce > 0) {
  fprintf(stdout, "Section from %lf to %lf (%d common epochs),
          start, end, (int)ce);
}
\endcode
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getNextCommonEpochSection(ssn_hsbfstream_t   sbfstream1,
                                       ssn_hsbfstream_t   sbfstream2,
                                       double            *gnsstimestart,
                                       double            *gnsstimeend,
                                       uint32_t          *commonepochs);

/**
 *  \brief  Check if the given SBF stream handle is empty
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle to check
 *
 *  Check if the given SBF stream handle contains an empty SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_isStreamEmpty(ssn_hsbfstream_t   sbfstreamhandle);

/**
 *  \brief  Set or reset the callback function
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
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
SSNSBFStream_pcSetCallback(ssn_hsbfstream_t           sbfstreamhandle,
                           ssn_sbfstream_progresscb_t callback);

/**
*  \brief  Set or reset the callback function with a userdata pointer
*
*  \param  sbfstreamhandle [in]  The SBF stream handle
*  \param  callback        [in]  The callback function or \p NULL
*  \param  userdata        [in]  The pointer that should be returned with the callback or \p NULL
*
*  Set the progress callback function which should be used to report the
*  current progress. Pass \p NULL to reset the currently selected progress
*  callback function. The passed userdata pointer is returned as third argument
*  of the callback function
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNSBFStream_pcSetUserDataCallback(ssn_hsbfstream_t                     sbfstreamhandle,
                                   ssn_sbfstream_userdata_progresscb_t  callback,
                                   void                                *userdata);

/**
 *  \brief  Subscribe a function to the progress callback
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  function        [in]  The ID of the function
 *
 *  Subscribe a function to report its progress using the specified callback
 *  function. Pass \p SSNSBFSTREAM_PROGRESSCB_FLIST_NONE to reset any subscribed
 *  function.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_pcSubscribe(ssn_hsbfstream_t                 sbfstreamhandle,
                         ssn_sbfstream_progresscb_flist_t function);

/**
 *  \brief  Unsubscribe a previously subscribed function
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
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
SSNSBFStream_pcUnsubscribe(ssn_hsbfstream_t                 sbfstreamhandle,
                           ssn_sbfstream_progresscb_flist_t function);

/**
 *  \brief  Check whether a given function is subscribed
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
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
SSNSBFStream_pcIsSubscribed(ssn_hsbfstream_t                  sbfstreamhandle,
                            ssn_sbfstream_progresscb_flist_t  function,
                            bool                             *issubscribed);

/**
 *  \brief  Set the leap second to use
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  leapsecond      [in]  The leap second to use
 *
 *  Set the leap second to use during post processing of the internal reference file. 
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
SSNSBFStream_setLeapSecond(ssn_hsbfstream_t sbfstreamhandle,
                           int8_t          leapsecond);

/**
 *  \brief  Whether or not to get only one leap second
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  getonlyonce     [in]  Whether or not to get it only once
 *
 *  By default the leap second to use - if not provided - is only computed once
 *  before inserting a reference stream. Pass \p false if the leap second should
 *  be detected for every block in the SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_getOnlyOneLeapSecond(ssn_hsbfstream_t  sbfstreamhandle,
                                  bool              getonlyonce);

/**
 *  \brief  Insert a GPS UTC SBF block
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  leapsecond      [in]  The leap second
 *  \param  gnsstime        [in]  (optional) The GNSS time (seconds) where to insert the SBF block,
 *                                           (F64_NOTVALID = not specified)
 *  \param  remove          [in]  (optional) Whether or not to remove any existing GPS UTC SBF blocks
 *
 *  Insert a GPS UTC block in the SBF stream.
 *  If \p gnsstime is not given it will look for the first existing GPS UTC SBF
 *  block present in the SBF stream and replace the block.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFStream_setGPSUTCBlock(ssn_hsbfstream_t  sbfstreamhandle,
                            int8_t            leapsecond,
                            double            gnsstime,
                            bool              remove);

/**
 *  \brief add pointer to escape variable to monitor escape
 *
 *  \param  sbfstreamhandle [in]  The post processing engine handle
 *  \param  pescape         [in]  The pointer to the esc value
 *
 *  When a pointer different from NULL is used the calculations will stop as soon 
 *  as value equals true.                 
 */
FW_EXPORT void
SSNSBFStream_setEscapePointer(ssn_hsbfstream_t  sbfstreamhandle,
                              bool              *pescape);

/**
 *  \brief  check if sbfstream was escaped
 *
 *  \param  sbfstreamhandle [in]  The sbf stream handle
 *
 *  \return Returns true if stream was escaped. 
 */
FW_EXPORT bool
SSNSBFStream_isEscaped(ssn_hsbfstream_t  sbfstreamhandle);

#ifdef __cplusplus
}
#endif

#endif
/* END OF HEADER FILE ========================================================*/
