/**
 *  \file     ssnsbfanalyze.h
 *  \ingroup  SSNSBFAnalyze
 *  \brief    API of the SBF Analyze module.
 *
 *  \par Copyright:
 *    (c) 2008 Septentrio Satellite Navigation NV/SA, Belgium
 *
 *  \note The SBF stream module also contains the progress callback
 *        functionality for the SBF analyze module.
 *
 *  Some utilities to analyze the contents of an SBF stream.
 */
#ifndef SSNSBFANALYZE_H
/** To avoid multiple inclusions */
#define SSNSBFANALYZE_H 1

/* Includes ==(needed for self-contained / -consistent)=======================*/

#include "sbfdef.h"       /* SBF definition */
#include "sbfsigtypes.h"  /* SBF signal types */
#include "ssnerror.h"     /* SSN error */
#include "ssnsbfstream.h" /* SBF stream module */
#include "ssntypes.h"     /* SSN types */

#include <stddef.h>       /* size_t */

/* Declarations ==============================================================*/

/* Constants & Macros --------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/* Public Variables/Structs --------------------------------------------------*/
#pragma pack(push, 4)

/**
 * \brief PVT mode percentages.
 */
typedef struct ssn_pvtmode_percentages_s
{
  float     npa;        /**< No PVT available */
  float     sp;         /**< Stand-Alone PVT */
  float     dp;         /**< Differential PVT */
  float     fl;         /**< Fixed location */
  float     rfia;       /**< RTK with fixed ambiguities */
  float     rfla;       /**< RTK with float ambiguities */
  float     sap;        /**< SBAS aided PVT */
  float     mrfia;      /**< Moving-base RTK with fixed ambiguities */
  float     mrfla;      /**< Moving-base RTK with float ambiguities */
  float     pppfia;     /**< Precise Point Positioning (PPP) with fixed ambiguities */
  float     pppfla;     /**< Precise Point Positioning (PPP) with float ambiguities */
  uint32_t  checktotal; /**< Total number of checked SBF blocks */  
} ssn_pvtmode_percentages_t;

/**
 * \brief PVT error percentages.
 */
typedef struct ssn_pvterror_percentages_s
{
  float     ne;           /**< No error */
  float     nem;          /**< Not enough measurements */
  float     neea;         /**< Not enough ephemirides available */
  float     dtl;          /**< DOP too large (larger than 15) */
  float     ssrtl;        /**< Sum of squared residuals too large */
  float     nc;           /**< No convergence */
  float     nemaor;       /**< Not enough measurements after outlier rejection */
  float     popdtel;      /**< Position output prohibited due to export laws */
  float     nedca;        /**< Not enough differential corrections available */
  float     bscu;         /**< Base station coordinates unavailable */
  float     total;        /**< Total error percentage */
  uint32_t  checktotal;   /**< Total number of checked SBF blocks */
  uint32_t  checkerror;   /**< Number of erroneous checked SBF blocks */
} ssn_pvterror_percentages_t;

/**
 * \brief Satellite usage attributes.
 */
typedef struct ssn_pvt_satusage_s
{
  uint8_t       svid;       /**< Satellite ID */
  uint8_t       freqnr;     /**< GLONASS frequency number, 0 if not used */
  SignalType_t  signaltype; /**< Signal type */
} ssn_pvt_satusage_t;

/**
 * \brief Tracked satellites attributes.
 */
typedef struct ssn_tracked_satellites_s
{
  uint8_t       svid;                 /**< Satellite ID */
  uint8_t       freqnr;               /**< GLONASS frequency number, 0 if not used */
  bool          signaltype[SIG_LAST]; /**< List of tracked signals */
} ssn_tracked_satellites_t;
#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

/* Public Procedures ---------------------------------------------------------*/

