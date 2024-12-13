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
* @defgroup TV_Settings_H TV Settings Header
* @{
*/

#ifndef _TV_SETTINGS_H
#define _TV_SETTINGS_H

#include <stdbool.h>
/*
 *@todo: Instead of tv add prefix tvSettings ie: tvSettingsError.h and tvSettingsType.h
*/
#include "tvError.h"
#include "tvTypes.h"
#include "tvSettingsODM.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief  Initialises TV Settings HAL
 *
 * This function is used to initialize the TV Setting HAL APIs.
 * All dependent vendor specific driver modules for implementing TV Settings HAL
 * are expected to be initialised when this call return successfully. Calling TvInit() API 
 * more than once without a TvTerm() API call should return failure. Any TV Settings
 * HAL API called before TvInit() API should return failure.
 *
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_STATE     - Interface is already initialized
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 * @see TvTerm()
 *
 * @post TvTerm() must be called to to release resources.
 *
 */
tvError_t TvInit();

/**
 * @brief De-initialises TV Settings HAL
 *
 * This function should terminate the TV Settings HAL APIs.
 * All dependent vendor specific driver modules for implementing TV Settings HAL
 * are expected to be terminated when this call return successfully. Calling TvTerm() API 
 * more than once without a TvInit() API call should return failure. Any TV Settings
 * HAL API called after TvTerm() and before TvInit() API should return failure.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_STATE     - Interface is already terminated
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 *
 */
 tvError_t TvTerm();

/**
 * @brief Registers the video format change callback
 *
 * This function registers a callback for video format change event.
 * Once registered, the callback function will be called by the TV Settings HAL implementation
 * whenever change in video format is detected at the start the primary video playback, with
 * right video format value detected. When the primary video playback stops, the TVSettings 
 * HAL will callback notifying SDR format as the default.
 * 
 * @param[in] cbData                - Callback data. Please refer ::tvVideoFormatCallbackData
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t RegisterVideoFormatChangeCB(tvVideoFormatCallbackData *cbData);
    
/**
 * @brief Registers the VideoContent FMM change callback
 *
 * This function registers a callback for the playback Filmmaker mode change event.
 * Once registered, the callback function will be called by the TV Settings HAL implementation
 * whenever the system detects SEI content_type 0x01 and content_subtype 0x00 at the start of the 
 * primary video playback, with value tvContentType_FMM for FMM enter event. Whenever the system 
 * detects SEI content_type other than 0x01 or content_subtype other than 0x00 during middle of 
 * primary video playback or when playback finishes the callback function will be called with
 * with value tvContentType_NONE for FMM exit event. This applies only to IP video sources and 
 * Tuner video sources. AVI Infoframes for HDMI sources will be handled in dsHDMIIn through 
 * dsHdmiInRegisterAviContentTypeChangeCB.
 *
 * @param[in] cbData                - Callback data. Please refer::tvVideoContentCallbackData
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t RegisterVideoContentChangeCB(tvVideoContentCallbackData *cbData);

/**
 * @brief Registers the Video resolution change callback.
 *
 * This function registers a callback for Video resolution change event.
 * Once registered, the callback function will be called by the TV Settings HAL implementation
 * whenever change in video resolution is detected at the start the primary video playback, with
 * right video resolution value detected. When the primary video playback stops, the TVSettings 
 * HAL will not make any callback.
 *
 * @param[in] cbData                - Callback data. Please refer ::tvVideoResolutionCallbackData
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t RegisterVideoResolutionChangeCB(tvVideoResolutionCallbackData *cbData);

/**
 * @brief Registers the Video framerate change callback
 *
 * This function registers a callback for Video framerate change event.
 * Once registered, the callback function will be called by the TV Settings HAL implementation
 * whenever change in video framerate is detected at the start the primary video playback, with
 * right video framerate value detected. When the primary video playback stops, the TVSettings 
 * HAL will not make any callback.
 *
 * @param[in] cbData                - Callback function. Please refer ::tvVideoFrameRateCallbackData
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t RegisterVideoFrameRateChangeCB(tvVideoFrameRateCallbackData *cbData);


/**
 * @brief Gets supported video formats of the system. 
 *
 * This function returns all the supported content formats. 
 *
 * @param[out] videoFormats    - List of available video formats. Please refer ::tvVideoFormatType_t
 * @param[out] numberOfFormats - Count of supported video formats. Min should be 1. Max value is VIDEO_FORMAT_MAX.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t GetTVSupportedVideoFormats(tvVideoFormatType_t *videoFormats[],unsigned short *numberOfFormats);

/**
 * @brief Gets current video format
 *
 * This function gets the video format value of the current primary video played on TV.@n
 * Whenever no video is played this API always returns VIDEO_FORMAT_SDR.
 *
 * @param[out] videoFormat                    - Current video format. Valid value will be a member of ::tvVideoFormatType_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentVideoFormat(tvVideoFormatType_t *videoFormat);

/**
 * @brief Gets the current video resolution
 *
 * This function gets the video resolution of the current primary video played on TV
 * Whenever no video is played this API always returns tvVideoResolution_NONE for resolutionValue in 
 * tvResolutionParam_t structure and rest of the parameters of tvResolutionParam_t structure are returned as 0 value.
 * 
 * @param[out] res                      - Video resolution value. Valid value will be a member of ::tvResolutionParam_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                     - Success
 * @retval tvERROR_INVALID_PARAM            - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE            - Interface is not initialized
 * @retval tvERROR_GENERAL                  - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentVideoResolution(tvResolutionParam_t *res);

/**
 * @brief Gets current video framerate
 *
 * This function gets the video frame rate of the current primary video played on TV
 * Whenever no video is played this API always returns tvVideoFrameRate_NONE.
 * 
 * @param[out] format                   - Video frame rate value. Valid value will be a member of ::tvVideoFrameRate_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                     - Success
 * @retval tvERROR_INVALID_PARAM            - Parameter is invalid
 * @retval tvERROR_INVALID_STATE            - Interface is not initialized
 * @retval tvERROR_GENERAL                  - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentVideoFrameRate(tvVideoFrameRate_t *format);

/**
 * @brief Gets current video source selected
 *
 * This function gets the video source selected for the primary video.
 * Whenever no video is played this API always returns VIDEO_SOURCE_IP.
 *
 * @param[out] currentSource            - Video source value. Valid value will be a member of ::tvVideoSrcType_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                     - Success
 * @retval tvERROR_INVALID_PARAM            - Parameter is invalid
 * @retval tvERROR_INVALID_STATE            - Interface is not initialized
 * @retval tvERROR_GENERAL                  - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentVideoSource(tvVideoSrcType_t *currentSource);

/**
 * @brief Gets supported video sources of the system. 
 *
 * This function returns all the supported video sources.
 *
 * @param[out] videoSources    - List of available video sources. Please refer ::tvVideoSrcType_t
 * @param[out] numberOfSources - Count of supported video sources. Min should be 1, max should be VIDEO_SOURCE_MAX
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t GetTVSupportedVideoSources(tvVideoSrcType_t *videoSources[],unsigned short *numberOfSources);


/**
 * @brief Gets the current backlight value
 *
 * This function gets the current backlight value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] backlight       - Current backlight value. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetBacklight()
 */
tvError_t GetBacklight(int *backlight);

/**
 * @brief Sets the backlight value in the backlight hardware
 *
 * This function updates the new backlight value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved backlight value should be applied automatically whenever the  current picture mode, current primary video format
 * and current primary video source are again selected in future.
 *
 * @param[in] backlight            - Backlight value to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetBacklight()
 */
tvError_t SetBacklight(int backlight);

/**
 * @brief Saves the backlight value.
 *
 * This function saves the backlight value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved backlight value should be applied automatically whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current backlight value in backlight HW.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the backlight to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *                 
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveBacklight(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,int value);

/**
 * @brief Sets the backlight fade settings
 * 
 * This function will fade the backlight between 2 different backlight values specified in a given duration.
 * It will only set and does'nt save the value.
 * The function call is asynchronous and expected to return immediately after initiating the fading process.
 * If there is change in backlight value due to SetBacklight API call or a change initiated due to 
 * picture mode change or primary video source change or primary video format change, the fading stops instantly
 * and system jumps to the new backlight value.
 *
 * @param[in] from                  - Percentage of current backlight value from where fade starts. Valid range is (0 - 100)
 *                                  - If the value is <100 then before fade starts the backlight will jump to the from % of the currently @n
 *                                   set backlight value.
 * @param[in] to                    - Percentage of current backlight value where fade ends. Valid range is (0 - 100)
 * @param[in] duration              - Time duration for which the backlight needs to be faded to reach new value. Valid range is (0 - 10000 ms)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetBacklightFade(int from,int to,int duration);

/**
 * @brief Gets the backlight fade settings
 * 
 * This function returns current backlight fade settings and the progress level of the fade. 
 *
 * @param[out] from                  - Percentage of current backlight value from where fade starts. Valid range is (0 - 100)
 * @param[out] to                    - Percentage of current backlight value where fade ends. Valid range is (0 - 100)
 * @param[out] current               - Current faded percentage of current backlight value indicating the progress of the fade. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentBacklightFade(int *from,int *to,int *current);

/**
 * @brief Gets the supported backlight modes
 *
 * This function returns all supported backlight modes for the TV
 * The output has the bitwise OR-ed value of all the supported backlight modes (tvBacklightMode_t).
 *
 * @param[out] blModes            - Supported backlight modes. Valid values will be members of ::tvBacklightMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_INVALID_PARAM      - Parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * @retval tvERROR_GENERAL            - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetCurrentBacklightMode(),SetCurrentBacklightMode()
 */
tvError_t GetSupportedBacklightModes(int *blModes);

/**
 * @brief Gets current blacklight mode
 *
 * This function gets the current backlight mode.
 *
 * @param[out] blMode            - Current backlight mode. Valid value will be a member of ::tvBacklightMode_t
 *                                 If more than one value is received then INVALID_PARAM is returned.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - Parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetSupportedBacklightModes(),SetCurrentBacklightMode()
 */
tvError_t GetCurrentBacklightMode(tvBacklightMode_t *blMode);

/**
 * @brief Sets the backlight mode
 *
 * This function sets the backlight mode.
 *
 * @param[in] blMode                         - Backlight mode to be set. Valid value can be one of the member of ::tvBacklightMode_t".
 *                                             If more than one value is bitwise OR-ed and passed then the function should return invalid param.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized 
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetSupportedBacklightModes(),GetCurrentBacklightMode()
 */
tvError_t SetCurrentBacklightMode(tvBacklightMode_t blMode);


/**
 * @brief Gets supported backlight dimming modes of the system. 
 *
 * This function returns all the supported backlight dimming modes.
 *
 * @param[out] dimmingModes    - List of dimming modes. Please refer ::tvDimmingMode_t
 * @param[out] numDimmingModes - Count of supported dimming modes. Min should be 1, Max should be tvDimmingMode_MAX.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t GetTVSupportedDimmingModes(tvDimmingMode_t *dimmingModes[],unsigned short *numDimmingModes);

/**
 * @brief Sets the backlight dimming mode.
 *
 * This function updates the new dimming mode to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved dimming mode value should be applied automatically whenever the  current picture mode, current primary video format 
 * If peak brightness capablity of the panel changes as a result of dimming mode change reload the edid accordingly 
 * to update VSVDB string if video format currently playing is handled via Dolby Vision core.
 *
 * @param[in] dimmingMode           - Dimming mode to be set. Valid values are ( "local", "fixed", "global" )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 * @todo: instead of char* use tvDimmingMode_t enum
 */
tvError_t SetTVDimmingMode(const char *dimmingMode);

/**
 * @brief Gets the backlight dimming mode
 *
 * This function gets the current dimmimng mode value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] dimmingMode           - Current dimming mode. Valid values are ( "local", "fixed", "global" )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetTVDimmingMode(char *dimmingMode);

/**
 * @brief Saves the backlight dimming mode
 *
 * This function saves the backlight dimming mode in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved backlight dimming mode should be applied automatically whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current backlight dimming mode.
 * If peak brightness capablity of the panel changes as a result of dimming mode change in future reload the edid accordingly 
 * to update VSVDB string if current video format is handled via Dolby Vision core.
 *
 * @param[in] videoSrcType          - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] dimmingMode           - Value of the backlight dimming mode to be set. Valid value will be a member of ::tvDimmingMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t SaveTVDimmingMode(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,tvDimmingMode_t dimmingMode);

/**
 * @brief Sets the local dimming level
 *
 * This function updates the new local dimming level to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved local dimming level value should be applied automatically whenever the  current picture mode, current primary video format
 * If peak brightness capablity of the panel changes as a result of local dimming level change reload the edid accordingly 
 * to update VSVDB string if current video format is handled via Dolby Vision core.
 *
 * @param[in] ldimStateLevel                -  Dimming level to set. Valid value will be a member of ::ldimStateLevel_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetLocalDimmingLevel(ldimStateLevel_t ldimStateLevel);

/**
 * @brief Gets the current dimming level
 *
 * This function gets the current local dimming level for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] ldimStateLevel               - Current Dimming level returned. Valid value will be a member of ::ldimStateLevel_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetLocalDimmingLevel(ldimStateLevel_t *ldimStateLevel);

/**
 * @brief Saves local dimming level.
 *
 * This function saves the local dimming level in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved local dimming level should be applied automatically whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current local dimming level applied in local dimming module.
 * If peak brightness capablity of the panel changes as a result of local dimming level change in future reload the edid accordingly 
 * to update VSVDB string if current video format is handled via Dolby Vision core.
 *
 * @param[in] videoSrcType          - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] ldimStateLevel        - Value of the local dimming level to be set. Valid value will be a member of ::ldimStateLevel_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveLocalDimmingLevel(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,ldimStateLevel_t ldimStateLevel);

/**
 * @brief Sets the brightness value to driver register(s)
 *
 * This function updates the new brightness value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved brightness value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] brightness             - Brightness value to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetBrightness()
 */
tvError_t SetBrightness(int brightness);

/**
 * @brief Gets the current brightness value
 * 
 * This function gets the current brightness value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] brightness            - Current brightness value. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - Parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetBrightness()
 */
tvError_t GetBrightness(int *brightness);

/**
 * @brief Saves the brightness value
 *
 * This function saves the brightness value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved brightness value should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current brightness value applied in PQ module.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the brightness to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 * @todo: instead of int for pq_mode use tvPQModeIndex_t enum for all save API's
 */
tvError_t SaveBrightness(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,int value);

/**
 * @brief Sets the contrast value to driver register(s)
 *
 * This function updates the new contrast value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved contrast value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] contrast               - Contrast value to be set.Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetContrast()
 */
tvError_t SetContrast(int contrast);

/**
 * @brief Gets the current contrast value
 *
 * This function gets the current contrast value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] contrast               - Current contrast value. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_INVALID_PARAM      - Parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * @retval tvERROR_GENERAL            - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetContrast()
 */
tvError_t GetContrast(int *contrast);

/**
 * @brief Saves the contrast value
 *
 *
 * This function saves the contrast value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved contrast value should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current contrast value applied in PQ module.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the contrast to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveContrast(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,int value);

/**
 * @brief Sets the sharpness value to driver register(s)
 *
 * This function updates the new sharpness value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved sharpness value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] sharpness                - Sharpness value to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                - Success
 * @retval tvERROR_INVALID_PARAM       - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE       - Interface is not initialized
 * @retval tvERROR_GENERAL             - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetSharpness()
 */
tvError_t SetSharpness(int sharpness);

/**
 * @brief Gets the current sharpness value
 *
 * This function gets the current sharpness value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] sharpness              - Current sharpness value. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE               - Success 
 * @retval tvERROR_INVALID_PARAM      - Parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * @retval tvERROR_GENERAL            - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetSharpness()
 */
tvError_t GetSharpness(int *sharpness);

/**
 * @brief Saves the sharpness value
 *
 * This function saves the sharpness value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved sharpness value should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current sharpness value applied in PQ module.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the sharpness to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t SaveSharpness(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,int value);

/**
 * @brief Sets the saturation value to driver register(s)
 *
 * This function updates the new saturation value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved saturation value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] saturation              - Saturation value to be set. Valid range is (0 - 100)
 *                       
 * @return tvError_t    
 *  
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_INVALID_PARAM      - Parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * @retval tvERROR_GENERAL            - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetSaturation()
 */
tvError_t SetSaturation(int saturation);

/**
 * @brief Gets the current saturation value
 *
 * This function gets the current saturation value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] saturation              - Current saturation value. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                - Success
 * @retval tvERROR_INVALID_PARAM       - Parameter is invalid
 * @retval tvERROR_INVALID_STATE       - Interface is not initialized
 * @retval tvERROR_GENERAL             - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetSaturation()
 */
tvError_t GetSaturation(int *saturation);

/**
 * @brief Saves the saturation value
 *
 * This function saves the sharpness value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved saturation value should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current saturation value applied in PQ module.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the saturation to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveSaturation(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,int value);

/**
 * @brief Sets the hue value to driver register(s)
 *
 * This function updates the new hue value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved hue value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] hue                     - Hue value to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_INVALID_PARAM      - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * @retval tvERROR_GENERAL            - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetHue()
 */
tvError_t SetHue(int hue);

/**
 * @brief Gets the current hue value
 *
 * This function gets the current hue value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] hue                    - Current hue value. Valid range (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_INVALID_PARAM      - Parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * @retval tvERROR_GENERAL            - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetHue()
 */
tvError_t GetHue(int *hue);

/**
 * @brief Saves the hue value
 *
 * This function saves the hue  value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved hue value should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current hue value applied in PQ module.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the hue to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveHue(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,int value);

/**
 * @brief Sets the color temperature to driver register(s)
 *
 * This function updates the new color temperature value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved color temperature value should be applied automatically whenever the  current picture mode, current primary video format
 * Loads the corresponding gamma and white balance values assoicated to the colour temperature from the picure quality database.
 *
 * @param[in] colorTemp              - Color temperature value to be set. Valid value will be a member of ::tvColorTemp_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetColorTemperature()
 */
tvError_t SetColorTemperature(tvColorTemp_t colorTemp);

/**
 * @brief Gets the current color temperature
 *
 * This function gets the current colour temperature value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] colorTemp             - Current color temperature. Valid value will be a member of ::tvColorTemp_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - Parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetColorTemperature()
 */
tvError_t GetColorTemperature(tvColorTemp_t *colorTemp);

/**
 * @brief Saves the color temperature value
 *
 * This function saves the color temperature value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved color temperature value should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current color temperature value applied in PQ module.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the color temperature to be set. Valid value will be member of ::tvColorTemp_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveColorTemperature(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,tvColorTemp_t value);

/**
 * @brief Sets the aspect ratio
 *
 * This function updates the new aspect ratio value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved aspect ratio value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] dispMode                - Aspect ratio value to be set. Valid value will be a member of ::tvDisplayMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetAspectRatio()
 */
tvError_t SetAspectRatio(tvDisplayMode_t dispMode);

/**
 * @brief Gets the current aspect ratio
 *
 * This function gets the current aspect ratio for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] dispMode             -  Aspect ratio value. Valid value will be a member of ::tvDisplayMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetAspectRatio()
 */
tvError_t GetAspectRatio(tvDisplayMode_t *dispMode);

/**
 * @brief Saves the aspect ratio value
 *
 * This function saves the aspect ratio value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved aspect ratio value should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current aspect ratio value applied in PQ module.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the aspect ratio to be set. Valid value will be a member of ::tvDisplayMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveAspectRatio(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,tvDisplayMode_t value);

/**
 * @brief Sets the low latency state to driver register(s)
 *
 * This function updates the new low latency state value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved low latency state value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] lowLatencyIndex       - Value of the low latency index to be set. Valid values are ( 0 for disable, 1 for enable)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetLowLatencyState( int lowLatencyIndex );

/**
 * @brief Gets the current low latency state
 *
 * This function gets the current low latency value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] lowlatencystate       - Current low latency index value. Valid values are ( 0, 1 )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetLowLatencyState(int *lowlatencystate);

/**
 * @brief Saves the low latency index
 *
 * This function saves the low latency index in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved low latency index should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in low latency index value applied in PQ module.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the low latency index to be set. Valid values are ( 0, 1 )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t SaveLowLatencyState( tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,int value );

/**
 * @brief Sets the dynamic contrast
 *
 * This function updates the dynamic contrast state to PQ module. The change takes effect for current
 * primary video source selected, video format played and picture mode selected, but not saved in picture profile database. 
 * The value is discarded and default value from picture profile database is used when primary video format 
 * or primary video source or picture mode changes.
 *
 * @param[in] dynamicContrastEnable  - Dynamic contrast enable flag value (valid values are "enabled" for enable and "disabled" for disable)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetDynamicContrast()
 */
tvError_t SetDynamicContrast(const char *dynamicContrastEnable);

/**
 * @brief Gets the current Dynamic contrast mode
 *
 * This function gets the current dynamic contrast value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] isDynamicContrastEnabled        - Current dynamic contrast mode flag value. (valid values are "enabled" for enable and "disabled" for disable)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetDynamicContrast()
 */
tvError_t GetDynamicContrast(char *isDynamicContrastEnabled);

/**
 * @brief Sets and saves the dynamic gamma
 *
 * This function sets the global dynamic gamma value. Currently loaded 2.2 gamma is shifted as per the 
 * new dynamic gamma value passed. The dynamic gamma value is saved for future use. Any reload of new gamma curve (as a result of
 * colour temperature change) should be followed by shifting of the new gamma curve based on the dynamic gamma value.
 *
 * @param[in] tvGammaValue  - The dynamic Gamma value to be applied. Valid values range from 1.80 till 2.60
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetDynamicGamma()
 */
tvError_t SetDynamicGamma(double tvGammaValue);

 /**
 * @brief Gets the current dynamic gamma
 *
 * This function gets the current global dynamic gamma value. 
 *
 * @param[in] tvGammaValue  - The current dynamic Gamma value to be returned. Valid values are 1.80 till 2.60
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetDynamicGamma()
 */tvError_t GetDynamicGamma(double *tvGammaValue);

/**
 * @brief Gets the supported DV modes and their count
 *
 * This function returns the supported Dolby Vision modes and their count
 *
 * @param[out] dvModes[]            - List of available DV modes. Refer ::tvDolbyMode_t @n
 *                                    Valid values are member of ::tvDolbyMode_t
 * @param[out] count                - Count of supported DV modes. Max is tvMode_Max and min is 0
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetTVSupportedDolbyVisionModes(tvDolbyMode_t *dvModes[],unsigned short *count);

/**
 * @brief Sets dolby vision mode
 *
 * This function updates the new dolby vision mode value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved dolby vision mode value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] dolbyMode              - Dolby vision mode to be set.  Valid values are member of ::tvDolbyMode_t
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
 * @pre TvInit() should be called before calling this API
 *
 * @see GetTVDolbyVisionMode()
 */
tvError_t SetTVDolbyVisionMode(tvDolbyMode_t dolbyMode);

/**
 * @brief Gets the current current dolby vision mode
 *
 * This function gets the current Dolby vision mode value for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[out] dolbyMode              - Current Dolby vision mode.  Valid values are member of ::tvDolbyMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetTVDolbyVisionMode()
 */
tvError_t GetTVDolbyVisionMode(tvDolbyMode_t *dolbyMode);


/**
 * @brief Saves the dolby mode value
 *
 * This function saves the dolby mode value in picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved dolby mode value should be applied automatically by whenever the 
 * specified picture mode is selected, specified primary video format(if handled via Dolby core) is played 
 * and specified primary video source is selected. There will be no change in current dolby mode value in Dolby Vision core.
 *
 * @param[in] videoSrcType           - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the dolby mode to be set. Valid value will be a member of ::tvDolbyMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveTVDolbyVisionMode(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,tvDolbyMode_t value);

/**
 * @brief Gets the supported picture modes and their count
 *
 * This function get the array of picture modes supported and their count
 *
 * @param[out] pictureModes              - List of available picture modes. Valid values are as per values returned by pic_modes_t.name and pic_modes_t.values parameter(refer tvPQModeIndex_t).
 * @param[out] count                     - Count of supported picture modes. Maximum possile value is PIC_MODES_SUPPORTED_MAX. Min is 1.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                   - Success
 * @retval tvERROR_INVALID_PARAM          - Parameter is invalid
 * @retval tvERROR_INVALID_STATE          - Interface is not initialized
 * @retval tvERROR_GENERAL                - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetTVSupportedPictureModes(pic_modes_t *pictureModes[],unsigned short *count);

/**
 * @brief Gets the current selected picture Mode
 *
 * This function will get the current selected picture mode for current pirmary video source and primary video format.
 *
 * @param[out] pictureMode         - Current picture mode. Valid values are as per values
 *                                   returned by ::pic_modes_t.name  parmaeter from GetTVSupportedPictureModes API. 
 *                                   The size of string will be PIC_MODE_NAME_MAX.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - Parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * @retval tvERROR_GENERAL         - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetTVPictureMode()
 */
tvError_t GetTVPictureMode(char *pictureMode);

/**
 * @brief Sets the Picture Mode
 *
 * This function updates the picture mode and reloads all the associated picture properties for the picture mode. This applies
 * to current selected primary video source and primary video format, if successful the association of picture mode to the
 * current video source and current primary video format is saved in override picture profile database. The associated
 * picture mode and all the associated picture properties will be reloaded again when the current video source and current
 * primary video format are selected in future.
 *
 * @param[in] pictureMode           - Picture mode to be set.Valid values are as per values
 *                                    returned by ::pic_modes_t.name  parmaeter from GetTVSupportedPictureModes API. 
 *                                    The size of string will be PIC_MODE_NAME_MAX.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see GetTVPictureMode()
 */
tvError_t SetTVPictureMode(const char * pictureMode);


/**
 * @brief Saves picture mode.
 *
 * This function saves the picturemode in picture profile database for the specific primary video format type 
 * and primary video source. The saved picture mode should be applied automatically whenever the 
 * specified specified primary video format is played and specified primary video source is selected.
 *
 * @param[in] videoSrcType          - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pictureMode          - Picture mode value to be saved. Valid values are as per values returned by 
 *                                    ::pic_modes_t.value  parmaeter from GetTVSupportedPictureModes API.
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveSourcePictureMode(tvVideoSrcType_t videoSrcType, tvVideoFormatType_t videoFormatType, int pictureMode);

/**
 * @brief Sets or saves the rgain value
 *
 * This function sets or saves the rgain value for a specfic color temperature and video source. If it is set operation (saveOnly=0) @n
 * the rgb gain and offset for the specified colour temperature will be loaded in white balance module and @n
 * the new red gain value from this API will be updated, but not saved in picture profile database. 
 * The value is discarded and default value from picture profile database is used when primary video format 
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the rgain will be saved for the specific video source and colour temperature. The saved 
 * rgain value will be automatically applied in white balance module when the colour temperaure choice is made as result of 
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] rgain                - Rgain Value to be set. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set=0 ( @a 0 for rgain value will be applied to PQ HW. i.e changes can be visible immediately on screen
 *                                                    @a 1 for rgain value will be saved and applied later i.e changes not visible immediately for current video)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int rgain,tvColorTempSourceOffset_t sourceId, int saveOnly);

/**
 * @brief Gets the current rgain value.
 *
 * This function gets the current rgain value for a specific color temperature and source offset.
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] rgain               - Rgain Value. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int* rgain,tvColorTempSourceOffset_t sourceId);

/**
 * @brief Sets or saves the ggain value
 *
 * This function sets or saves the ggain value for a specfic color temperature and video source. If it is set operation (saveOnly=0) @n
 * the rgb gain and offset for the specified colour temperature will be loaded in white balance module and @n
 * the new green gain value from this API will be updated, but not saved in picture profile database. 
 * The value is discarded and default value from picture profile database is used when primary video format 
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the ggain will be saved for the specific video source and colour temperature. The saved 
 * ggain value should be automatically applied in white balance module when the colour temperaure choice is made as result of 
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] ggain                - Ggain Value to be set. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set=0 ( @a 0 for ggain value will be applied to PQ HW. i.e changes can be visible immediately on screen
 *                                                    @a 1 for ggain value will be saved and applied later i.e changes not visible immediately for current video)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int ggain,tvColorTempSourceOffset_t sourceId, int saveOnly);

/**
 * @brief Gets the current ggain value for a specfic color temperature and source
 *
 * This function gets the ggain value for a specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] ggain               - Ggain Value. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int* ggain,tvColorTempSourceOffset_t sourceId);

/**
 * @brief Sets or saves the bgain value
 *
 * This function sets or saves the bgain value for a specfic color temperature and video source. If it is set operation (saveOnly=0) @n
 * the rgb gain and offset for the specified colour temperature will be loaded in white balance module and @n
 * the new bgain gain value from this API will be updated, but not saved in picture profile database. 
 * The value is discarded and default value from picture profile database is used when primary video format 
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the bgain will be saved for the specific video source and colour temperature. The saved 
 * bgain value will be automatically applied in white balance module when the colour temperaure choice is made as result of 
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] bgain                - Bgain Value to be set. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set=0 ( @a 0 for bgain value will be applied to PQ HW. i.e changes can be visible immediately on screen
 *                                                    @a 1 for bgain value will be saved and applied later i.e changes not visible immediately for current video)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int bgain,tvColorTempSourceOffset_t sourceId, int saveOnly);

/**
 * @brief Gets the current bgain value for a specfic color temperature and source
 *
 * This function gets the bgain value for a specfic color temperature and source
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] bgain               - Bgain Value. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int* bgain,tvColorTempSourceOffset_t sourceId);

/**
 * @brief Sets or saves the rpostoffset value
 *
 * This function sets or saves the rpostoffset value for a specfic color temperature and video source. If it is set operation (saveOnly=0) @n
 * the rgb gain and offset for the specified colour temperature will be loaded in white balance module and @n
 * the new rpostoffset gain value from this API will be updated, but not saved in picture profile database. 
 * The value is discarded and default value from picture profile database is used when primary video format 
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the rpostoffset will be saved for the specific video source and colour temperature. The saved 
 * rpostoffset value should be automatically applied in white balance module when the colour temperaure choice is made as result of 
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] rpostoffset          - Rpostoffset Value to be set. Valid range is  (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set=0 ( @a 0 for rpostoffset value will be applied to PQ HW. i.e changes can be visible immediately on screen
 *                                                    @a 1 for rpostoffset value will be saved and applied later i.e changes not visible immediately for current video)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int rpostoffset,tvColorTempSourceOffset_t sourceId, int saveOnly);

/**
 * @brief Gets the current rpostoffset value
 *
 * This function gets the current rpostoffset value for a specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] rpostoffset         - Rpostoffset Value. Valid range is (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int* rpostoffset,tvColorTempSourceOffset_t sourceId);

/**
 * @brief Sets or saves the gpostoffset value
 *
 * This function sets or saves the gpostoffset value for a specfic color temperature and video source. If it is set operation (saveOnly=0) @n
 * the rgb gain and offset for the specified colour temperature will be loaded in white balance module and @n
 * the new gpostoffset gain value from this API will be updated, but not saved in picture profile database. 
 * The value is discarded and default value from picture profile database is used when primary video format 
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the gpostoffset will be saved for the specific video source and colour temperature. The saved 
 * gpostoffset value should be automatically applied in white balance module when the colour temperaure choice is made as result of 
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] gpostoffset          - Gpostoffset Value to be set. Valid range is  (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set=0 ( @a 0 for gpostoffset value will be applied to PQ HW. i.e changes can be visible immediately on screen
 *                                                    @a 1 for gpostoffset value will be saved and applied later i.e changes not visible immediately for current video)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int gpostoffset,tvColorTempSourceOffset_t sourceId, int saveOnly);

/**
 * @brief Gets the current gpostoffset value for a specfic color temperature and source
 *
 * This function gets the gpostoffset value for a specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] gpostoffset         - Gpostoffset Value. Valid range is (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int* gpostoffset,tvColorTempSourceOffset_t sourceId);

/**
 * @brief Sets or saves the bpostoffset value
 *
 * This function sets or saves the bpostoffset value for a specfic color temperature and video source. If it is set operation (saveOnly=0) @n
 * the rgb gain and offset for the specified colour temperature will be loaded in white balance module and @n
 * the new bpostoffset gain value from this API will be updated, but not saved in picture profile database. 
 * The value is discarded and default value from picture profile database is used when primary video format 
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the bpostoffset will be saved for the specific video source and colour temperature. The saved 
 * bpostoffset value should be automatically applied in white balance module when the colour temperaure choice is made as result of 
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] bpostoffset          - Bpostoffset Value to be set. Valid range is  (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set=0 ( @a 0 for bpostoffset value will be applied to PQ HW. i.e changes can be visible immediately on screen
 *                                                    @a 1 for bpostoffset value will be saved and applied later i.e changes not visible immediately for current video)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int bpostoffset,tvColorTempSourceOffset_t sourceId, int saveOnly);

/**
 * @brief Gets the current bpostoffset value for a specfic color temperature and source
 *
 * This function gets the bpostoffset value for a specfic color temperature and source
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] bpostoffset         - Bpostoffset Value. Valid range is (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int* bpostoffset,tvColorTempSourceOffset_t sourceId);

/**
 * @brief Enables / disables the WB mode
 *
 * This function enables or disables white balance calibration mode. When enabled configures backlight in fixed dimming mode 
 * and sets all PQ elements except for gamma/white balance elements in bypass mode/disabled mode. On disable restores the 
 * dimming mode and all PQ elements in the last known state before the WB calibration mode was enabled.
 *
 * @param[in] value                        - Enable / disable WB mode ( @a true for enable , @a false for disable )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                   - Success
 * @retval tvERROR_INVALID_STATE          - Interface is not initialized
 * @retval tvERROR_GENERAL                - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t EnableWBCalibrationMode(bool value);

/**
 * @brief Gets the current WB mode
 *
 * This function returns the current status of white balance calibration mode.
 *
 * @param[out] value                        - Current WB mode ( @a true for enable , @a false for disable )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                   - Success
 * @retval tvERROR_INVALID_PARAM          - Parameter is invalid
 * @retval tvERROR_INVALID_STATE          - Interface is not initialized
 * @retval tvERROR_GENERAL                - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentWBCalibrationMode(bool *value);

/**
 * @brief Sets the gamma calibrated values to gamma HW for current selected colour temperature.
 *
 * This function sets the gamma calibrated values(0 - 1023) for the primary colors to gamma Hardware
 * for the current selected colour temperature, but they are not saved in picture profile database. The gamma values
 * will be discarded and default value from picture profile database is used on colour temperature value change as a result of picture mode change or primary video source
 * change or primary vidoe format change.
 *
 * @param[in] pData_R       - Array of gamma red values. Valid range is (0 - 1023)
 * @param[in] pData_G       - Array of gamma green values. Valid range is (0 - 1023)
 * @param[in] pData_B       - Array of gamma blue values. Valid range is (0 - 1023)
 * @param[in] size          - Common size of each array. Valid range is (0 - 256)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetGammaTable(unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);

/**
 * @brief Gets the default gamma values from picture profile database.
 *
 * This function gets the default gamma calibrated values(0 - 65535) for the primary colors for a specific color temperature.
 *
 * @param[in] colortemp       - Color temperature. Valid value will be member of ::tvColorTemp_t
 * @param[out] pData_R        - Array of gamma red values. Valid range is (0 - 1023)
 * @param[out] pData_G        - Array of gamma green values. Valid range is (0 - 1023)
 * @param[out] pData_B        - Array of gamma blue values. Valid range is (0 - 1023)
 * @param[in] size           - Common size of each array. Valid range is (0 - 256)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetDefaultGammaTable(tvColorTemp_t colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);

/**
 * @brief Gets the current gamma calibrated values from gamma HW for current selected colour temperature.
 *
 * This function gets the current gamma calibrated values(0 - 65535) for the primary colors for a current color temperature.
 *
 * @param[out] pData_R        - Array of gamma red values. Valid range is (0 - 1023)
 * @param[out] pData_G        - Array of gamma green values. Valid range is (0 - 1023)
 * @param[out] pData_B        - Array of gamma blue values. Valid range is (0 - 1023)
 * @param[in] size           - Common size of each array. Valid range is (0 - 256)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetGammaTable(unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);

/**
 * @brief Saves the gamma calibrated values.s
 *
 * This function saves the gamma calibrated values in picture profile database for the primary colors for a specific color temperature.
 * The saved gamma calibrated values will be automatically applied when the specified colour temperature choice is made
 * as a result of picture mode change or primary video source change or primary vidoe format change.
 *
 * @param[in] colortemp       - Color temperature. Valid value will be member of ::tvColorTemp_t
 * @param[out] pData_R        - Array of gamma red values. Valid range is (0 - 1023)
 * @param[out] pData_G        - Array of gamma green values. Valid range is (0 - 1023)
 * @param[out] pData_B        - Array of gamma blue values. Valid range is (0 - 1023)
 * @param[out] size           - Common size of each array. Valid range is (0 - 256)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveGammaTable(tvColorTemp_t colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);

/**
 * @brief Sets the calibrated Dolby vision TMAX paramaeter in the Dolby vision core.
 *
 * This function sets the Dolby vision TMAX paramaeter in the Dolby vision core, but will not be saved in picture profile database. 
 * The value is discarded and default value from picture profile database is used when primary video format 
 * or primary video source or picture mode changes.
 *
 * @param[in] value       - Value of the TMAX to be set. Valid range is (0 to 10000)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetDvTmaxValue(int value);    

/**
 * @brief Gets the current Dolby vision TMAX paramaeter from the Dolby vision core.
 *
 * This function gets the current Dolby vision TMAX paramaeter from the Dolby vision core.
 *
 * @param[out] value       - Value of the TMAX to be set. Valid range is (0 to 10000)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t GetDvTmaxValue(int *value);


/**
 * @brief Saves the Dolby vision TMAX paramaeter
 *
 * This function saves the Dolby vision TMAX paramaeter in picture profile database for the specified LDIM state level.
 * The saved TMAX value will be applied in Dolby Vision core whenever the specified ldim state level is selected 
 * as a result of picture mode change or primary video source change or primary vidoe format change.
 *
 * @param[in] state       - LDIM state level. Refer ::ldimStateLevel_t
 * @param[in] value       - Value of the TMAX to be saved. Valid range is (0 to 10000)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t SaveDvTmaxValue(ldimStateLevel_t state, int value);

/**
 * @brief Gets the supported Component colors
 *
 * This function gets the supported component colors. @n
 * The output has the bitwise OR-ed value of all the supported colors (tvDataComponentColor_t).
 *
 * @param[out] blComponentColor           - Bit wise OR-ed value for supported component colors. Please refer ::tvDataComponentColor_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetSupportedComponentColor(int *blComponentColor);

/**
 * @brief Sets the current component saturation value
 *
 * This function uses specified saturation property for the specified colour and adjust the default colour properties
 * of the colour management system. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successfull will be saved in override picture profile database.
 * The saved component saturation value for the specified colour will take effect automatically whenever the 
 * current picture mode, current primary video format and current video source are again selected in future.
 *
 * @param[in] blSaturationColor          - Component color. Valid value will be one of the member of ::tvDataComponentColor_t.
 *                                         If more than one value is bitwise OR-ed and passed then the function should return invalid param.
 * @param[in] saturation                 - Saturation value to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success  
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() and SetCMSState(true) should be called before calling this API
 *
 * @see SetCMSState()
 */
tvError_t SetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int saturation);

