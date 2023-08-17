/**
 *  \file
 *  \ingroup  SSNSDK
 *  \brief    API of the SSN SDK module, which manages license handles.
 *
 *  \par Copyright:
 *    (c) 2008 Septentrio Satellite Navigation NV/SA, Belgium
 *
 *  The SSN SDK module is the main object of the SDK and has a major
 *  part in the verification of the license and permissions.
 */
#ifndef SSNSDK_H
/** To avoid multiple inclusions */
#define SSNSDK_H 1

/* Includes ==(needed for self-contained / -consistent)=======================*/

#include "ssnerror.h"   /* SSN error module */
#include "ssnhandle.h"  /* SSN safe handle */
#include "ssntypes.h"   /* SSN types */

#include <stddef.h>     /* size_t */

#ifdef __cplusplus
extern "C" {
#endif

/* Declarations ==============================================================*/

/* Constants & Macros --------------------------------------------------------*/

/** Different PPSDK Permissable features. */
typedef enum
{
  SSN_SDK_BASEFINDER_PERM,                  /**< BaseFinder Permission*/
} ssn_ppsdk_perms_t;


/* Types ---------------------------------------------------------------------*/

/** SSN SDK handle */
typedef ssn_hhandle_t ssn_hsdk_t;

/* Public Variables/Structs --------------------------------------------------*/

/* Public Procedures ---------------------------------------------------------*/

/**
 *  \brief  Open an SSN SDK handle
 *
 *  \param  ssnsdkhandle [in/out] The SSN SDK handle
 *
 *  \note When an error occurs in one of the functions all opened handles
 *        should be closed by calling their \p close() function to free any
 *        allocated memory and to cleanup the handle.
 *
 *  Open an SSN SDK handle without a license verification. This handle can be
 *  used by modules and functions that do not depend on the permissions to
 *  enable or disable functionality.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_open(ssn_hsdk_t *ssnsdkhandle);

/**
 *  \brief  Open an SSK SDK handle with a valid license
 *
 *  \param  ssnsdkhandle [in/out] The SSN SDK handle
 *
 *  Open an SSN SDK handle with a license verification. This handle can be used
 *  by modules and functions that depend on a valid permissions file to enable
 *  or disable functionality.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_openLicensed(ssn_hsdk_t *ssnsdkhandle);


/**
*  \brief  Check if a license is valid and if the permission file matches the inserted dongle
*
*  Checks the license and match with the permission file of the inserted dongle
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNSDK_checkLicensed();

/**
*  \brief  Return the permission value associated with a PPSDK functionality.
*
*  This function first calls the \ref SSNSDK_checkLicensed function to check the license
*  and then returns the value fo the requested permission
*
*  \param  perm [in]  The permission that must be returned
*  \param  val  [out] The value associated with the requested PPSDK functionality
*                     in the permission file, or 0 if there is no permission
*                     for this functionality.
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either:
*          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
*              the function was executed successfully
*          \li an error code describing the error
*             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNSDK_getPermission(ssn_ppsdk_perms_t perm, int* val);

/**
*  \brief  Returns the number of runs left for a DEMO dongle
*
*  Checks how many runs are left for a DEMO dongle
*
*  \param  demoDongle [out] true if the dongle is a demo dongle, else false
*  \param  runsLeft [out] the number of runs left if the dongle is a demo dongle, else 0
*
*  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
*/
FW_EXPORT ssn_error_t
SSNSDK_checkDemoRuns(bool *demoDongle, uint16_t *runsLeft);

/**
 *  \brief  Close an SSN SDK handle
 *
 *  \param  ssnsdkhandle  [in]  The SSN SDK handle to close
 *
 *  Closes an SSN SDK handle and frees any allocated memory.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_close(ssn_hsdk_t ssnsdkhandle);

/**
 *  \brief  Validate an SSN SDK handle
 *
 *  \param  ssnsdkhandle  [in]  The SSN SDK handle to verify
 *
 *  Validate an SSN SDK handle.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_validate(ssn_hsdk_t ssnsdkhandle);

/**
 *  \brief  Set the SDK temporary directory
 *
 *  \param  ssnsdkhandle  [in/out]  The SSN SDK handle
 *  \param  tempdir       [in]      The path to the temporary directory
 *
 *  Some SDK functionality creates temporary files to store and modify data.
 *  This function allows you to overwrite the default path.
 *
 *  \note The path is limited to 255 characters.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_setTempDir(ssn_hsdk_t  ssnsdkhandle,
                  char       *tempdir);

/**
 *  \brief  Get the license serial number
 *
 *  \param  ssnsdkhandle  [in]  The SSN SDK handle
 *  \param  serialnumber  [out] The serial number
 *
 *  Get the SSN SDK license serial number.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_licGetSN(ssn_hsdk_t  ssnsdkhandle,
                uint32_t   *serialnumber);

/**
 *  \brief  Get the license hardware ID
 *
 *  \param  ssnsdkhandle  [in]  The SSN SDK handle
 *  \param  hwid          [out] The hardware ID
 *
 *  Get the SSN SDK license hardware ID.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_licGetHWID(ssn_hsdk_t  ssnsdkhandle,
                  uint32_t   *hwid);

/**
 *  \brief  Get the license information text
 *
 *  \param  ssnsdkhandle  [in]  The SSN SDK handle
 *  \param  size          [out] The license info text size
 *  \param  text          [out] The license info text
 *
 *  \note This function uses the "double-call" mechanism. Call the function once
 *        and set the \p text parameter to \p NULL to get the size of the info
 *        text message, allocate the required amount of bytes and call the
 *        function a second time to fill in the text message.
 *        It is recommended to set buffersize to the size of the allocated memory
 *        before the second call.
 *
 *  Get the license text info message.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_licGetText(ssn_hsdk_t  ssnsdkhandle,
                  size_t     *size,
                  char       *text);

/**
 *  \brief  Get the license information extra
 *
 *  \param  ssnsdkhandle  [in]  The SSN SDK handle
 *  \param  size          [out] The license info extra size
 *  \param  extra         [out] The license info extra
 *
 *  \note This function uses the "double-call" mechanism. Call the function once
 *        and set the \p extra parameter to \p NULL to get the size of the info
 *        extra message, allocate the required amount of bytes and call the
 *        function a second time to fill in the extra message.
 *        It is recommended to set buffersize to the size of the allocated memory
 *        before the second call.
 *
 *  Get the license extra info message.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSDK_licGetExtra(ssn_hsdk_t   ssnsdkhandle,
                   size_t      *size,
                   char        *extra);

#ifdef __cplusplus
}
#endif

#endif
/* END OF HEADER FILE ========================================================*/
