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

/**
 * @brief Sets the white balance control. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function sets the white balance for a specific source, color, color temperature and control.
 *
 * @param[in] inputSrc                    - Source of input to be set. Valid values are ( "HDMI", "TV", "AV" )
 * @param[in] colorTemp                   - Color temperature value to be set. Valid values are ( "custom", "normal", "cool", "warm" )
 * @param[in] color                       - Color to be set. Valid values are ( "red", "blue", "green" )
 * @param[in] ctrl                        - Control to be set. Valid values are ( "gain", "offset" )
 * @param[in] value                       - Values to be set for the specific control. Valid range : for gain is ( 0 to 2047 ), for offset is ( -1024 to 1024 )
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
tvError_t SetWBctrl(char *inputSrc, char *colorTemp,char *color, char *ctrl, int value);

/**
 * @brief Gets the current white balance control. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function gets the white balance for a specific source, color, color temperature and control.
 *
 * @param[in] inputSrc                    - Source of input. Valid values are ( "HDMI", "TV", "AV" )
 * @param[in] colortemp                   - Color temperature value. Valid values are ( "custom", "normal", "cool", "warm" )
 * @param[in] color                       - Color. Valid values are ( "red", "blue", "green" )
 * @param[in] ctrl                        - Control. Valid values are ( "gain", "offset" )
 * @param[out] value                      - Values for the specific control. Valid range : for gain is ( 0 to 2047 ), for offset is ( -1024 to 1024 )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                    - Success
 * @retval tvERROR_INVALID_PARAM           - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE           - When the input value is not valid
 * @retval tvERROR_GENERAL                - Underlying failures - SoC, memory, etc
 * 
 * @pre tvInit() should be called before calling this API
 */
tvError_t GetWBctrl(char *inputSrc, char *colortemp, char *color, char *ctrl, int *value);

/**
 * @brief Saves the color temperature to driver cache. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function saves the color temperature for user to driver cache file
 *
 * @param[in] rgbType               - RGB type. Valid value will be a member of ::tvRGBType_t
 * @param[in] value                 - Color temperature value to be set. Valid range : for gain (0 to 2047) , for offset (-1024 to 1024)
 * @param[in] boost                 - boost or nonboost
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
tvError_t SaveColorTemperatureUser(tvRGBType_t rgbType, int value,int boost);


/**
 * @brief Gets the supported HLG modes and their count. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function returns the supported HLG modes and their count
 *
 * @param[out] dvModes[]            - List of available HLG modes. Refer ::pic_modes_t and ::tvDolbyMode_t @n
 *                                    Valid values are "dark" and & "bright" for ::pic_modes_t.name @n
 *                                    Valid values are member of ::tvDolbyMode_t tvHLGMode_Dark and ::tvDolbyMode_t tvHLGMode_Bright @n
 *                                    for ::pic_modes_t.value.
 * @param[out] count                - Count of supported HLG modes. Max and min is 2
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 * 
 * @pre tvInit() should be called before calling this API
 */
tvError_t GetTVSupportedHLGModesODM(pic_modes_t *dvModes[],unsigned short *count);

/**
 * @brief Sets the HLG mode. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function sets the HLG mode in Dolby vision core.
 * The change takes effect for current primary video source selected, primary video format if handled via Dolby vision core 
 * and picture mode selected, but not saved for future use. The value is discarded if primary video format or 
 * primary video source or picture mode changes.
 *
 * @param[in] hlgMode              - HLG mode to be set. Valid values can be one of the 
 *                                     strings from ::pic_modes_t.name parameter returned by GetTVSupportedHLGModesODM
 *
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 *
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre tvInit() should be called before calling this API
 */
tvError_t SetTVHLGModeODM(const char * hlgMode);

/**
 * @brief Gets the supported HDR10 modes and their count. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function returns the supported HDR10 modes and their count
 *
 * @param[out] dvModes[]            - List of available HDR10 modes. Refer ::pic_modes_t and ::tvDolbyMode_t @n
 *                                    Valid values are "dark" and & "bright" for ::pic_modes_t.name @n
 *                                    Valid values are member of ::tvDolbyMode_t tvHDR10Mode_Dark and ::tvDolbyMode_t tvHDR10Mode_Bright @n
 *                                    for ::pic_modes_t.value.
 * @param[out] count                - Count of supported HDR10 modes. Max and min is 2
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre tvInit() should be called before calling this API
 */
tvError_t GetTVSupportedHDR10ModesODM(pic_modes_t *dvModes[],unsigned short *count);

/**
 * @brief Sets the HDR10 mode. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function sets the HDR10 mode in Dolby vision core.
 * The change takes effect for current primary video source selected, primary video format if handled via Dolby vision core 
 * and picture mode selected, but not saved for future use. The value is discarded if primary video format or 
 * primary video source or picture mode changes.
 *
 * @param[in] hdr10Mode              - HDR10 mode to be set. Valid values can be one of the 
 *                                     strings from ::pic_modes_t.name parameter returned by GetTVSupportedHDR10ModesODM
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre tvInit() should be called before calling this API
 */
tvError_t SetTVHDR10ModeODM(const char * hdr10Mode);

#ifdef __cplusplus
}
#endif

#endif // End of _TV_SETTINGS_ODM_H

/** @} */ // End of TV_SETTINGS_ODM_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