/**
 * @brief Gets current component saturation
 *
 * This function returns the current component saturation for the specified color, for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[in] blSaturationColor         - Component color. Valid value will be a member of ::tvDataComponentColor_t
 * @param[out] saturation               - Saturation value of the color. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @see SetCurrentComponentSaturation()
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int *saturation);

/**
 * @brief Sets the current component hue value
 *
 * This function uses specified hue property for the specified colour and adjust the default colour properties
 * of the colour management system. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successfull will be saved in override picture profile database.
 * The saved component hue value for the specified colour will take effect automatically whenever the 
 * current picture mode, current primary video format and current video source are again selected in future.
 *
 * @param[in] blHueColor               - Component color. Valid value will be a member of ::tvDataComponentColor_t
 * @param[in] hue                      - Hue value to be set. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() and SetCMSState(true) should be called before calling this API
 *
 * @see SetCMSState()
 */
tvError_t SetCurrentComponentHue(tvDataComponentColor_t blHueColor, int hue);

/**
 * @brief Gets current component hue
 *
 * This function returns the current component hue for the specified color, for the primary video source selected, 
 * primary video format played and picture mode selected.                          
 *
 * @param[in] blHueColor              - Component color. Valid value will be a member of ::tvDataComponentColor_t
 * @param[out] hue                     - Hue value of the color. Valid range is (0 - 100)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @see SetCurrentComponentHue()
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentComponentHue(tvDataComponentColor_t blHueColor, int *hue);

/**
 * @brief Sets the current component luma value
 *
 * This function uses specified luma property for the specified colour and adjust the default colour properties
 * of the colour management system. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successfull will be saved in override picture profile database.
 * The saved component luma value for the specified colour will take effect automatically whenever the 
 * current picture mode, current primary video format and current video source are again selected in future.
 *
 * @param[in] blLumaColor            - Component color. Valid value will be a member of ::tvDataComponentColor_t
 * @param[in] Luma                    - Luma value to be set. Valid range is (0 - 30)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() and SetCMSState(true) should be called before calling this API
 *
 * @see SetCMSState()
 */
