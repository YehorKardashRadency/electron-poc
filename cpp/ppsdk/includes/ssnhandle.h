/**
 *  \file     ssnhandle.h
 *  \ingroup  SSNHandle
 *  \brief    SSN safe handle definition.
 *
 *  \par Copyright:
 *    (c) 2007 - 2008 Septentrio Satellite Navigation NV/SA, Belgium
 *
 *  The SSN safe handle module provides security functionality to validate
 *  handles.
 */

#ifndef SSNHANDLE_H
/** To avoid multiple inclusions */
#define SSNHANDLE_H 1

/* Includes ==(needed for self-contained / -consistent)=======================*/

#include "ssntypes.h" /* SSN types */

/* Declarations ==============================================================*/

/* Constants & Macros --------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/* Public Variables/Structs --------------------------------------------------*/

#pragma pack(push, 4)

/**
 * \brief Generic SSN safe handle.
 */
typedef struct ssn_hhandle_s
{
  /*@shared@*/ void *handle_data;  /**< Pointer to the actual handle data (real pointer) */
  uint32_t           magicnbr;     /**< Magic number */
} ssn_hhandle_t;

#pragma pack(pop)

/* Public Procedures ---------------------------------------------------------*/

#endif
/* END OF HEADER FILE ========================================================*/
