/**
 *  \file     ssnerror.h
 *  \ingroup  SSNError
 *  \brief    Declaration of types, macros and functions used by the SSN Error
 *            module.
 *
 *  \par Copyright:
 *    (c) 2006 - 2009 Septentrio Satellite Navigation NV/SA, Belgium
 *
 *  These are the declarations of the types, macros and functions used by the
 *  SSN error module.\n
 *  It allows the creation of custom error messages and codes.
 */
#ifndef SSNERROR_H
/** To avoid multiple inclusions */
#define SSNERROR_H 1

/* Includes ==(needed for self-contained / -consistent)=======================*/

#include "ssntypes.h" /* SSN types */

/* Declarations ==============================================================*/

/**
\verbatim
  ssn_error_t is defined to be very similar to WIN32_HRESULTS ...

    ssn_error_t are 32 bit values layed out as follows:

      3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
      1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
     +-+-----------------------------+---------------+-+-------------+
     |S|            Module           |    Submodule  |G|   Code      |
     +-+-----------------------------+---------------+-+-------------+

  Where:

    S - Severity - indicates success/fail
      0 - Success
      1 - Fail

    Module - indicates the module that generated the error.

    Submodule - indicates the submodule that generated the error.

    G - General used code - indicates whether an error is general to all modules or not.
      0 - Private
      1 - General

    Code - indicates the id of the error.
\endverbatim
 */
typedef uint32_t ssn_error_t;

/* Constants & Macros --------------------------------------------------------*/

/** Multiple SSN error modules. */
typedef enum
{
  SSNERROR_MODULE_UNKNOWN,              /**< Module: Unknown */
  SSNERROR_MODULE_GENERAL,              /**< Module: General */
  SSNERROR_MODULE_PPENGINE,             /**< Module: Post processing engine */
  SSNERROR_MODULE_SBFSTREAM,            /**< Module: SBF stream */
  SSNERROR_MODULE_RNXDEC,               /**< Module: RINEX decoder */
  SSNERROR_MODULE_LICENSE,              /**< Module: License mechanism */
  SSNERROR_MODULE_SSNHANDLE,            /**< Module: SSN handle. */
  SSNERROR_MODULE_SSNLICENSE,           /**< Module: SSN License mechanism */
  SSNERROR_MODULE_SSNERROR,             /**< Module: SSN error */
  SSNERROR_MODULE_SSNSNMP,              /**< Module: SSN SNMP handle */
  SSNERROR_MODULE_SBFANALYZE,           /**< Module: SBF Analyze */
  SSNERROR_MODULE_SSNSDK,               /**< Module: SSN SDK */
  SSNERROR_MODULE_PPECOMPUTE,           /**< Module: PPE Compute */
  SSNERROR_MODULE_BASEFINDER,           /**< Module: BaseFinder */
  SSNERROR_MODULE_MAX                   /**< Maximum number of modules */
} ssn_error_modules_t;

/** Multiple SSN error submodules. */
typedef enum
{
  SSNERROR_SUBMODULE_UNKNOWN,           /**< Submodule: Unknown */
  SSNERROR_SUBMODULE_GENERAL,           /**< Submodule: General */
  SSNERROR_SUBMODULE_SBFSTREAM,         /**< Submodule: SBF stream */
  SSNERROR_SUBMODULE_RNXDEC,            /**< Submodule: RINEX decoder */
  SSNERROR_SUBMODULE_PPENGINE,          /**< Submodule: Post Processing engine */
  SSNERROR_SUBMODULE_RNX210,            /**< Submodule: RINEX 2.10 decoder */
  SSNERROR_SUBMODULE_RNX300,            /**< Submodule: RINEX 3.00 decoder */
  SSNERROR_SUBMODULE_LICENSE,           /**< Submodule: License mechamism */
  SSNERROR_SUBMODULE_SSNHANDLE,         /**< Submodule: SSN handle */
  SSNERROR_SUBMODULE_SSNLICENSEPPSDK,   /**< Submodule: SSN License PP-SDK */
  SSNERROR_SUBMODULE_SSNLICENSEDUMMY,   /**< Submodule: SSN License dummy */
  SSNERROR_SUBMODULE_SSNERROR,          /**< Submodule: SSN error */
  SSNERROR_SUBMODULE_SSNSNMP,           /**< Submodule: SSN SNMP */
  SSNERROR_SUBMODULE_SBFANALYZE,        /**< Submodule: SBF Analyze */
  SSNERROR_SUBMODULE_SSNSDK,            /**< Submodule: SSN SDK */
  SSNERROR_SUBMODULE_SSNSDKPPSDK,       /**< Submodule: SSN SDK PPSDK */
  SSNERROR_SUBMODULE_PPECOMPUTE,        /**< Submodule: PPE Compute */
  SSNERROR_SUBMODULE_BASEFINDER,        /**< Submodule: BaseFinder */
  SSNERROR_SUBMODULE_MAX                /**< Maximum number of submodules */
} ssn_error_submodules_t;

