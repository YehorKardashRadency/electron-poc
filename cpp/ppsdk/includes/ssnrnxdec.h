/**
 *  \file     ssnrnxdec.h
 *  \ingroup  SSNRNXDec
 *  \brief    API of the SSN RINEX Decoder module.
 *
 *  \par Copyright:
 *    (c) 2006 - 2008 Septentrio Satellite Navigation NV/SA, Belgium
 *
 *  \note None of the SSN RINEX decoder module functions require a valid SSN
 *        license unless otherwise noted in the function description. A valid
 *        SSN SDK handle is required to open an SSN RINEX handle.
 *
 *  The SSN RINEX decoder module allows the conversion from RINEX navigation and
 *  RINEX observation data files to SBF data.\n
 *  All known satellite types are supported.
 *
 *  \par References:
 *    \li RINEX: The Receiver Independent Exchange Format Version 2.10 [Gurtner 2002]
 *        ( http://www.aiub.unibe.ch/download/rinex/rinex210.txt )
 *    \li RINEX: The Receiver Independent Exchange Format Version 3.00 [Gurtner 2006]
 *        ( http://www.aiub.unibe.ch/download/rinex/rinex300.pdf )
 */
#ifndef SSNRNXDEC_H
/** To avoid multiple inclusions */
#define SSNRNXDEC_H 1

/* Includes ==(needed for self-contained / -consistent)=======================*/

#include "ssnerror.h"     /* Error handling */
#include "ssnsbfstream.h" /* SBF stream */
#include "ssnsdk.h"       /* SSN SDK handle */
#include "ssnhandle.h"    /* SSN safe handle */

#include <stddef.h>       /* size_t */