tvError_t SetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int Luma);

/**
 * @brief Gets the current component luma
 *
 * This function returns the current component luma for the specified color, for the primary video source selected, 
 * primary video format played and picture mode selected.
 *
 * @param[in] blLumaColor          - Component color. Valid value will be a member of ::tvDataComponentColor_t
 * @param[out] Luma                 - Luma value of the color. Valid range is (0 - 30)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @see SetCurrentComponentLuma()
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int *Luma);

/**
 * @brief Save the CMS value
 *
 * This function saves the CMS value in override picture profile database for the specific picture mode, primary video format type 
 * and primary video source. The saved CMS value should automatically take effect whenever the 
 * specified picture mode is selected, specified primary video format is played, specified primary video source is selected
 * and the CMS state is enabled for that combination. There will be no change in current CMS value applied in colour management system.
 * When the component_type is passed as COMP_NONE and color_type is passed as tvDataColor_NONE, the cms_value
 * refers to CMS state.
 *
 * @param[in] videoSrcType            - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode                - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType        - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] component_type        - Component type value. Valid value will be a member of ::tvComponentType_t
 * @param[in] color_type            - Color type value. Valid value will be a member of ::tvDataComponentColor_t
 * @param[in] cms_value              - Value of the CMS to be set. 
 *                                    If the value of component_type is COMP_NONE and color_type is tvDataColor_NONE then the cms_value represents the CMS state. 
 *                                    Valid values are true(1) or false(0).
 *                                    If the value of component_type is not COMP_NONE and color_type is not tvDataColor_NONE then the cms_value represents the value for the
 *                                    corresponding colour type (::tvComponentType_t) and component type (::tvDataComponentColor_t) specified.
 *                                    Values range : for Hue and saturation (0 - 100), for Luma (0 - 30)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized 
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @see SetCMSState(), SetCurrentComponentHue(), GetCurrentComponentLuma() and SetCurrentComponentSaturation()
 * @pre TvInit() should be called before calling this API
 */
 tvError_t SaveCMS(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,tvComponentType_t component_type,tvDataComponentColor_t color_type,int cms_value);

