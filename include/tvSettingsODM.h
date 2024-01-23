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
 * @brief Gets supported video formats of the system. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function returns all the supported content formats. 
 *
 * @param[out] videoFormats    - Bitwise ORed values of enum ::tvVideoHDRFormat_t
 * @param[out] numberOfFormats - Count of supported video formats. Min should be 1
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre tvInit() should be called before calling this API
 */
tvError_t GetSupportedVideoFormatsODM(unsigned int * videoFormats,unsigned short *numberOfFormats);

/**
 * @brief Gets current video format. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function gets the video format value of the current primary video played on TV
 *
 * @return tvVideoHDRFormat_t 
 *
 * @retval tvVideoHDRFormat_SDR              - SDR format
 * @retval tvVideoHDRFormat_HLG              - HLG Format
 * @retval tvVideoHDRFormat_HDR10            - HDR10 format
 * @retval tvVideoHDRFormat_HDR10PLUS        - HDR10 plus format
 * @retval tvVideoHDRFormat_DV               - DV format.
 *
 * @pre tvInit() should be called before calling this API
 */
tvVideoHDRFormat_t GetCurrentVideoFormatODM(void);

/**
 * @brief Gets supported backlight dimming modes of the system.  To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function returns all the supported backlight dimming modes.
 *
 * @param[out] dimmingModes    - array of dimming modes names. Valid values are "fixed", "local" and "global"
 * @param[out] numDimmingModes - Count of supported dimming modes. Min should be 1
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre tvInit() should be called before calling this API
 */
tvError_t GetTVSupportedDimmingModesODM(char **dimmingModes,unsigned short *numDimmingModes);

/**
 * @brief Returns ::tvhdr_type_t enum for given ::tvVideoHDRFormat_t enum. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function ::tvhdr_type_t enum for given ::tvVideoHDRFormat_t enum.
 *
 * @param[in] videoFormat            - Video format. Valid values can be member of ::tvVideoHDRFormat_t
 *
 * @return int - Valid values can be member of ::tvhdr_type_t
 *
 * @pre tvInit() should be called before calling this API
 */
int ConvertVideoFormatToHDRFormatODM(tvVideoHDRFormat_t videoFormat);

/**
 * @brief Returns ::tvVideoHDRFormat_t enum for given ::tvhdr_type_t enum. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function ::tvhdr_type_t enum for given ::tvhdr_type_t enum.
 *
 * @param[in] hdrFormat            - hdr format. Valid values can be member of ::tvhdr_type_t
 *
 * @return int - Valid values can be member of ::tvVideoHDRFormat_t
 *
 * @pre tvInit() should be called before calling this API
 */
 int ConvertHDRFormatToContentFormatODM(tvhdr_type_t hdrFormat);

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
 * @brief Gets the current CMS default value. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function returns the default CMS value
 *
 * @param[out] component_type      - Component type. Valid value will be a member of ::tvComponentType_t
 *
 * @return int
 *
 * @retval 15                       - Luma default value
 * @retval 50                       - Hue or saturation default value
 * @retval -1                       - Input parameter is invalid
 *
 * @pre tvInit() should be called before calling this API
 */
 int GetCMSDefault(tvComponentType_t component_type);


/**
 * @brief Returns Panel ID information. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function returns the panel ID string.
 *
 * @param[out] panelid            - Panel ID string to be returned.
 *
 * @return int - Valid values can be member of ::tvVideoHDRFormat_t
 *
 * @retval 0                       - Success
 * @retval -1                      - General failure.
 *
 * @pre tvInit() should be called before calling this API
 */
int GetPanelIDODM(char* panelid);

/**
 * @brief Reads the WB/Gamma/Peak brightness calibration info and passes it to the PQ drivers at bootup. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function reads the WB/Gamma/Peak brightness calibration info and passes it to the PQ drivers at bootup.
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
tvError_t TvSyncCalibrationInfoODM();       //Reading from Serialisation area calib values (gamma/wb/peak brightness) and update drivers.


/**
 * @brief Reads PQ capability information sections from the specified file. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function reads PQ capability information sections from the specified file. The file format is predefined and a template file is supplied by RDK.
 *
 * @param[in] file               - The name of the file from which PQ capability information sections need to be read.
 * @param[out] cpybuffer         - The return buffer (max size 512 bytes), where PQ capability information sections are copied to.
 * @param[in] searchstring       - Heading of the section.
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
tvError_t ReadAllModeConfigfileODM(const char *file, char *cpybuffer, const char *searchstring);


/**
 * @brief Gets the supported DV modes and their count.  To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function returns the supported Dolby Vision modes and their count
 *
 * @param[out] dvModes[]            - List of available DV modes. Refer ::pic_modes_t and ::tvDolbyMode_t @n
 *                                    Valid values are "dark" and & "bright" for ::pic_modes_t.name @n
 *                                    Valid values are member of ::tvDolbyMode_t tvDolbyMode_Dark and ::tvDolbyMode_t tvDolbyMode_Bright @n
 *                                    for ::pic_modes_t.value.
 * @param[out] count                - Count of supported DV modes. Max and min is 2
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
tvError_t GetTVSupportedDolbyVisionModesODM(pic_modes_t *dvModes[],unsigned short *count);


/**
 * @brief Sets dolby vision mode. To be deprecated soon.
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function sets the Dolby vision mode in Dolby vision core.
 * The change takes effect for current primary video source selected, primary video format if handled via Dolby vision core 
 * and picture mode selected, but not saved for future use. The value is discarded if primary video format or 
 * primary video source or picture mode changes.
 *
 * @param[in] dolbyMode              - Dolby vision mode to be set. Valid values can be one of the 
 *                                     strings from ::pic_modes_t.name parameter returned by GetTVSupportedDolbyVisionModesODM
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
 *
 * @see GetTVDolbyVisionMode()
 */
tvError_t SetTVDolbyVisionModeODM(const char * dolbyMode);


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

/**
 * @brief Gets current video Source
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function gets the video Source
 *
 * @param[out] currentSource                 - Current video source. Valid value will be a member of ::tvVideoSrcType_t
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentSource(tvVideoSrcType_t *currentSource);

/**
 * @brief Sets wake-up configuration
 * @note SOC vendors can stub these ODM functions and mark it as weak
 *
 * This function enables/disables the specific deepsleep wake-up source
 *
 * @param[in] src_type                     - Wakeup source type. Valid value will be a member of ::tvWakeupSrcType_t
 * @param[in] value                        - Enable/disable wakeup source to be set ( 0 for @a disable and 1 for @a enable )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, write failure, etc
 *
 * @pre TvInit() should be called before calling this API
*/
tvError_t SetWakeupConfig(const tvWakeupSrcType_t src_type, const bool value);

#ifdef __cplusplus
}
#endif

#endif // End of _TV_SETTINGS_ODM_H

/** @} */ // End of TV_SETTINGS_ODM_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK