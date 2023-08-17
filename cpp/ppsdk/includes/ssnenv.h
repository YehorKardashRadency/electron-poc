/**
 *  \file
 *  \ingroup  SsnEnv
 *  \brief    Declaration of functions used to read the environment
 *
 *  \par Copyright:
 *    (c) 2007 - 2016 Septentrio Satellite Navigation NV/SA, Belgium
 *
 */
#ifndef SSNENV_H
/** To avoid multiple inclusions */
#define SSNENV_H 1

#include "ssntypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief  Reads the environment setting (either from the settings file if found there, else from the system environment) 
 *  
 *  The environment settings can be overwritten by creating a file ".septentrio/receiver.conf" in the user's 
 *  home (Linux) or UserProfile (Windows) folder. When trying to retrieve an environment setting this method
 *  tries first to read it from the "receiver.conf" file, if the file is not present or the setting is not
 *  available an attempt is made to read the setting from the system's envrionment.
 *  
 *  \note the function "ssnenv_useSettingsFile(false)" can be used to ignore the settings file and only use the system's
 *        environment
 *
 *  \param  name  [in]  The name of the environment setting that should be read.
 *
 *  \return
 *    Returns value of the given environment setting.
 */
/*@observer@*/ /*@null@*/ FW_EXPORT char* ssnenv_getEnv(const char* name);

/**
*  \brief function that resets the initialized flag so that the settings file or system environment is re-read
*/
FW_EXPORT void ssnenv_resetInitialized();

/**
*  \brief function that enables/disables reading of the enviroment settings from the settings file (enabled by default)
*  
 * \param enable if true the settings file is tried when using the function ssnenv_getEnv (default), else it isn't
*/
FW_EXPORT void ssnenv_useSettingsFile(bool enable);

#ifdef __cplusplus
}
#endif

#endif
/* END OF HEADER FILE ========================================================*/