/**
 * @brief Sets and save's the CMS state
 *
 * This function enable or disable the CMS state. When enabled the hue/saturation/luma properties for
 * RGBCMY colours stored in override picture profile database for the current picture mode, video source and video format 
 * will used to adjust the default properties of the colour management system. 
 * When disabled the colour management system is restored with default properties and hue/saturation/luma properties 
 * for RGBCMY colours will not be used to adjust default properties.
 * The change is applied for current primary video source selected, video format played and picture mode selected 
 * and if successfull will be saved in override picture profile database. The saved CMS state value should be 
 * take effect automatically whenever the  current picture mode, current primary video format
 * and current primary video source are again selected in future.
 *
 * @param[in] enableCMSState        - CMS state to be set. @n
 *                                    Valid values are true if need to be enabled and false if need to be disabled.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetCMSState(bool enableCMSState);

/**
 * @brief Gets the CMS state
 *
 * This function gets the current CMSState for the current picture mode selected,
 * current primary video format played and current primary video source selected. 
 * The default value is determined during PQ calibration before pre production stage.
 *
 * @param[out] enableCMSState        - Current CMS state set. @n
 *                                    Valid values are true if it is enabled and false if it is disabled.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @see SetCMSState()
 * 
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCMSState(bool *enableCMSState);

/**
 * @brief Gets the default PQ Setting parameters
 *
 * This function returns default values for various PQ Setting parameters for a given picture mode index, primary video source @n
 * and primary video format.
 * GetCMSState will return value of CMS state set by SetCMSState for respective source, format and picture mode.
 *
 * @param[in] videoSrcType          - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pqIndex               - Picture mode index value. Valid values are as per values will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] pqParamIndex          - The PQ parmaeter enum for which the default value is expected. Valid value will be a member of  ::tvPQParameterIndex_t
 * @param[out] value                - The default value returned for the requested PQ setting parameter in pqParamIndex.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t GetDefaultPQParams(int pqIndex,tvVideoSrcType_t videoSrcType,tvVideoFormatType_t videoFormatType, tvPQParameterIndex_t pqParamIndex, int *value);


/**
 * @brief Gets the PQ Setting parameters
 *
 * This function returns the override values for various PQ Setting parameters for a given picture mode index, primary video source @n
 * and primary video format.
 *
 * @param[in] pqIndex               - Picture mode index value. Valid values will be a member of ::tvPQModeIndex_t
 * @param[in] videoSrcType          - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] pqParamIndex          - The PQ parmaeter enum for which the default value is expected. Valid value will be a member of  ::tvPQParameterIndex_t
 * @param[out] value                - The override value returned for the requested PQ setting parameter in pqParamIndex.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetPQParams(int pqIndex,tvVideoSrcType_t videoSrcType,tvVideoFormatType_t videoFormatType, tvPQParameterIndex_t pqParamIndex, int *value);

/**
 * @brief Gets the max gamma/whitebalance gain value capable for the platform.
 *
 * This function returns the max gamma gain value capable for the platform. The valid range can be in powers of 2 @n
 * from 2^10 till (2^31)-1.
 *
 * @return int
 *
 *
 * @pre TvInit() should be called before calling this API
 */
