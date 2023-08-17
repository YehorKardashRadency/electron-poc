/*! \file
 *  \ingroup  BaseFinder
 *  \brief    Contains constellation definitions to be used in BaseFinder
 *
 *  \par Copyright:
 *    (c) 2006 - 2017 Septentrio Satellite Navigation NV/SA, Belgium
 */

#ifndef BASEFINDER_CONSTELLATIONS
#define BASEFINDER_CONSTELLATIONS

// make sure the enums can be used as bit fields
/** The different constellations that can be used by BaseFinder */
typedef enum
{
  SSNBASEFINDER_GPS     = 0x01,  //!< GPS satellite system
  SSNBASEFINDER_GLONASS = 0x02,  //!< GLONASS satellite system
  SSNBASEFINDER_GALILEO = 0x04,  //!< Galileo satellite system
  SSNBASEFINDER_BEIDOU  = 0x08,  //!< BEIDOU satellite system
  SSNBASEFINDER_SBAS    = 0x10,  //!< SBAS satellite system
  SSNBASEFINDER_QZSS    = 0x20,  //!< QZSS satellite system
  SSNBASEFINDER_IRNSS   = 0x40,  //!< IRNSS satellite system
} ssn_basefinder_constellations_t;

#endif // BASEFINDER_CONSTELLATIONS
