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
* @defgroup TV_SETTINGS_ODM_H TV Types Header
* @{
*/

#ifndef _TV_SETTINGS_ODM_H
#define _TV_SETTINGS_ODM_H
#include "tvTypesODM.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Stores the new gamma test points in non volatile area. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function stores the new gamma test points in non volatile area.
 *
 * @param[in] length                  - Length of the gamma array of values.
 * @param[in] gamma                   - Array of gamma values to be stored.
 *
 * @pre tvInit() should be called before calling this API
 */
void SetGammaTestPoint( int length, unsigned short gamma[ ]);

/**
 * @brief Stores the new gamma test points in non volatile area. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function returns the gamma test points that is default or the last stored value using SetGammaTestPoint API.
 *
 * @param[out] length                  - Length of the gamma array of values.
 * @param[out] gamma                   - Array of gamma values to be returned.
 *
 * @pre tvInit() should be called before calling this API
 */
void GetGammaTestPoint( int *length, unsigned short gamma[]);

#ifdef __cplusplus
}
#endif

#endif // End of _TV_SETTINGS_ODM_H

/** @} */ // End of TV_SETTINGS_ODM_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