int GetMaxGainValue();

/**
 * @brief Enables or disables gamma module
 *
 * This function enables or disables the gamma module
 *
 * @param[in] mode                - Gamma mode( @a 0 for disable gamma module or @a 1 for enable gamma module)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t EnableGammaMode(int mode);

/**
 * @brief Sets the gamma pattern
 *
 * This function sets the primary color level at 10bit resolution( 0 - 1023 ). Should bypass all PQ elements @n
 * and display the full screen pattern of the primary colour passed. This function will only set and does'nt save the value.
 *
 * @param[in] is_10_bit         - Value to check if red/green/blue paramter is 10 bit resolution or 8 bit resolution. @n
 *                                  Valid values are  ( @a 0 for is 10 bit,  @a 1 for 8 bit). If 8 bit resolution is passed @n
 *                                  values should be converted to 10 bit by 2 bit left shift and then used.
 * @param[in] R_Value           - Red level of input pattern. Valid range is ( 0 - 1023 for 10 bit and 0 to 255 for 8 bit )
 * @param[in] G_Value           - Green level of input pattern. Valid range is ( 0 - 1023 for 10 bit and 0 to 255 for 8 bit )
 * @param[in] B_Value           - Blue level of input pattern. Valid range is ( 0 - 1023 for 10 bit and 0 to 255 for 8 bit )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() and SetGammaPatternMode(true) should be called before calling this API
 *
 * @see SetGammaPatternMode()
 */