/** Multiple SSN error codes. */
typedef enum
{
  /* Warnings */
  SSNERROR_WARNING_OK,                  /**< Everything OK */
  SSNERROR_WARNING_FALSE,               /**< False success */
  SSNERROR_WARNING_ALREADYPRESENT,      /**< Object already present */
  SSNERROR_WARNING_ENDOFSTREAM,         /**< End of stream reached */
  SSNERROR_WARNING_ENDOFFILE,           /**< End of file reached */
  SSNERROR_WARNING_INVALIDSBFBLOCK,     /**< Invalid SBF block */
  SSNERROR_WARNING_NODGPS,              /**< No DGPS data could be created */
  SSNERROR_WARNING_TIMEOUTOFRANGE,      /**< Given time stamp was out of SBF range */
  SSNERROR_WARNING_ENDOFLIST,           /**< Reached the end of a list */
  SSNERROR_WARNING_STREAMEMPTY,         /**< The given SBF stream is empty */
  SSNERROR_WARNING_TRACEERR,            /**< One ore more trace errors were seen inside algorithm */

  /* Errors */
  SSNERROR_ERROR_UNEXPECTED,            /**< Unexpected event inside algorithm */
  SSNERROR_ERROR_NOTIMPLEMENTED,        /**< Functionality not yet implemented */
  SSNERROR_ERROR_INVALIDARG,            /**< Invalid argument passed to the function */
  SSNERROR_ERROR_NULLPOINTER,           /**< An unexpected nullpointer has been passed to the function */
  SSNERROR_ERROR_OUTOFRANGE,            /**< At least one parameter is out of range */
  SSNERROR_ERROR_BUFTOOSMALL,           /**< The buffer presented to this function is too small */
  SSNERROR_ERROR_EMPTYSTRING,           /**< Passed string argument is empty */
  SSNERROR_ERROR_OUTOFMEMORY,           /**< Allocation problem (out of memory?) */
  SSNERROR_ERROR_BUSY,                  /**< Object busy */
  SSNERROR_ERROR_NOTPRESENT,            /**< Object not present */
  SSNERROR_ERROR_INVALIDLICENSE,        /**< Invalid license */
  SSNERROR_ERROR_LICENSENOTFOUND,       /**< No license information files not found. */
  SSNERROR_ERROR_LICENSENODONGLE,       /**< No dongle found. */
  SSNERROR_ERROR_INITLICENSE,           /**< Could not initialize license object */
  SSNERROR_ERROR_DEMOENDED,             /**< Demo period ended */
  SSNERROR_ERROR_INVALIDHANDLE,         /**< Invalid handle */
  SSNERROR_ERROR_INVALIDNAME,           /**< The specified file or directory name is not valid */
  SSNERROR_ERROR_READONLY,              /**< Object is read only -> probably in use */
  SSNERROR_ERROR_FILEOPEN,              /**< Error opening file */
  SSNERROR_ERROR_FILECLOSE,             /**< Error closing file */
  SSNERROR_ERROR_FILEREAD,              /**< Error reading file */
  SSNERROR_ERROR_FILEWRITE,             /**< Error writing file */
  SSNERROR_ERROR_FILESEEK,              /**< Error seeking file */
  SSNERROR_ERROR_FILEREMOVE,            /**< Error while removing file. */
  SSNERROR_ERROR_FILERO,                /**< File was opened read only. */
  SSNERROR_ERROR_WRONGSTATE,            /**< Object is in the wrong state */
  SSNERROR_ERROR_INVALIDRINEXFILE,      /**< Invalid RINEX file */
  SSNERROR_ERROR_IRNXHEADER,            /**< No END OF HEADER line found */
  SSNERROR_ERROR_IRNXEPOCHFLAG,         /**< Invalid epoch flag */
  SSNERROR_ERROR_INVALIDSBFFILE,        /**< Invalid SBF file */
  SSNERROR_ERROR_INVALIDASCIICMD,       /**< Invalid ASCII command */
  SSNERROR_ERROR_INVALIDSNMPCMD,        /**< Invalid SNMP command */
  SSNERROR_ERROR_INVALIDTIMESTAMP,      /**< Invalid timestamp */
  SSNERROR_ERROR_INVALIDRATE,           /**< Invalid rate specified. */
  SSNERROR_ERROR_INVALIDSBFBLOCK,       /**< Invalid SBF block */
  SSNERROR_ERROR_INVALIDSBFID,          /**< Invalid SBF ID specified */
  SSNERROR_ERROR_ONEINSTANCE,           /**< Only one instance is allowed */
  SSNERROR_ERROR_FNNOTENOUGH,           /**< Not enough GLONASS frequency numbers. */
  SSNERROR_ERROR_NOPVT,                 /**< Not enough data to compute a PVT */
  SSNERROR_ERROR_NO_GPSCORR,            /**< Not enough data to compute RTCM3 GPS corrections (possible lack of Doppler Measurements) */
  SSNERROR_ERROR_NOINFOFILEPATH,        /**< No info files path found. */
  SSNERROR_ERROR_INFOFILEPATHTOOLARGE,  /**< File path of info files exceeds 256 chars. */
  SSNERROR_ERROR_NOFLEXRATE,            /**< The specified SBF id has no flex rate. */
  SSNERROR_ERROR_ASN1,                  /**< ASN.1 parse error */
  SSNERROR_ERROR_SNMP,                  /**< General SNMP error */
  SSNERROR_ERROR_NOPOSDATA,             /**< No position data */
  SSNERROR_ERROR_NOPERMSFILE,           /**< No valid permissions file found */
  SSNERROR_ERROR_BADSERIALNR,           /**< Permissions not for this hardware (incorrect serial number) */
  SSNERROR_ERROR_WRONGHWPLATFORM,       /**< The hardware platform ID's do not match */
  SSNERROR_ERROR_STREAMNOTEMPTY,        /**< The specified stream is not empty */
  SSNERROR_ERROR_DIRISSUE,              /**< A directory issue (does not exist or invalid permissions) */
  SSNERROR_ERROR_NEQUICK,               /**< Could not initialize NeQuick. */
  SSNERROR_ERROR_BLOCKNOTFOUND,         /**< The requested SBF block could not be found. */
  SSNERROR_ERROR_PPEC_INITFAILED,       /**< PPECompute module failed to initialize. */
  SSNERROR_ERROR_PPEC_PVTFAILED,        /**< PPECompute module PVT computation failed. */
  SSNERROR_ERROR_PPEC_NAVMSGFAILED,     /**< PPECompute module NavMsg decoding failed. */
  SSNERROR_ERROR_PPEC_MEASFAILED,       /**< PPECompute module Meas decoding failed. */
  SSNERROR_ERROR_PPEC_UPDATEFAILED,     /**< PPECompute module failed to update. */
  SSNERROR_ERROR_PVTFAILED,             /**< PVT computation failed. */
  SSNERROR_ERROR_RTCMENCODINGFAILED,    /**< RTCM encoding failed. */
  SSNERROR_ERROR_APPENDBLOCKFAILED,     /**< Failed to append an SBF block. */
  SSNERROR_ERROR_PPEC_PVAFAILED,        /**< PPECompute module PVA computation failed. */
  SSNERROR_ERROR_PPEC_EXTMEASMSGFAILED,  /**< PPECompute module Ext Meas for INS decoding failed. */
  SSNERROR_ERROR_ELC_INVALIDSETTINGS,   /**< Invalid settings combination for ELC */
  SSNERROR_ERROR_NOPPSDKDONGLE,         /**< The found dongle is not for PPSDK (in case compiling for e.g. for GeoTagZ) */
  SSNERROR_ERROR_NOGEOTAGZDONGLE,       /**< The found dongle is not for PPSDK (in case compiling for e.g. for PPSDK) */
  SSNERROR_ERROR_CONSTELLATIONRINEX,    /**< Unsupported RINEX Constellation */
  SSNERROR_ERROR_BASEFINDERDBMISSING,   /**< The BaseFinder Database was not found */
  SSNERROR_ERROR_BASEFINDERDBFORMAT,    /**< The BaseFinder Database Format is wrong */
  SSNERROR_ERROR_BASEFINDER_NO_RINEX,   /**< The BaseFinder found no valid RINEX data for the given settings */
  SSNERROR_ERROR_BASEFINDER_NO_POS,     /**< The BaseFinder position is not specified */
  SSNERROR_ERROR_BASEFINDER_NO_TIME,    /**< The BaseFinder time interval is not specified */
  SSNERROR_ERROR_BASEFINDER_NO_RADIUS,  /**< The BaseFinder radius is not specified */
  SSNERROR_ERROR_UNCOMPRESSING_GZ,      /**< Error during the uncompressing of a GZ file */
  SSNERROR_ERROR_UNCOMPRESSING_Z,       /**< Error during the uncompressing of a Z file */
  SSNERROR_ERROR_NOBASEFINDERPERM,      /**< There is no basefinder permission */
  SSNERROR_ERROR_MAX                    /**< Number of warning and error codes in this enum */
} ssn_error_codes_t;