/**
 *  \brief  Get the PVT mode percentages
 *
 *  \param  sbfstreamhandle [in]  The SBF stream containing PVT data
 *  \param  sbfid           [in]  The ID of the SBF block to use
 *  \param  percentages     [out] Structure containing the different percentages
 *
 *  Compute the percentage of each PVT mode available in an SBF stream from SBF
 *  blocks with the given SBF ID.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFAnalyze_getPVTModePercentages(ssn_hsbfstream_t            sbfstreamhandle,
                                    SBFID_t                     sbfid,
                                    ssn_pvtmode_percentages_t  *percentages);

/**
 *  \brief  Get the PVT error percentages
 *
 *  \param  sbfstreamhandle [in]  The SBF stream containing PVT data
 *  \param  sbfid           [in]  The ID of the SBF block to use
 *  \param  percentages     [out] Structure containing the different percentages
 *
 *  Compute the percentage of each PVT error present in an SBF stream from SBF
 *  blocks with the given SBF ID.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFAnalyze_getPVTErrorPercentages(ssn_hsbfstream_t             sbfstreamhandle,
                                     SBFID_t                      sbfid,
                                     ssn_pvterror_percentages_t  *percentages);

/**
 *  \brief  Check if a specific satellite was used when computing a PVT
 *
 *  \param  sbfstreamhandle [in]  The SBF stream containing PVT data
 *  \param  gnsstime        [in]  GNSS time (seconds) of the epoch
 *  \param  pvt_satusage    [in]  Satellite information
 *  \param  isused          [out] Boolean value set to true if used, false if not
 *
 *  Check the PVT data from a specific epoch (or the first epoch with PVT after
 *  the given epoch) to see if a specified satellite has been used in the PVT
 *  computations of that epoch.
 *
 *  \note This function requires the PVTResiduals SBF block to be present in the SBF stream.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFAnalyze_isSatelliteUsed(ssn_hsbfstream_t    sbfstreamhandle,
                              double              gnsstime,
                              ssn_pvt_satusage_t  pvt_satusage,
                              bool               *isused);

/**
 *  \brief  List all used satellites and signals at a given epoch
 *
 *  \param  sbfstreamhandle [in]  The SBF stream handle
 *  \param  gnsstime        [in]  GNSS time (in seconds) of the epoch
 *  \param  size            [out] Size or number of elements
 *  \param  pvt_satusage    [out] List of used satellites
 *
 *  \post \p size contains either the number of bytes that need to be allocated
 *        to hold the \p pvt_satusage array, or the number of elements contained
 *        in the \p pvt_satusage array.
 *
 *  This function will create a list of the used satellites, frequency numbers
 *  and signal types at a given GNSS time stamp.
 *
 *  This function uses the so called "double-call" mechanism. The first time the
 *  function is called \p NULL is passed as the \p pvt_satusage parameter and
 *  \p size will contain the number of bytes that need to be allocated to hold
 *  the resulting array of \p pvt_satusage_t elements.\n
 *  The second time the function is called the \p pvt_satusage array will be
 *  filled and \p size will contain the number of elements the array contains.
 *  It is recommended to set buffersize to the size of the allocated memory
 *  before the second call.
 *
 *  \note This function requires the PVTResiduals SBF block to be present in the SBF stream.
 *  \note If a satellite signal is tracked on multiple antenna's this will lead
 *        to duplicate entries in the output.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFAnalyze_listUsedSatellites(ssn_hsbfstream_t     sbfstreamhandle,
                                 double               gnsstime,
                                 size_t              *size,
                                 ssn_pvt_satusage_t  *pvt_satusage);

/**
 *  \brief  Check if a specific satellite was tracked when computing a PVT
 *
 *  \param  sbfstreamhandle   [in]  The SBF stream containing PVT data
 *  \param  gnsstime          [in]  GNSS time (seconds) of the epoch
 *  \param  tracked_satellite [in]  Satellite information
 *  \param  istracked         [out] Boolean value set to true if used, false if not
 *
 *  Check the PVT data from a specific epoch (or the first epoch with PVT after
 *  the given epoch) to see if a specified satellite has been tracked in the PVT
 *  computations of that epoch.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFAnalyze_isSatelliteTracked(ssn_hsbfstream_t           sbfstreamhandle,
                                 double                     gnsstime,
                                 ssn_tracked_satellites_t   tracked_satellite,
                                 bool                      *istracked);

/**
 *  \brief  List all tracked satellites and signals at a given epoch
 *
 *  \param  sbfstreamhandle     [in]  The SBF stream handle
 *  \param  gnsstime            [in]  GNSS time (in seconds) of the epoch
 *  \param  size                [out] Size or number of elements
 *  \param  tracked_satellites  [out] List of used satellites
 *
 *  \post \p size contains either the number of bytes that need to be allocated
 *        to hold the \p tracked_satellites array, or the number of elements
 *        contained in the \p tracked_satellites array.
 *
 *  This function will create a list of the tracked satellites, frequency
 *  numbers and signal types at a given GNSS time stamp.
 *
 *  This function uses the so called "double-call" mechanism. The first time the
 *  function is called \p NULL is passed as the \p tracked_satellites parameter
 *  and \p size will contain the number of bytes that need to be allocated to
 *  hold the resulting array of \p tracked_satellites_t elements.\n
 *  The second time the function is called the \p tracked_satellites array will
 *  be filled and \p size will contain the number of elements the array contains.
 *  It is recommended to set buffersize to the size of the allocated memory
 *  before the second call.
 *
 *  \return The function returns an \ref ssnerror::ssn_error_t with either: 
 *          \li \ref ssnerror::SSNERROR_WARNING_OK "SSNERROR_WARNING_OK" if 
 *              the function was executed successfully 
 *          \li an error code describing the error
 *             (see \ref ssnerror::ssn_error_codes_t).
 */
FW_EXPORT ssn_error_t
SSNSBFAnalyze_listTrackedSatellites(ssn_hsbfstream_t          sbfstreamhandle,
                                    double                    gnsstime,
                                    size_t                   *size,
                                    ssn_tracked_satellites_t *tracked_satellites);

#ifdef __cplusplus
}
#endif

#endif
/* END OF HEADER FILE ========================================================*/