tvError_t SetGammaPattern(int is_10_bit, int R_Value, int G_Value, int B_Value);

/**
 * @brief Gets the target x and y coordinates for the panel gamma
 *
 * This function returns the target x and y coordinates for a given color temperature and as defined by CIE 1931 color space chromaticity coordinates for the panel gamma
 *
 * @param[in] colorTemp            - Colour temperature value. The valid value will be a member of::tvColorTemp_t
 * @param[out] x                   - X coordinate value is as defined by CIE 1931 color space chromaticity coordinates. The range is 0 to 1.0.
 * @param[out] y                   - Y coordinate value is as defined by CIE 1931 color space chromaticity coordinates. The range is 0 to 1.0.
 *
* @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 * @pre TvInit() should be called before calling this API
 */

tvError_t GetTVGammaTarget(tvColorTemp_t colorTemp,double *x, double *y);

/**
 * @brief Sets the gamma pattern mode
 *
 * This function allows gamma pattern mode to be enabled or disabled. Only if it is enabled the API's SetGammaPattern and SetGrayPattern will take effect. @n
 * When enabled the gamma module will be disabled and system ready to accept the new pattern values from SetGammaPattern and SetGrayPattern APIs. @n
 * When disabled the last set gamma values before the SetGammaPatternMode(true) API call will be restored.
 * This function will only set and does'nt save the value.
 *
 * @param[in] mode         - Valid values are true and false. true when gamma pattern mode needs to be enabled @n
 *                             false when gamma pattern mode needs to be enabled.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetGammaPattern()
 */