/** Multiple levels of severity. */
typedef enum
{
  SSNERROR_SEVERITY_SUCCESS,            /**< The result is a success. */
  SSNERROR_SEVERITY_FAILURE,            /**< The result is a failure. */
  SSNERROR_SEVERITY_MAX                 /**< Maximum number of severity levels. */
} ssn_error_severity_t;

/** Multiple levels of error types. */
typedef enum
{
  SSNERROR_TYPE_PRIVATE,                /**< A private, internal error. */
  SSNERROR_TYPE_GENERAL,                /**< A general error. */
  SSNERROR_TYPE_MAX                     /**< Maximum number of error types. */
} ssn_error_type_t;

/**
 *  \brief  Extract the error code from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \param  ssnerror  [in]  The error value that needs to be decoded.
 *
 *  Extract the error code from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \return
 *    Returns the code of the error.
 */
#define SSNERROR_GETCODE(ssnerror) \
  ((uint32_t)(ssnerror) & 0x0000007F)

/**
 *  \brief  Extract the code of the submodule from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \param  ssnerror  [in]  The error value that needs to be decoded.
 *
 *  Extract the code of the submodule from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \return
 *    Returns the code of the submodule.
 */
#define SSNERROR_GETSUBMODULE(ssnerror) \
  (((uint32_t)(ssnerror) >> 8) & 0x000000FF)