#ifdef __cplusplus
extern "C" {
#endif

/* Declarations ==============================================================*/

/* Constants & Macros --------------------------------------------------------*/

/** Maximum number of RINEX files */
#define MAX_RNX_FILES   72
/** Maximum length of RINEX file names */
#define MAX_RNX_FLENGTH 256

/* Types ---------------------------------------------------------------------*/

/** RINEX decoder handle */
typedef ssn_hhandle_t ssn_hrnxdec_t;

/** RINEX Doppler options */
typedef enum
{
  SSNRNXDEC_DOPPLERFROMLX_NEVER = 0,    /**< Doppler in SBF is taken from the Dx observable in RINEX, 
                                             and is set to NOTVALID if there is no Dx observable */
  SSNRNXDEC_DOPPLERFROMLX_ALWAYS,       /**< Doppler in SBF is always computed from differencing
                                             carrier phase measurements (Lx).  The Dx observable in RINEX is discarded.*/
  SSNRNXDEC_DOPPLERFROMLX_AUTO,         /**< Doppler in SBF is taken from the Dx observable in RINEX if 
                                             available, or is computed from carrier phase otherwise */
} ssn_rnxdec_dopplerfromlx_t;

/** RINEX parameter types */
typedef enum
{
  SSNRNXDEC_PARAM_LEAPSECOND              = 0,  /**< Leap seconds */
  SSNRNXDEC_PARAM_GLONASS_FREQUENCYFILE DEPRECATED_ENUM("This functionality should not be used anymore and will be removed in a future version."),
                                                /**< GLONASS frequency files */
  SSNRNXDEC_PARAM_GLONASS_FALLBACKLIST DEPRECATED_ENUM("This functionality should not be used anymore and will be removed in a future version."),
                                                /**< GLONASS frequency list fallback */
  SSNRNXDEC_PARAM_CN0_INTERNAL_DEFAULT,         /**< Use the internal default values for C/N0 (CA = 45, P1 = 20, P2 = 25) */
  SSNRNXDEC_PARAM_FORCEDOPPLERFROMCARRIERPHASE, /**< Doppler computation mode, see ssn_rnxdec_dopplerfromlx_t */
  SSNRNXDEC_PARAM_MAX                           /**< Maximum number of parameters */
} ssn_rnxdec_parameters_t;

/** RINEX decoder progress callback function list */
typedef enum
{
  SSNRNXDEC_PROGRESSCB_FLIST_NONE       = 0x0000, /**< None */
  SSNRNXDEC_PROGRESSCB_FLIST_CREATESBF  = 0x0001, /**< SSNRNXDec_createSBF() */

  SSNRNXDEC_PROGRESSCB_FLIST_ALL        = 0xFFFF, /**< All */
} ssn_rnxdec_progresscb_flist_t;

/**
 *  \brief  RINEX decoder callback function
 *
 *  \param  fitem       [in] Function ID
 *  \param  percentage  [in] Current progress percentage
 *
 *  A callback function used by the RINEX decoder functionality to indicate
 *  the current progress percentage.
 *
 *  \return void
 */
typedef void (*ssn_rnxdec_progresscb_t)(ssn_rnxdec_progresscb_flist_t fitem, float percentage);

/**
*  \brief  RINEX decoder user data pointer callback function
*
*  \param  fitem       [in]  Function ID
*  \param  percentage  [in]  Current progress percentage
*  \param  userData    [in]  User Data pointer
*
*  A callback function used by the RINEX decoder functionality to indicate
*  the current progress percentage.
*
*  \return void
*/
typedef void(*ssn_rnxdec_userdata_progresscb_t)(ssn_rnxdec_progresscb_flist_t fitem, float percentage, void *userData);

/* Public Variables/Structs --------------------------------------------------*/

/**
 * \brief RINEX callback structure.
 */
typedef struct rnxdec_callback_s
{
  ssn_rnxdec_progresscb_t           progresscb;       /**< Progress callback function */
  ssn_rnxdec_userdata_progresscb_t  progressudcb;     /**< Progress callback function with user data */
  void                             *userdata;         /**< Pointer to the userdata that should be returned with the progressudcb */
  ssn_rnxdec_progresscb_flist_t     progresscb_flist; /**< List of subscribed functions */
} rnxdec_callback_t;


/* Public Procedures ---------------------------------------------------------*/

/**
 *  \brief Open a RINEX decoder handle
 *
 *  \param ssnsdkhandle [in]  The SSN SDK handle
 *  \param rnxdechandle [out] The RINEX decoder structure
 *
 *  \note When an error occcurs in one of the functions all opened handles 
 *        should be closed by calling their \p close() function to free any
 *        allocated memory and to cleanup the handle.
 *
 *  Allocate the required ammount of memory for the RINEX decoder handle and
 *  initialize the handle.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNRNXDec_open(ssn_hsdk_t     ssnsdkhandle,
               ssn_hrnxdec_t *rnxdechandle);

/**
 *  \brief Close a RINEX decoder handle
 *
 *  \param rnxdechandle [in] The RINEX decoder structure
 *
 *  \pre  \p rnxdechandle is not \p NULL
 *
 *  Close the RINEX decoder handle and free the allocated memory.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNRNXDec_close(ssn_hrnxdec_t rnxdechandle);

/**
 *  \brief Validate a RINEX decoder handle
 *
 *  \param rnxdechandle [in] The RINEX decoder handle to validate
 *
 *  Check if a RINEX decoder handle is valid or not.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNRNXDec_validate(ssn_hrnxdec_t  rnxdechandle);

/**
 *  \brief Set optional parameters
 *
 *  \param rnxdechandle [in]  The RINEX decoder structure
 *  \param parameter    [in]  RINEX decoder parameter options
 *  \param value        [in]  RINEX decoder parameter values
 *
 *  Set the optional parameters.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNRNXDec_setParameters(ssn_hrnxdec_t             rnxdechandle,
                        ssn_rnxdec_parameters_t   parameter,
                        void                     *value);

/**
 *  \brief  Add RINEX files
 *
 *  \param  rnxdechandle  [in]  The RINEX decoder structure
 *  \param  filename      [in]  Name of the RINEX file to add
 *
 *  \pre  \p rnxdechandle is not \p NULL
 *
 *  Add a RINEX file to the list of files that need to be converted.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNRNXDec_addRinexFile(ssn_hrnxdec_t  rnxdechandle,
                       char          *filename);

/**
 *  \brief  List the added RINEX files.
 *
 *  \param  rnxdechandle  [in]      The RINEX decoder structure
 *  \param  length        [in/out]  The length of the file name
 *  \param  filename      [out]     The file name of the RINEX file
 *
 *  \pre    \p rnxdechandle is not \p NULL
 *
 *  \note This function uses the so called "double-call" mechanism. Call this
 *        function twice, passing \p NULL as the reply string the first time to
 *        calculate the amount of memory that needs to be allocated to fit the
 *        reply string. It is recommended to set buffersize to the size of the 
 *        allocated memory before the second call.
 *
 *  List the added RINEX files one by one. Call this function repeatedly for
 *  each added RINEX file name.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNRNXDec_listRinexFiles(ssn_hrnxdec_t  rnxdechandle,
                         size_t        *length,
                         char          *filename);

/**
*  \brief Create an SBF stream from one or more RINEX files
*
*  \param rnxdechandle     [in]  The RINEX decoder structure
*  \param sbfstreamhandle  [out] The converted SBF data
*
*  \pre  \p rnxdechandle is not \p NULL
*
*  \post \p sbfstreamhandle contains the converted RINEX data
*
*  \note The SBF stream handle holding the output information will be created by
*        this function.
*
*  Convert a number of RINEX navigation and observation data files to SBF blocks.
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
*          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
*              the function was executed successfully
*          \li an error code describing the error
*             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNRNXDec_createSBF(ssn_hrnxdec_t     rnxdechandle,
                    ssn_hsbfstream_t *sbfstreamhandle);

/**
*  \brief Create an SBF stream from one or more RINEX files and crops the output to the given interval
*
*  \param rnxdechandle     [in]  The RINEX decoder structure
*  \param cropstart        [in]  The GNSS time stamp (in seconds) from where to start
*  \param cropend          [in]  The GNSS time stamp (in seconds) where to end
*  \param sbfstreamhandle  [out] The converted SBF data
*
*  \pre  \p rnxdechandle is not \p NULL
*
*  \post \p sbfstreamhandle contains the converted RINEX data
*
*  \note The SBF stream handle holding the output information will be created by
*        this function.
*
*  Convert a number of RINEX navigation and observation data files to SBF blocks.
* 
*  If cropstart is set to its "do-not-use" value (\p F64_NOTVALID) no cropping will 
*  be performed at the start.\n
*  If cropstart is set to its "do-not-use" value (\p F64_NOTVALID) no cropping will
*  be performed at the end.
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
*          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
*              the function was executed successfully
*          \li an error code describing the error
*             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNRNXDec_createSBFCropped(ssn_hrnxdec_t     rnxdechandle,
                           double            cropstart,
                           double            cropend,
                           ssn_hsbfstream_t *sbfstreamhandle);

/**
 *  \brief  Set or reset the callback function
 *
 *  \param  rnxdechandle  [in]  The RINEX decoder handle
 *  \param  callback      [in]  The progress callback function or \p NULL
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
SSNRNXDec_pcSetCallback(ssn_hrnxdec_t           rnxdechandle,
                        ssn_rnxdec_progresscb_t callback);

/**
*  \brief  Set or reset the callback function with a userdata pointer
*
*  \param  rnxdechandle    [in]  The RINEX decoder handle
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
SSNRNXDec_pcSetUserDataCallback(ssn_hrnxdec_t                     rnxdechandle,
                                ssn_rnxdec_userdata_progresscb_t  callback,
                                void                             *userdata);

/**
 *  \brief  Subscribe a function to the progress callback
 *
 *  \param  rnxdechandle  [in]  The RINEX decoder handle
 *  \param  function      [in]  The ID of the function
 *
 *  Subscribe a function to report its progress using the specified callback
 *  function. Pass \p SSNRNXDEC_PROGRESSCB_FLIST_NONE to reset any subscribed
 *  function.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNRNXDec_pcSubscribe(ssn_hrnxdec_t                 rnxdechandle,
                      ssn_rnxdec_progresscb_flist_t function);

/**
 *  \brief  Unsubscribe a previously subscribed function
 *
 *  \param  rnxdechandle  [in]  The RINEX decoder handle
 *  \param  function      [in]  The ID of the function
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
SSNRNXDec_pcUnsubscribe(ssn_hrnxdec_t                 rnxdechandle,
                        ssn_rnxdec_progresscb_flist_t function);

/**
 *  \brief  Check whether a given function is subscribed
 *
 *  \param  rnxdechandle  [in]  The RINEX decoder handle
 *  \param  function      [in]  The ID of the function
 *  \param  issubscribed  [out] True or false
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
SSNRNXDec_pcIsSubscribed(ssn_hrnxdec_t                  rnxdechandle,
                         ssn_rnxdec_progresscb_flist_t  function,
                         bool                          *issubscribed);

/**
 *  \brief add pointer to escape variable to monitor escape
 *
 *  \param  rnxdechandle [in]  The post processing engine handle
 *  \param  pescape      [in]  The pointer to the esc value
 *
 *  When a pointer different from NULL is used the calculations will stop as soon 
 *  as value equals true.                 
 */
FW_EXPORT void
SSNRNXDec_setEscapePointer(ssn_hrnxdec_t   rnxdechandle,
                           bool           *pescape);

/**
 *  \brief  check if rnxdec was escaped
 *
 *  \param  rnxdechandle [in]  The rinex decoding handle
 *
 *  \return Returns true if stream was escaped. 
 */
FW_EXPORT bool
SSNRNXDec_isEscaped(ssn_hrnxdec_t  rnxdechandle);

#ifdef __cplusplus
}
#endif

#endif
/* END OF HEADER FILE ========================================================*/