tvError_t SetGammaPatternMode(bool mode);

/**
 * @brief Sets the RGB values of RGB pattern
 *
 * This function sets the primary color level at 8bit resolution(0 - 255). This pattern is processed via PQ pipeline @
 * elemennts before it reaches the panel.
 *
 * @param[in] r                    - Red level of input pattern to be set. Valid range is (0 - 255)
 * @param[in] g                    - Green level of input pattern to be set. Valid range is (0 - 255)
 * @param[in] b                    - Blue level of input pattern to be set. Valid range is (0 - 255)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetRGBPattern(int r,int g, int b) ;

/**
 * @brief Gets the current RGB values of the RGB pattern.
 *
 * This function gets the current primary color level(0 - 255) of the RGB pattern.
 *
 * @param[out] r                    - Red level of input pattern. Valid range is (0 - 255)
 * @param[out] g                    - Green level of input pattern. Valid range is (0 - 255)
 * @param[out] b                    - Blue level of input pattern. Valid range is (0 - 255)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetRGBPattern(int *r,int *g,int *b);

/**
 * @brief Sets the gray pattern value
 *
 * This function sets the various gray pattern levels. Should bypass all PQ elements @n
 * and display the full screen grey pattern.
 *
 * @param[in] YUVValue              - Gray level of input pattern to be set. Valid range is (0 - 255)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() and SetGammaPatternMode(true) should be called before calling this API
 *
 * @see SetGammaPatternMode()
 */
tvError_t SetGrayPattern(int YUVValue);

