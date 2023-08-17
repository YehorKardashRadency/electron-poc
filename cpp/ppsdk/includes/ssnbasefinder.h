/**
 *  \file
 *  \ingroup  BaseFinder
 *  \brief    API of the SSN BaseFinder module, which retrieve reference data from base stations.
 *
 *  \par Copyright:
 *    (c) 2006 - 2018 Septentrio Satellite Navigation NV/SA, Belgium
 *
 *  The SSN BaseFinder module allows downloading the most appropriate
 *  reference data for the given settings.
 *
 */
#ifndef SSNBASEFINDER_H
/** To avoid multiple inclusions */
#define SSNBASEFINDER_H 1

/* Includes ==(needed for self-contained / -consistent)=======================*/

#include "ssnerror.h"                      /* Error handling */
#include "ssnsbfstream.h"                  /* SBF stream */
#include "ssnsdk.h"                        /* SSN SDK handle */
#include "ssnhandle.h"                     /* SSN safe handle */
#include "basefinderconstellations.h"     /* The constellations to be used by BaseFinder */

#ifdef __cplusplus
extern "C" {
#endif

/* Declarations ==============================================================*/

/* Constants & Macros --------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

#pragma pack(push, 4)

/** RINEX decoder handle */
typedef ssn_hhandle_t ssn_hbasefinder_t;

/** RINEX decoder progress callback function list */
typedef enum
{
  SSNBASEFINDER_PROGRESSCB_FLIST_NONE              = 0x0000, /**< None */
  SSNBASEFINDER_PROGRESSCB_FLIST_CREATESBF         = 0x0001, /**< SSNBaseFinder_createSBF() */
  SSNBASEFINDER_PROGRESSCB_FLIST_CREATESTATIONLIST = 0x0002, /**< SSNBaseFinder_createStationList() */
  SSNBASEFINDER_PROGRESSCB_FLIST_ALL               = 0xFFFF, /**< All */
} ssn_basefinder_progresscb_flist_t;

/** \brief represents the name and provider of a base station */
typedef struct
{
  const char* name;
  const char* provider;
} ssn_basefinder_station_id_t;

/** \brief represents the provider and a station of a base station */
typedef struct
{
  const char* provider;
  const char* station;
} ssn_basefinder_blacklist_info_t;

/** \brief represents the properties of a base station */
typedef struct
{
  char* name;
  char* provider;
  double latitude;
  double longitude;
  double altitude;
  double distance;
  int constellations;
  char* receiverType;
} ssn_basefinder_station_info_t;

/**
 * \brief Represents a list of reference stations.
 */
typedef struct
{
  /// Pointer to the array of stations.
  ssn_basefinder_station_info_t* stations;

  /// Number of stations in this list.
  size_t size;
} ssn_basefinder_station_info_list_t;

/**
 * \brief Used by BaseFinder to store the results of its computation.
 */
typedef struct
{
  ssn_basefinder_station_info_t station;
  int constellations;
  double sbfInterval;
} ssn_basefinder_sbf_result_t;

/**
 *  \brief  BaseFinder callback function
 *
 *  \param[in] fitem      Function ID
 *  \param[in] percentage Current progress percentage
 *
 *  A callback function used by the BaseFinder functionality to indicate
 *  the current progress percentage.
 *
 *  \return void
 */
typedef void (*ssn_basefinder_progresscb_t)(ssn_basefinder_progresscb_flist_t fitem, float percentage);

/**
*  \brief  BaseFinder user data pointer callback function
*
*  \param[in] fitem      Function ID
*  \param[in] percentage Current progress percentage
*  \param[in] userData   User Data pointer
*
*  A callback function used by the BaseFinder functionality to indicate
*  the current progress percentage.
*
*  \return void
*/
typedef void(*ssn_basefinder_userdata_progresscb_t)(ssn_basefinder_progresscb_flist_t fitem, float percentage, void *userData);

#pragma pack(pop)

/* Public Variables/Structs --------------------------------------------------*/

/* Public Procedures ---------------------------------------------------------*/

/**
 *  \brief Open a BaseFinder handle
 *
 *  \param[in]  ssnsdkhandle     The SSN SDK handle
 *  \param[out] basefinderhandle The BaseFinder handle
 *
 *  \note When an error occcurs in one of the functions all opened handles 
 *        should be closed by calling their \p close() function to free any
 *        allocated memory and to cleanup the handle.
 *
 *  Allocate the required ammount of memory for the BaseFinder handle and
 *  initialize the handle.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_open(ssn_hsdk_t          ssnsdkhandle,
                    ssn_hbasefinder_t *basefinderhandle);
 
/**
 *  \brief Close a BaseFinder handle
 *
 *  \param[in] basefinderhandle The BaseFinder handle
 *
 *  \pre  \p basefinderhandle is not \p NULL
 *
 *  Close the BaseFinder handle and free the allocated memory.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_close(ssn_hbasefinder_t *basefinderhandle);

/**
 *  \brief Validate a BaseFinder handle
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *
 *  Check if a BaseFinder handle is valid or not.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_validate(ssn_hbasefinder_t  basefinderhandle);

/**
 *  \brief Check the license for basefinder
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *
 *  Check if the license of the handle is valid for BaseFinder.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_checkLicense(ssn_hbasefinder_t  basefinderhandle);

/**
 *  \brief Set SBF input file.
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] sbfFileName The SBF file to be used to lookup the position and time interval
 *
 *  Note that setting this option resets the already set position and time
 *  interval. If the position or interval from the SBF file should not be used
 *  they must be set after setting the SBF input file. In order to find the
 *  position the file must contain at least one PVTCartesian or PVTGeodetic SBF
 *  block. The interval is looked up by finding the first and last MeasEpoch SBF
 *  block.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setSbfInput(ssn_hbasefinder_t basefinderhandle,
                          const char* sbfFileName);

/**
 *  \brief Set position using Cartesian coordinates.
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] x the cartesian x position in m
 *  \param[in] y the cartesian y position in m
 *  \param[in] z the cartesian z position in m
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setPositionCartesian(ssn_hbasefinder_t basefinderhandle,
                                   double x, double y, double z);

/**
 *  \brief Set position using Geodetic coordinates (degrees, degrees, meter).
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] lat the geodetic latitude in degrees
 *  \param[in] lon the geodetic longitude in degrees
 *  \param[in] alt the geodetic altitude in m
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setPositionGeodetic(ssn_hbasefinder_t basefinderhandle,
                                  double lat, double lon, double alt);

/**
 * \brief Set the begin time for which reference data must be found (GNSS time in seconds).
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] time the begin time in GNSS time in seconds
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setBeginTime(ssn_hbasefinder_t basefinderhandle, double time);

/**
 * \brief Set the end time for which reference data must be found (GNSS time in seconds).
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] time the end time in GNSS time in seconds
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setEndTime(ssn_hbasefinder_t basefinderhandle, double time);

/**
 *  \brief Set the proxy to use for network accesses (URL:port).
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] proxy the proxy that should be used (URL:port)
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setProxy(ssn_hbasefinder_t basefinderhandle, const char* proxy);

/**
 *  \brief Disable proxy for the given hosts.
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] host Array with hosts for which the proxy should not be used
 *  \param[in] numberOfHosts The number of elements in the host array
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setNoProxyHosts(ssn_hbasefinder_t basefinderhandle,
                              const char* host[], size_t numberOfHosts);

/**
 *  \brief Set the search radius around the rover position in km (default 100km).
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] radius The search radius in km
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setSearchRadius(ssn_hbasefinder_t basefinderhandle,
                              uint32_t radius);

/**
 *  \brief Set the preferred reference constellations.
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param constellations A bitwise-or of the preferred constellations.
 *
 *  \note Currently only GPS, GLONASS, SBAS, GALILEO and BeiDou are supported. Enabling other
 *        systems has no effect, but they are foreseen for future versions.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setPreferredConstellations(ssn_hbasefinder_t basefinderhandle,
                                         ssn_basefinder_constellations_t constellations);

/**
 *  \brief Set the blacklisted stations.
 *
 *  If the provider for one of the given stations is an empty string, all
 *  stations matching its name will be blacklisted.
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] blacklistInfos Array with black listed stations
 *  \param[in] numberOfBlacklistInfos The number of elements in the host array
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setBlacklistedStations(ssn_hbasefinder_t basefinderhandle,
                                     const ssn_basefinder_blacklist_info_t blacklistInfos[],
                                     size_t numberOfBlacklistInfos);

/**
 *  \brief Make SSNBaseFinder_createSBF() work in manual mode using the given station.
 *
 *  Manual mode means that SSNBaseFinder_createSBF() creates a reference SBF with
 *  data from the given station. Pass \p NULL to work in automatic mode (the
 *  default).
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] station The base station to use
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setManualStation(ssn_hbasefinder_t basefinderhandle,
                               const ssn_basefinder_station_id_t* station);

/**
 *  \brief Set to true to force Doppler computation from the Lx (carrier-phase) observables.
 *
 *  By default the Doppler data is copied from the Dx observables when present,
 *  otherwise it is computed from the Lx observables.
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] enable Set to true to force Doppler computation from the Lx (carrier-phase) observables.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setForceComputeDoppler(ssn_hbasefinder_t basefinderhandle,
                                     bool enable);

/**
 *  \brief Set the directory where the downloaded RINEX files must be kept as a reference.
 *
 *  If not set, the files are automatically deleted.
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] directory the directory where the downloaded RINEX files must be kept as a reference
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setRinexDirectory(ssn_hbasefinder_t basefinderhandle,
                                const char* directory);

/**
 *  \brief Enable/disable automatic signal detection (default enabled).
 *
 *  By default, the SBF input file (if provided) is parsed to find which signal
 *  types are included. The search algorithm uses these signals to find the best
 *  reference station. This function can be used to disable this behavior.
 *
 *  \param[in] basefinderhandle The BaseFinder handle to validate
 *  \param[in] enable Enable/disable automatic signal detection (default enabled)
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_setAutoSignalDetection(ssn_hbasefinder_t basefinderhandle,
                                     bool enable);

/**
 *  \brief Create an SBF stream from the most applicable reference data.
 *
 *  \param[in]  basefinderhandle The BaseFinder handle.
 *  \param[out] sbfstreamhandle The reference SBF data.
 *  \param[out] result Optional pointer to store extra results. If not NULL, must be
 *                     freed using SSNBaseFinder_freeSbfResult() after use.
 *
 *  \post \p sbfstreamhandle contains the reference SBF data
 *
 *  \note The SBF stream handle holding the output information will be created by
 *        this function.
 *
 *  Downloads the most applicable reference data and converts it to SBF.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_createSBF(ssn_hbasefinder_t basefinderhandle,
                        ssn_hsbfstream_t* sbfstreamhandle,
                        ssn_basefinder_sbf_result_t* result);

/**
 * \brief Free a result created by SSNBaseFinder_createSBF().
 *
 *  \param[in]     basefinderhandle The BaseFinder handle.
 *  \param[in,out] result The result to free
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_freeSbfResult(ssn_hbasefinder_t basefinderhandle,
                            ssn_basefinder_sbf_result_t* result);

/**
 * \brief Create a list of the stations matching the given criteria.
 *
 * \param[in]  basefinderhandle The BaseFinder handle.
 * \param[out] stations         Pointer to the list to be created.
 *
 * \note If this function returns successfully, \p stations must be freed using
 *       SSNBaseFinder_freeStationList().
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_createStationList(ssn_hbasefinder_t  basefinderhandle,
                                ssn_basefinder_station_info_list_t* stations);

/**
 * \brief Free a list created with SSNBaseFinder_createStationList().
 *
 * \param[in] basefinderhandle The BaseFinder handle.
 * \param[in] stations         Pointer to the list to be freed.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_freeStationList(ssn_hbasefinder_t  basefinderhandle,
                              ssn_basefinder_station_info_list_t* stations);

/**
 * \brief Create a CSV file containing the given stations.
 *
 * \param[in] basefinderhandle The BaseFinder handle.
 * \param[in] stations         Pointer to the list of stations.
 * \param[in] fileName         Name of the CSV file to create.
 *
 * \note A first header line is written to describe the content of the columns
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either:
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if
 *              the function was executed successfully
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_writeStationListCsv(ssn_hbasefinder_t  basefinderhandle,
                                  const ssn_basefinder_station_info_list_t* stations,
                                  const char* fileName);

/**
 *  \brief  Set or reset the callback function
 *
 *  \param[in]  basefinderhandle The BaseFinder handle
 *  \param[in]  callback         The progress callback function or \p NULL
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
SSNBaseFinder_pcSetCallback(ssn_hbasefinder_t           basefinderhandle,
                            ssn_basefinder_progresscb_t callback);

/**
*  \brief  Set or reset the callback function with a userdata pointer
*
*  \param[in] basefinderhandle The BaseFinder handle
*  \param[in] callback         The callback function or \p NULL
*  \param[in] userdata         The pointer that should be returned with the callback or \p NULL
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
SSNBaseFinder_pcSetUserDataCallback(ssn_hbasefinder_t                     basefinderhandle,
                                    ssn_basefinder_userdata_progresscb_t  callback,
                                    void                                 *userdata);

/**
 *  \brief  Subscribe a function to the progress callback
 *
 *  \param[in] basefinderhandle The BaseFinder handle
 *  \param[in] function         The ID of the function
 *
 *  Subscribe a function to report its progress using the specified callback
 *  function. Pass \p SSNBASEFINDER_PROGRESSCB_FLIST_NONE to reset any subscribed
 *  function.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNBaseFinder_pcSubscribe(ssn_hbasefinder_t                 basefinderhandle,
                          ssn_basefinder_progresscb_flist_t function);

/**
 *  \brief  Unsubscribe a previously subscribed function
 *
 *  \param[in] basefinderhandle The BaseFinder handle
 *  \param[in] function         The ID of the function
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
SSNBaseFinder_pcUnsubscribe(ssn_hbasefinder_t                 basefinderhandle,
                            ssn_basefinder_progresscb_flist_t function);

/**
 *  \brief  Check whether a given function is subscribed
 *
 *  \param[in]  basefinderhandle The BaseFinder handle
 *  \param[in]  function         The ID of the function
 *  \param[out] issubscribed     True or false
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
SSNBaseFinder_pcIsSubscribed(ssn_hbasefinder_t                  basefinderhandle,
                             ssn_basefinder_progresscb_flist_t  function,
                             bool                               *issubscribed);

/**
 *  \brief add pointer to escape variable to monitor escape
 *
 *  \param[in]  basefinderhandle The BaseFinder handle
 *  \param[in]  pescape          The pointer to the esc value
 *
 *  When a pointer different from NULL is used the calculations will stop as soon 
 *  as value equals true.                 
 */
FW_EXPORT void
SSNBaseFinder_setEscapePointer(ssn_hbasefinder_t     basefinderhandle,
                               bool                 *pescape);

/**
 *  \brief  check if BaseFinder was escaped
 *
 *  \param[in] basefinderhandle The BaseFinder handle
 *
 *  \return Returns true if stream was escaped. 
 */
FW_EXPORT bool
SSNBaseFinder_isEscaped(ssn_hbasefinder_t  basefinderhandle);

/**
* Returns the report with details about the last executed
* SSNBaseFinder_createStationList() or SSNBaseFinder_createSBF().
*
* \param[in]  basefinderhandle The BaseFinder handle
* \param[out] report           Output parameter to store a pointer to the
*                              allocated report.
*
* \note Ownership of the report string is transferred to the caller. Hence,
*       \p *report should be deallocated using free().
*/
FW_EXPORT ssn_error_t
SSNBaseFinder_getLastReport(ssn_hbasefinder_t basefinderhandle, char** report);

#ifdef __cplusplus
}
#endif

#endif // SSNBASEFINDER_H
/* END OF HEADER FILE ========================================================*/
