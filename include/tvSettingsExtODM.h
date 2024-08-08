/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2016 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License" );
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
* @defgroup TV_Settings_EXT_ODM TV Settings Header
* @{
*/

#ifndef _TV_SETTINGS_EXT_ODM_H
#define _TV_SETTINGS_EXT_ODM_H
#include <vector>
#include <string>
#include "tvError.h"
#include "tvTypes.h"
#include "tvTypesODM.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Reads PQ capability information sections PQ capability configuration file. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function reads PQ capability information sections from the PQ capability configuration file. @n
 * The file format is predefined and a template file is supplied by RDK.
 *
 * @param[in] param               - Heading of the section in PQ capability configuration file.
 * @param[out] info               - info holds the capability details of all picture quality params.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre tvInit() should be called before calling this API
 */
int ReadCapablitiesFromConfODM(std::string param, capDetails_t& info);

/**
 * @brief Gets the current white balance info. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function gets the White balance info into the vectors
 *
 * @param[out] params               - WB info param. Valid values for : wbControls is ( "gain", "offset" ), wbGain is (0 to 2047), wbOffset is (-1024 to 1024))
 * @param[out] selector             - Selector vector. Valid values are ( "color temp", "input" )
 * @param[out] colorTmp             - Color temperature vector. Valid values are ( "custom", "normal", "cool", "warm" )
 * @param[out] input                - Input source vector. Valid values are ( "TV", "HDMI", "AV" )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                   - Success
 * @retval tvERROR_INVALID_PARAM          - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE          - When the input value is not valid
 * @retval tvERROR_GENERAL                - Underlying failures - SoC, memory, etc
 *
 * @pre tvInit() should be called before calling this API
 */
 tvError_t GetWbInfo(getWBInfo_t* params, std::vector<std::string> &selector, std::vector<std::string> &colorTmp, std::vector<std::string> &input);

#ifdef __cplusplus
}
#endif

#endif // End of _TV_SETTINGS_EXT_ODM_H

/** @} */ // End of TV_Settings_EXT_ODM
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