/**
 * @brief Gets the current gray pattern value 
 *
 * This function gets the current gray pattern level
 *
 * @param[out] YUVValue              - Gray level of input pattern. Valid range is (0 - 255)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t GetGrayPattern(int* YUVValue);

/**
 * @brief Gets the current open circuit status of the backlight hardware
 *
 * Gets the current open circuit status of the backlight hardware
 *
 * @param[out] status              - Open circuit status. Valid values are >=1 due to led fault @n
 *                                     and 0 when no led fault is detected.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetOpenCircuitStatus(int *status);

/**
 * @brief Enables or disabless the pixel compensation block.
 *
 * This function enables or disabled the pixel compensation block to offset pixel intentisity changes
 * due to overall backlight changes in local dimming zones.
 *
 * @param[in] mode                 - Valid values are true and false. @n
 *                                     true when pixel compensation block needs to be enabled @n
 *                                      false when pixel compensation block needs to be disabled.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t EnableLDIMPixelCompensation(bool mode);

/**
 * @brief Enables or disables the local dimming module
 *
 * This function enables or disabless the local dimming modulek. When disabled the backlight @
 * for all zones will have fixed backlight level.
 *
 * @param[in] mode                 - Valid values are true and false. @n
 *                                     true when local dimming module needs to be enabled @n
 *                                      false when local dimming module needs to be disabled.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t EnableLDIM(bool mode);

/**
 * @brief Starts the local dimming sequence test.
 *
 * This function starts the local dimming sequence test. When API is called, all LDIM zones are first @
 * turned off and then each LDIM zone is turned on for a certain duration (specified by delay parameter) @n
 * and repeated for all LDIM zones sequentially. At the end of the test the orginal state of all LDIM zone is restored.
 *
 * @param[in] mode                 - The ldim sequence test mode. Valid value is 2.
 * @param[in] delay                - Number of miiliseconds a given ldim zone need to be turned on. Valid value is 1-1000ms.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t StartLDIMSequenceTest(int mode, int delay);

/**
 * @brief Enables or disables the backlight test mode
 *
 * This function setup the backlight hardware to for calibration purposes. The number of dimming zones @n
 * the backlight intensity and the specific dimming zones to be turned on are decided based on the test mode
 * as defined for the respective platforms.
 *
 * @param[in] mode                 - The backlight test mode. Valid values can be members of ::tvBacklightTestMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t SetBacklightTestMode(tvBacklightTestMode_t mode);

/**
 * @brief Enables or disables the white balance module
 *
 * This function enables or disabless the  white balance. 
 *
 * @param[in] mode                 - Valid values are true and false. @n
 *                                     true when  white balance module needs to be enabled @n
 *                                      false when  white balance module needs to be disabled.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t EnableWhiteBalance(bool mode);

/**
 * @brief Enables or disables the dynamic contrast module
 *
 * This function enables or disabless the dynamic contrast module.
 *
 * @param[in] mode                 - Valid values are true and false. @n
 *                                     true when dynamic contrast module needs to be enabled @n
 *                                      false when dynamic contrast needs to be disabled.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t EnableDynamicContrast(bool mode);

/**
 * @brief Enables or disables the local contrast module
 *
 * This function enables or disabless the local contrast module.
 *
 * @param[in] mode                 - Valid values are true and false. @n
 *                                     true when local contrast module needs to be enabled @n
 *                                      false when local contrast needs to be disabled.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t EnableLocalContrast(bool mode);

/**
 * @brief Triggers short circuit detection and returns the status.
 *
 * On calling GetLdimZoneShortCircuitStatus, the short circuit detection logic
 * is triggered. It detects short circuits between zones. On completion, it
 * returns a list of zones where a short circuit was detected.
 *
 * @param[out] shortcircuit_zone_list  Pre-allocated array indicating short circuit status for each zone.
 *                                        0 - No short circuit detected.
 *                                        1 - Short circuit detected.
 * @param[in]  size                    Size of the shortcircuit_zone_list array.
 *                                        The size is platform/hardware specific.
 * @param[out] status                  Short circuit detection status.
 *                                        0 - Success, no short circuit detected.
 *                                        1 - Failure, at least one short circuit detected.
 *
 * @return tvError_t
 * @retval tvERROR_NONE                    Short circuit detection completed successfully.
 * @retval tvERROR_INVALID_PARAM           Invalid input parameter.
 * @retval tvERROR_INVALID_STATE           Detection logic failed to execute.
 * @retval tvERROR_GENERAL                 Underlying failures (SoC, memory, etc.).
 * @retval tvERROR_OPERATION_NOT_SUPPORTED Operation is not supported on this platform.
 *
 * @see GetNumberOfDimmingZones()
 *
 * @pre TvInit() should be called before calling this API.
 */
tvError_t GetLdimZoneShortCircuitStatus(unsigned char* shortcircuit_zone_list, unsigned int size, int* status);

/**
 * @brief Retrieves the number of dimming zones supported by the platform.
 *
 * On calling GetNumberOfDimmingZones, the API retrieves the number of dimming zones
 * available for the current platform.
 *
 * @param[out] number_of_dimming_zones  Pointer to an unsigned integer where the number of dimming zones
 *                                      will be stored. This is a platform-specific value.
 *
 * @return tvError_t
 * @retval tvERROR_NONE                    The number of dimming zones was retrieved successfully.
 * @retval tvERROR_INVALID_PARAM           Invalid input parameter (e.g., number_of_dimming_zones is NULL).
 * @retval tvERROR_INVALID_STATE           The system is not in a state where dimming zones can be queried.
 * @retval tvERROR_GENERAL                 Underlying failures (e.g., hardware issues, memory errors).
 * @retval tvERROR_OPERATION_NOT_SUPPORTED The platform does not support dimming zones.
 *
 * @pre TvInit() should be called before calling this API.
 */
tvError_t GetNumberOfDimmingZones(unsigned int* number_of_dimming_zones);

/**
 * @brief Sets 2Point Custom Whitebalance
 *
 * This function sets Whitebalance for a current picture mode index, primary video source @n
 * and primary video format.
 *
 * @param[in] color                 - Color type value. Valid value will be a member of ::tvWBColor_t
 * @param[in] control               - Control index value. Valid values will be a member of ::tvWBControl_t
 * @param[in] value                 - The WhiteBalance Value to be set.Valid range gain (0 - 2047) and offset (-1024 to 1023)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetCustom2PointWhiteBalance(tvWBColor_t color, tvWBControl_t control, int value);

/**
 * @brief Gets the current Custom WhiteBalance
 *
 * This function gets the current WhiteBalance value for the primary video source selected,
 * primary video format played,picture mode selected,given color and given control value..
 *
 * @param[in] color                 - Color type value. Valid value will be a member of ::tvWBColor_t
 * @param[in] control               - Control index value. Valid values will be a member of ::tvWBControl_t
 * @param[out] value                - Current WB value. Valid range gain  (0 - 2047) and offset (-1024 to 1023)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - Parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @retval tvERROR_GENERAL           - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 *
 * @see SetCustom2PointWhiteBalance()
 */
tvError_t GetCustom2PointWhiteBalance(tvWBColor_t color, tvWBControl_t control, int *value);

/**
 * @brief Saves WhiteBalance
 *
 * This function saves the WhiteBalance in picture profile database for the specific primary video format type
 * and primary video source. The saved Whitebalance value should be applied automatically whenever the
 * specified specified primary video format is played and specified primary video source is selected.
 *
 * @param[in] videoSrcType          - Source input value.Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pictureMode           - Picture mode value to be saved.Valid values are as per values returned by
 *                                    ::pic_modes_t.value  parmeter from GetTVSupportedPictureModes API.
 * @param[in] videoFormatType       - Video format type value.Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] color                 - color value.Valid value will be a member of ::tvWBColor_t
 * @param[in] control               - control value.Valid value will be a member of ::tvWBControl_t
 * @param[in] value                 - The WhiteBalance value to be set.Valid range gain  (0 - 2047) and offset (-1024 to 1023)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */

tvError_t SaveCustom2PointWhiteBalance(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType, tvWBColor_t color, tvWBControl_t control, int value);

#ifdef __cplusplus
}
#endif

#endif // End of _TV_SETTINGS_H

/** @} */ // End of TV_Settings_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
