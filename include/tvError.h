/*
* If not stated otherwise in this file or this component's Licenses.txt file the
* following copyright and licenses apply:
*
* Copyright 2016 RDK Management
*
* Licensedunder the Apache License, Version 2.0 (the "License");
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
* @addtogroup TV_Settings_HAL TV Settings HAL
* @{
**/

/**
* @defgroup TV_Error TV Error
* @{
**/

#ifndef _TV_ERROR_H
#define _TV_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif
 
/* Error codes returned by tvSetting HAL */
typedef enum
{
     
    tvERROR_NONE = 0,                   //!< No error
    tvERROR_GENERAL,                    //!< Other errors from drivers
    tvERROR_OPERATION_NOT_SUPPORTED,    //!< Operation not supported
    tvERROR_INVALID_PARAM,              //!< Invalid Parameter error
    tvERROR_INVALID_STATE               //!< Invalid State error
}tvError_t;

#ifdef __cplusplus
}
#endif

#endif // _TV_ERROR_H

/** @} */ // End of TV_Error
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of HPK