/**
 *  \brief  Extract the code of the module from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \param   ssnerror [in]  The error value that needs to be decoded.
 *
 *  Extract the code from the module of an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \return
 *    Returns the code of the module.
 */
#define SSNERROR_GETMODULE(ssnerror) \
  (((uint32_t)(ssnerror) >> 16) & 0x00007fff)

/**
 *  \brief  Extract the success or failure bit from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \param  ssnerror  [in]  The error value that needs to be decoded.
 *
 *  Extract the success or failure bit from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \retval 0 Success
 *  \retval 1 Failure
 */
#define SSNERROR_GETSEVERITY(ssnerror) \
  (((uint32_t)(ssnerror) >> 31) & 0x00000001)

/**
 *  \brief  Extract the general or private bit from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \param  ssnerror  [in]  The error value that needs to be decoded.
 *
 *  Extract the general or private bit from an \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \retval 0 Private
 *  \retval 1 General
 */
#define SSNERROR_GETTYPE(ssnerror) \
  (((uint32_t)(ssnerror) >> 7) & 0x00000001)

/**
 *  \brief  Create an \ref ssnerror::ssn_error_t "ssn_error_t" code.
 *
 *  \param  sev     [in]  Specifies the severity.
 *  \param  mod     [in]  Specifies the module.
 *  \param  submod  [in]  Specifies the submodule.
 *  \param  gen     [in]  Specifies the type of error.
 *  \param  code    [in]  The actual error code.
 *
 *  Create a full \ref ssnerror::ssn_error_t "ssn_error_t" value containing all the
 *  required error data.
 *
 *  \return
 *    Returns a full \ref ssnerror::ssn_error_t "ssn_error_t".
 */
