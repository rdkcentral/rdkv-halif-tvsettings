/*
* If not stated otherwise in this file or this component's LICENSE file the
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
 * @addtogroup HPK Hardware Porting Kit
 * @{
 * @par The Hardware Porting Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their ports before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware Porting Kit effectively enables an OEM and/or SOC
 * vendor to self-certify their own Video Accelerator devices, with minimal RDKM
 * assistance.
 *
 */

/**
 * @addtogroup TV_Settings TV Settings Module
 * @{
 */


/**
* @addtogroup TV_Settings_HAL TV Settings HAL
* @{
*/

/**
* @defgroup TV_Error_H TV Error Header
* @{
*/


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

#endif //_TV_ERROR_H

/** @} */ // End of TV_Error_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
