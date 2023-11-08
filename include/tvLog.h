/*
* If not stated otherwise in this file or this component's Licenses.txt file the
* following copyright and licenses apply:
*
* Copyright 2016 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**
* @addtogroup HPK HPK
* @{
**/

/**
* @defgroup TV_Settings TV Settings Module
* @{
**/

/**
* @defgroup TV_Settings_HAL TV Settings HAL
* @{
**/

/**
* @defgroup TV_Log_H TV Log Header
* @{
**/

#ifndef _TV_LOG_H
#define _TV_LOG_H


#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ERROR(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "ERROR", ##__VA_ARGS__);}while(0); //!< Macro to log ERROR messages

#define INFO(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "INFO", ##__VA_ARGS__);}while(0); //!< Macro to log INFO messages

#ifdef DEBUG_ENABLED 

#define DEBUG(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "DEBUG", ##__VA_ARGS__);}while(0);
#else
#define DEBUG(text, ...) //!< Macro to log DEBUG messages
#endif


#ifdef __cplusplus
}
#endif

#endif // _TV_LOG_H

/** @} */ // End of TV_Log_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