#define SSNERROR_CREATE(sev, mod, submod, gen, code) \
  ((ssn_error_t)(((uint32_t)(sev) << 31) | ((uint32_t)(mod) << 16) | ((uint32_t)(submod) << 8) | ((uint32_t)(gen) << 7) | ((uint32_t)(code))))

/**
 *  \brief  Check if the error was a success or a failure.
 *
 *  \param  ssnerror  [in]  The error value to be decoded.
 *
 *  Check if the error was a success or a failure.
 *
 *  \retval 0 Failure
 *  \retval 1 Success
 */
#define SSNERROR_GETSTATUS(ssnerror) \
  (((uint32_t)(ssnerror) < 0x80000000) ? 1 : 0)

/**
 *  \brief  Check if the error is actually a warning.
 *
 *  \param  ssnerror  [in]  The error value to be decoded.
 *
 *  Check if the error is actually a warning.
 *
 *  \retval 0 Error
 *  \retval 1 Warning
 */
#define SSNERROR_ISWARNING(ssnerror) \
  ((((uint32_t)(ssnerror) < 0x80000000) && ((uint32_t)(ssnerror) != 0)) ? 1 : 0)

/* Types ---------------------------------------------------------------------*/

/* Public Variables/Structs --------------------------------------------------*/

/* Public Procedures ---------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
/**
 *  \brief  Get the error message.
 *
 *  \param  ssnerror  [in]  The \ref ssnerror::ssn_error_t "ssn_error_t".
 *
 *  \pre  \p ssnerror is not \p NULL.
 *
 *  Get the error message.
 *
 *  \return
 *    Returns the error message.
 */
FW_EXPORT const char*
SSNError_getMessage(ssn_error_t ssnerror);

/**
 *  \brief  Get the name of the module where the error occurred.
 *
 *  \param  ssnerror  [in]  The \ref ssnerror::ssn_error_t "ssn_error_t" code.
 *
 *  \pre  \p ssnerror is not \p NULL.
 *
 *  Get the name of the module where the error occurred.
 *
 *  \return
 *    Returns the name of the module were the error occurred.
 */
FW_EXPORT const char*
SSNError_getModule(ssn_error_t ssnerror);

/**
 *  \brief  Get the name of the submodule where the error occurred.
 *
 *  \param  ssnerror  [in]  The \ref ssnerror::ssn_error_t "ssn_error_t" code.
 *
 *  \pre  \p ssnerror is not \p NULL.
 *
 *  Get the name of the submodule where the error occurred.
 *
 *  \return
 *    Returns the name of the submodule where the error occurred.
 */
FW_EXPORT const char*
SSNError_getSubmodule(ssn_error_t ssnerror);

#ifdef __cplusplus
}
#endif

#endif
/* END OF HEADER FILE ========================================================*/
