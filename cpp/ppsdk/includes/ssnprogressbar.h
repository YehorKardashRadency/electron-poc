/**
 * \file ssnprogressbar.h
 *
 * \brief Septentrio's implementation of a textual progressbar
 *
 *
 * (c) 2017 Septentrio nv/sa, Belgium
 */

#ifndef SSNPROGRESSBAR_H
#define SSNPROGRESSBAR_H 1

#include "ssntypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief prints the progress bar
 *
 *  \param prefix the prefix to print before the progress bar
 *  \param percentage the percentage the progress bar should indicate */
void FW_EXPORT ssnPrintProgressBar(char *prefix, float percentage);


/** \brief clears the progress bar */
void FW_EXPORT ssnClearProgressBar();

#ifdef __cplusplus
}
#endif

#endif
/* End of "ssnprogressbar.h" */

