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
 * @param[out] videoFormats    - List of available video formats.
 *                             - Array of pointers to `tvVideoFormatType_t` that will be populated with the supported video formats.
 *                             - The caller must allocate memory for the array of pointers (`tvVideoFormatType_t *`) before
 *                               invoking this function.
 *                             - The size of the array should be equal to the `VIDEO_FORMAT_MAX` index of the
 *                               `tvVideoFormatType_t` enumeration.
 *                             - Each pointer in the array must point to a valid memory location that can store a
 *                               `tvVideoFormatType_t` value.
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
 * @param[out] videoSources    - List of available video sources.
 *                             - Array of pointers to `tvVideoSrcType_t` that will be populated with the supported video sources.
 *                             - The caller must allocate memory for the array of pointers (`tvVideoSrcType_t *`) before
 *                               invoking this function.
 *                             - The size of the array should be equal to the `VIDEO_SOURCE_MAX` index of the
 *                               `tvVideoSrcType_t` enumeration.
 *                             - Each pointer in the array must point to a valid memory location that can store a
 *                               `tvVideoSrcType_t` value.
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
 * @brief Gets the Backlight capabilities.
 *
 * This function gets the Backlight capabilities from the Backlight section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support backlight, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_backlight - Maximum Backlight value.
 *                           - The minimum value will be 0.
 * @param[out] context_caps  - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetBacklightCaps(int *max_backlight, tvContextCaps_t ** context_caps);

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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @param[out] dimmingModes    - List of dimming modes.
 *                             - Array of pointers to `tvDimmingMode_t` that will be populated with the supported dimming modes.
 *                             - The caller must allocate memory for the array of pointers (`tvDimmingMode_t *`) before
 *                               invoking this function.
 *                             - The size of the array should be equal to the `tvDimmingMode_MAX` index of the
 *                               `tvDimmingMode_t` enumeration.
 *                             - Each pointer in the array must point to a valid memory location that can store a
 *                               `tvDimmingMode_t` value.
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
 * @param[in] dimmingMode           - Dimming mode to be set. Valid values are ( "Local", "Fixed", "Global" )
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
 * @param[out] dimmingMode           - Current dimming mode. Valid values are ( "Local", "Fixed", "Global" )
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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the DimmingMode capabilities.
 *
 *
 * This function gets the DimmingMode capabilities from the DimmingMode section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support TVDimmingMode, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] dimming_mode  - Returns a pointer to an array of platform-supported dimming modes.
 *                           - Values will be members of ::tvDimmingMode_t.
 *                           - The returned array must not be freed by the caller.
 *                           - Memory should be allocated in HAL function
 * @param[out] num_dimming_mode - The number of supported dimming modes.
 *                              - Represents the total elements in the `dimming_mode` array.
 *                              - Returns the length of the array pointed to by `dimming_mode`.
 *
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetTVDimmingModeCaps(tvDimmingMode_t** dimming_mode, size_t* num_dimming_mode, tvContextCaps_t** context_caps);

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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the Brightness capabilities.
 *
 * This function gets the Brightness capabilities from the Brightness section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support brightness, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_brightness - Maximum Brightness value.
 *                           - The minimum value will be 0.
 * @param[out] context_caps   - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetBrightnessCaps(int *max_brightness, tvContextCaps_t ** context_caps);

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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the Contrast capabilities.
 *
 * This function gets the Contrast capabilities from the Contrast section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support contrast, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_contrast - Maximum Contrast value.
 *                          - The minimum value will be 0.
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetContrastCaps(int* max_contrast, tvContextCaps_t ** context_caps);

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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the Sharpness capabilities.
 *
 * This function gets the Sharpness capabilities from the Sharpness section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support sharpness, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_sharpness - Maximum Sharpness value.
 *                           - The minimum value will be 0.
 * @param[out] context_caps  - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetSharpnessCaps(int *max_sharpness, tvContextCaps_t ** context_caps);

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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
 *
 * @param[in] videoSrcType          - Source input value. Valid value will be a member of ::tvVideoSrcType_t
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
 * @brief Gets the Saturation capabilities.
 *
 * This function gets the Saturation capabilities from the Saturation section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support saturation, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_saturation - The maximum allowable saturation level.
 *                          - The minimum value will be 0.
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetSaturationCaps(int* max_saturation, tvContextCaps_t ** context_caps);

/**
 * @brief Saves the saturation value
 *
 * This function saves the sharpness value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved saturation value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current saturation value applied in PQ module.
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the Hue capabilities.
 *
 * This function gets the Hue capabilities from the Hue section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support hue, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_hue      - Maximum Hue value.
 *                          - The minimum value will be 0.
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetHueCaps(int* max_hue, tvContextCaps_t ** context_caps);

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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the ColorTemperature capabilities.
 *
 * This function gets the ColorTemperature capabilities from the ColorTemperature section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support colorTemperature, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] color_temp   - Returns a pointer to an array of platform-supported color temperature modes.
 *                          - Values will be members of ::tvColorTemp_t.
 *                          - The returned array must not be freed by the caller.
 *                          - Memory should be allocated in HAL function
 * @param[out] num_color_temp - The total number of supported color temperature modes.
 *                            - Represents the number of elements in the `color_temp` array.
 *
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemperatureCaps(tvColorTemp_t** color_temp, size_t* num_color_temp, tvContextCaps_t** context_caps);

/**
 * @brief Saves the color temperature value
 *
 * This function saves the color temperature value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved color temperature value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current color temperature value applied in PQ module.
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the AspectRatio capabilities.
 *
 * This function gets the AspectRatio capabilities from the AspectRatio section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support AspectRatio, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] aspect_ratio  - Returns a pointer to an array of platform-supported aspect ratio modes.
 *                           - Values will be members of ::tvDisplayMode_t.
 *                           - The returned array must not be freed by the caller.
 *                           - Memory should be allocated in HAL function
 * @param[out] num_aspect_ratio - The total number of supported aspect ratio modes.
 *                              - Represents the number of elements in the `aspect_ratio` array.
 *
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetAspectRatioCaps(tvDisplayMode_t** aspect_ratio, size_t* num_aspect_ratio, tvContextCaps_t** context_caps);

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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the LowLatencyState capabilities.
 *
 * This function gets the LowLatencyState capabilities from the LowLatencyState section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support LowLatencyState, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_latency  - Maximum Latency value.
 *                          - The minimum value will be 0.
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetLowLatencyStateCaps(int* max_latency, tvContextCaps_t ** context_caps);

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
 * @param[out] dvModes[]       - List of available DV modes.
 *                             - Array of pointers to `tvDolbyMode_t` that will be populated with the supported DV modes.
 *                             - The caller must allocate memory for the array of pointers (`tvDolbyMode_t *`) before
 *                               invoking this function.
 *                             - The size of the array should be equal to the `tvMode_Max` index of the
 *                               `tvDolbyMode_t` enumeration.
 *                             - Each pointer in the array must point to a valid memory location that can store a
 *                               `tvDolbyMode_t` value.
 * @param[out] count           - Count of supported DV modes. Max is tvMode_Max and min is 0
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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @param[out] pictureModes    - List of available picture modes.
 *                             - Array of pointers to `pic_modes_t` that will be populated with the supported picture modes.
 *                             - The caller must allocate memory for the array of pointers (`pic_modes_t *`) before
 *                               invoking this function.
 *                             - The size of the array should be equal to the `PIC_MODES_SUPPORTED_MAX`.
 *                             - Each pointer in the array must point to a valid memory location that can store a
 *                               `pic_modes_t` value.
 * @param[out] count           - Count of supported picture modes. Maximum possile value is PIC_MODES_SUPPORTED_MAX. Min is 1.
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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * @brief Gets the PictureMode capabilities.
 *
 * This function gets the PictureMode capabilities from the PictureMode section of the pq_capabilities.json.
 *
 * For this feature num_context must be greater than zero. The context structure must be populated with 
 * the supported PictureMode, VideoSource, and VideoFormat specific to the platform.
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support PictureMode, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] mode          - Returns a pointer to an array of platform-supported PQ modes.
 *                           - Values will be members of ::tvPQModeIndex_t.
 *                           - The returned array must not be freed by the caller.
 *                           - Memory should be allocated in HAL function
 * @param[out] num_pic_modes  - The number of supported picture modes.
 *                             - Represents the total elements in `mode`.
 * @param[out] context_caps  - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
 tvError_t GetTVPictureModeCaps(tvPQModeIndex_t** mode, size_t* num_pic_modes, tvContextCaps_t** context_caps);

/**
 * @brief Sets or saves the rgain value
 *
 * This function sets or saves the rgain value for a specfic color temperature and video source. If it is set operation (saveOnly=0) @n
 * the rgb gain and offset for the specified colour temperature will be loaded in white balance module and @n
 * the new red gain value from this API will be applied and saved in the picture profile database.
 * The value is discarded and default value from picture profile database is used when primary video format
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the rgain will be saved for the specific video source and colour temperature. The saved
 * rgain value will be automatically applied in white balance module when the colour temperaure choice is made as result of
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] rgain                - Rgain Value to be set. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set and Save=0
 *                                   ( @a 0 for rgain value will be applied to PQ HW and saved in the picture profile database to use later.
 *                                     i.e changes can be visible immediately on screen
 *                                     @a 1 for rgain value will be saved and applied later i.e changes not visible immediately for current video)
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
 * the new green gain value from this API will be applied and saved in the picture profile database.
 * The value is discarded and default value from picture profile database is used when primary video format
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the ggain will be saved for the specific video source and colour temperature. The saved
 * ggain value should be automatically applied in white balance module when the colour temperaure choice is made as result of
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] ggain                - Ggain Value to be set. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set and Save=0
 *                                   ( @a 0 for ggain value will be applied to PQ HW and saved in the picture profile database to use later.
 *                                     i.e changes can be visible immediately on screen
 *                                     @a 1 for ggain value will be saved and applied later i.e changes not visible immediately for current video)
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
 * the new blue gain value from this API will be applied and saved in the picture profile database.
 * The value is discarded and default value from picture profile database is used when primary video format
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the bgain will be saved for the specific video source and colour temperature. The saved
 * bgain value will be automatically applied in white balance module when the colour temperaure choice is made as result of
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] bgain                - Bgain Value to be set. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set and Save=0
 *                                   ( @a 0 for bgain value will be applied to PQ HW and saved in the picture profile database to use later.
 *                                     i.e changes can be visible immediately on screen
 *                                     @a 1 for bgain value will be saved and applied later i.e changes not visible immediately for current video)
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
 * the new rpostoffset gain value from this API will be applied and saved in the picture profile database.
 * The value is discarded and default value from picture profile database is used when primary video format
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the rpostoffset will be saved for the specific video source and colour temperature. The saved
 * rpostoffset value should be automatically applied in white balance module when the colour temperaure choice is made as result of
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] rpostoffset          - Rpostoffset Value to be set. Valid range is  (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set And Save=0
 *                                   ( @a 0 for rpostoffset value will be applied to PQ HW and saved in the picture profile database to use later.
 *                                     i.e changes can be visible immediately on screen
 *                                     @a 1 for rpostoffset value will be saved and applied later i.e changes not visible immediately for current video)
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
 * the new gpostoffset gain value from this API will be applied and saved in the picture profile database.
 * The value is discarded and default value from picture profile database is used when primary video format
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the gpostoffset will be saved for the specific video source and colour temperature. The saved
 * gpostoffset value should be automatically applied in white balance module when the colour temperaure choice is made as result of
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] gpostoffset          - Gpostoffset Value to be set. Valid range is  (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set and Save=0
 *                                   ( @a 0 for gpostoffset value will be applied to PQ HW and saved in the picture profile database to use later.
 *                                     i.e changes can be visible immediately on screen
 *                                     @a 1 for gpostoffset value will be saved and applied later i.e changes not visible immediately for current video)
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
 * the new bpostoffset gain value from this API will be applied and saved in the picture profile database.
 * The value is discarded and default value from picture profile database is used when primary video format
 * or primary video source or picture mode changes.
 * If it is save operation (saveOnly =1) then the bpostoffset will be saved for the specific video source and colour temperature. The saved
 * bpostoffset value should be automatically applied in white balance module when the colour temperaure choice is made as result of
 * picture mode change or primary video format change or primary video source change.
 *
 * @param[in] colorTemp            - Color temperature value to be save/set. Valid value will be a member of ::tvColorTemp_t
 * @param[in] bpostoffset          - Bpostoffset Value to be set. Valid range is  (-1024 to +1023)
 * @param[in] sourceId             - SourceId value. Valid value will be a member of ::tvColorTempSourceOffset_t
 * @param[in] saveOnly             - Save=1 / Set and Save=0
 *                                   ( @a 0 for bpostoffset value will be applied to PQ HW and saved in the picture profile database to use later.
 *                                     i.e changes can be visible immediately on screen
 *                                     @a 1 for bpostoffset value will be saved and applied later i.e changes not visible immediately for current video)
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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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
 * This function will only set and doesn't save the value.
 *
 * @param[in] mode         - Valid values are true and false. true when gamma pattern mode needs to be enabled @n
 *                           false when gamma pattern mode needs to be disabled.
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
tvError_t SetRGBPattern(int r,int g, int b);

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
 * @brief Sets 2Point Custom WhiteBalance
 *
 * This function sets WhiteBalance (Red,Green,Blue Gain/Offset) for the current picture mode index, current video source,
 * and current video format.
 * The custom WhiteBalance (Red, Green, Blue Gain/Offset) is applicable only when the color temperature is set to tvColorTemp_USER.
 *
 * Gain                             - Modifies the intensity of Red, Green, and Blue at the brighter level
 * Offset                           - Modifies the intensity of Red, Green, and Blue at the darker level
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
 * @pre SetColorTemperature() should be set to "tvColorTemp_USER" before calling this API
 */
tvError_t SetCustom2PointWhiteBalance(tvWBColor_t color, tvWBControl_t control, int value);

/**
 * @brief Gets the Custom WhiteBalance
 *
 *  This function gets the custom WhiteBalance(Red,Green,Blue Gain/Offset) value for the current video source selected,
 *  current video format played,picture mode selected,given color and given control value.
 *
 *  The function always retrieves the custom WhiteBalance (Red, Green, Blue Gain/Offset) associated with tvColorTemp_USER.
 *
 *  Gain                            - Modifies the intensity of Red, Green, and Blue at the brighter level
 *  Offset                          - Modifies the intensity of Red, Green, and Blue at the darker level
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
 * @brief Gets the Custom2PointWhiteBalance capabilities.
 *
 * This function gets the Custom2PointWhiteBalance capabilities from the Custom2PointWhiteBalance section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support backlight, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] min_gain         - Minimum Gain.
 * @param[out] min_offset       - Minimum Saturation.
 * @param[out] max_gain         - Maximum Gain.
 * @param[out] max_offset       - Maximum Saturation.
 * @param[out] color - A structure representing the supported white balance color components.
 * @param[out] component - A structure defining the controls available for white balance adjustments.
 * @param[out] num_color - The total number of supported white balance color components.
 *                       - Represents the number of elements in the 'color' array.
 * @param[out] num_control - The total number of supported white balance control options.
 *                         - Represents the number of elements in the 'component' array.
 * @param[out] context_caps     - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCustom2PointWhiteBalanceCaps ( int *min_gain, int *min_offset, int *max_gain, int *max_offset, tvWBColor_t **color, tvWBControl_t **control, size_t* num_color, size_t* num_control, tvContextCaps_t ** context_caps );

/**
 * @brief Saves WhiteBalance
 *
 * This function saves the WhiteBalance in picture profile database for the specific primary video format type
 * and primary video source. The saved Whitebalance value should be applied automatically whenever the
 * specified specified primary video format is played and specified primary video source is selected.
 * Gain                             - Modifies the intensity of Red, Green, and Blue at the brighter level
 * Offset                           - Modifies the intensity of Red, Green, and Blue at the darker level
 * The supported formats, sources, and modes must be fetched from the configuration details of each specific feature in the
 * PQ capability configuration file.
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

 /**
 * @brief Gets the precision detail capabilities.
 *
 * This function gets the PrecisionDetail capabilities from the PrecisionDetail section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support precision detail, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_precision - Maximum Precision value
 *                          - The minimum value will be 0.
 * @param[out] context_caps  - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetPrecisionDetailCaps(int* max_precision, tvContextCaps_t ** context_caps);

/**
 * @brief Gets the precision detail setting.
 *
 * This function gets the precision detail setting for the primary video source selected,
 * primary video format played and picture mode selected.
 * If the platform does not support precision detail, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] precisionDetail - Current precision detail setting. Valid values are ( 0=disabled, 1=enabled )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetPrecisionDetail(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int * precisionDetail);

/**
 * @brief Sets the precision detail setting.
 *
 * This function sets the new precision detail setting, which only applies to the certain video formats in specific
 * picture modes and sources.
 * The change is applied to hardware if the current video format (DV) and picture mode (DV IQ or DV Bright) support
precision detail.
 * The saved precision detail setting shall be applied automatically whenever the current picture mode and current
primary video format support precision detail.
 *
 * If the platform does not support precision detail, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] precisionDetail - Current precision detail setting. Valid values are ( 0=disabled, 1=enabled )
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetPrecisionDetail(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int precisionDetail);

/**
 * @brief Gets all SDR gamma setting capabilities supported by the platform.
 *
 * This function gets the SDRGamma capabilities from the SDRGamma section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support SDR gamma setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] sdr_gamma     - Returns a pointer to an array of supported SDR gamma settings.
 *                           - Values will be members of ::tvPQModeIndex_t.
 *                           - The returned array must not be freed by the caller.
 *                           - Memory should be allocated in HAL function
 * @param[out] num_sdr_gamma  - The total number of supported SDR gamma settings.
 *                            - Represents the number of elements in the `sdr_gamma` array.
 * @param[out] context_caps  - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetSdrGammaCaps(tvSdrGamma_t ** sdr_gamma, size_t * num_sdr_gamma, tvContextCaps_t ** context_caps);

/**
 * @brief Gets the current SDR gamma setting for a given picture mode and primary video source.
 *
 * If the platform does not support an SDR gamma setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[out] sdrGamma - SDR gamma setting. Valid value will be a member of ::tvSdrGamma_t.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetSdrGamma(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvSdrGamma_t * sdrGamma);

/**
 * @brief Sets an SDR gamma value.
 *
 * This function sets the SDR gamma value in picture profile database for the specific picture mode
 * and primary video source. The saved SDR gamma value shall be applied automatically whenever the
 * specified picture mode is selected and specified primary video source is selected.
 *
 * The SDR gamma value is applied in the PQ module if the current picture mode and video source match
 * the parameters.
 *
 * If the platform does not support an SDR gamma setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] sdrGamma - Value of the SDR gamma to be set. Valid value will be member of ::tvSdrGamma_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetSdrGamma(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvSdrGamma_t sdrGamma);

/**
 * @brief Gets the maximum local contrast enhancement setting value supported by the platform.
 *
 * This function gets the LocalContrastEnhancement capabilities from the LocalContrastEnhancement section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The local contrast enhancement setting ranges from 0..N inclusive where 0 is OFF and N is the maximum effect
level and
 * value supported by the platform. The value of N is returned by this function.
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support a local contrast enhancement setting, then tvERROR_OPERATION_NOT_SUPPORTED is
returned.
 *
 * @param[out] maxLocalContrastEnhancement - Maximum local contrast enhancement setting value.
 *                                         - The minimum value will be 0.
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetLocalContrastEnhancementCaps(int * maxLocalContrastEnhancement, tvContextCaps_t ** context_caps);

/**
 * @brief Sets the local contrast enhancement value.
 *
 * This function sets the local contrast enhancement value for the specified picture mode,
 * primary video format and primary video source. The local contrast enhancement value should be applied
 * automatically by whenever the
 * specified picture mode, primary video format and primary video source is selected.
 *
 * The local contrast enhancement value is applied in the PQ module if the current picture mode, primary video
 * format and
 * primary video source match the parameters.
 *
 * If the platform does not support local contrast enhancement, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType    - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode         - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] localContrastEnhancement - Value of the local contrast enhancement to be set.
 *                                     - Valid values are from 0..N where 0=OFF and N is the maximum effect level, 
 *                                     - returned by GetLocalContrastEnhancementCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetLocalContrastEnhancement(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int localContrastEnhancement);

 /**
 * @brief Gets the local contrast enhancement value.
 *
 * This function gets the local contrast enhancement value for the specified picture mode,
 * primary video format and primary video source.
 *
 * If the platform does not support local contrast enhancement, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType              - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode                   - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType           - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] localContrastEnhancement - Value of the local contrast enhancement.
 *                                      - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                                      - returned by GetLocalContrastEnhancementCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetLocalContrastEnhancement(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int * localContrastEnhancement);

/**
 * @brief Gets the maximum MPEG noise reduction setting value supported by the platform.
 *
 * This function gets the MPEGNoiseReduction capabilities from the MPEGNoiseReduction section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The MPEG noise reduction setting ranges from 0..N inclusive where 0 is OFF and N is the maximum effect level and
 * value supported by the platform. The value of N is returned by this function.
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support an MPEG noise reduction setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] maxMPEGNoiseReduction - Maximum MPEG noise reduction setting value.
 *                                   - The minimum value will be 0.
 * @param[out] context_caps          - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetMPEGNoiseReductionCaps(int * maxMPEGNoiseReduction, tvContextCaps_t ** context_caps);

/**
 * @brief Sets the MPEG noise reduction value.
 *
 * This function sets the MPEG noise reduction value for the specific picture mode,
 * primary video format and primary video source. The set MPEG noise reduction value should be applied automatically by whenever the
 * specified picture mode, primary video format and primary video source is selected.
 *
 * The MPEG noise reduction value is applied in the PQ module if the current picture mode, primary video format and
 * primary video source match the parameters.
 *
 * If the platform does not support MPEG noise reduction, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType       - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode            - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType    - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] mpegNoiseReduction - Value of the MPEG noise reduction to be set.
 *                               - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                               - returned by GetMPEGNoiseReductionCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetMPEGNoiseReduction(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int mpegNoiseReduction);
/**
 * @brief Gets the MPEG noise reduction value.
 *
 * This function gets the MPEG noise reduction value for the specific picture mode,
 * primary video format and primary video source.
 *
 * If the platform does not support MPEG noise reduction, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType        - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode             - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType     - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] mpegNoiseReduction - Value of the MPEG noise reduction.
 *                                - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                                - returned by GetMPEGNoiseReductionCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetMPEGNoiseReduction(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int * mpegNoiseReduction);

/**
 * @brief Gets the maximum digital noise reduction setting value supported by the platform.
 *
 * This function gets the DigitalNoiseReduction capabilities from the DigitalNoiseReduction section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The digital noise reduction setting ranges from 0..N inclusive where 0 is OFF and N is the maximum effect level and
 * value supported by the platform. The value of N is returned by this function.
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support an digital noise reduction setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] maxDigitalNoiseReduction - Maximum digital noise reduction setting value.
 *                                      - The minimum value will be 0.
 * @param[out] context_caps             - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetDigitalNoiseReductionCaps(int * maxDigitalNoiseReduction, tvContextCaps_t ** context_caps);

/**
 * @brief Sets the digital noise reduction value.
 *
 * This function sets the digital noise reduction value for the specified picture mode,
 * primary video format and primary video source. The digital noise reduction value should be applied automatically by whenever the
 * specified picture mode, primary video format and primary video source are selected.
 *
 * The digital noise reduction value is applied in the PQ module if the current picture mode, primary video format and
 * primary video source match the parameters.
 *
 * If the platform does not support digital noise reduction, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType          - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] digitalNoiseReduction - Value of the digital noise reduction.
 *                                  - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                                  - returned by GetDigitalNoiseReductionCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetDigitalNoiseReduction(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int digitalNoiseReduction);

/**
 * @brief Gets the digital noise reduction value.
 *
 * This function gets the digital noise reduction value for the specified picture mode,
 * primary video format and primary video source.
 *
 * If the platform does not support digital noise reduction, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType            - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode                 - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType         - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] digitalNoiseReduction  - Value of the digital noise reduction.
 *                                    - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                                    - returned by GetDigitalNoiseReductionCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetDigitalNoiseReduction(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int * digitalNoiseReduction);

/**
 * @brief Gets the maximum AI super resolution setting value supported by the platform.
 *
 * This function gets the AISuperResolution capabilities from the AISuperResolution section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The AI super resolution setting ranges from 0..N inclusive where 0 is OFF and N is the maximum effect level and
 * value supported by the platform. The value of N is returned by this function.
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support an AI super resolution setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] maxAISuperResolution - Maximum AI super resolution setting value.
 *                                  - The minimum value will be 0.
 * @param[out] context_caps         - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetAISuperResolutionCaps(int * maxAISuperResolution, tvContextCaps_t ** context_caps);

/**
 * @brief Sets the AI super resolution value.
 *
 * This function sets the AI super resolution value in picture profile database for the specific picture mode,
 * primary video format and primary video source. The saved AI super resolution value shall be applied automatically whenever the
 * specified picture mode, primary video format and primary video source is selected.
 *
 * The AI super resolution value is applied in the PQ module if the current picture mode and video source match
 * the parameters.
 *
 * If the platform does not support an AI super resolution setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType      - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode           - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType   - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] aiSuperResolution - Value of the AI super resolution.
 *                              - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                              - returned by GetAISuperResolutionCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetAISuperResolution(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int aiSuperResolution);

/**
 * @brief Gets the AI super resolution value.
 *
 * This function gets the AI super resolution value in the picture profile database for the specific picture mode,
 * primary video format and primary video source.
 *
 * If the platform does not support an AI super resolution setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType       - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode            - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType    - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] aiSuperResolution - Value of the AI super resolution.
 *                               - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                               - returned by GetAISuperResolutionCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetAISuperResolution(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int * aiSuperResolution);

/**
 * @brief Gets the maximum MEMC setting value supported by the platform.
 *
 * This function gets the MEMC capabilities from the MEMC section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The MEMC setting ranges from 0..N inclusive where 0 is OFF and N is the maximum effect level and
 * value supported by the platform. The value of N is returned by this function.
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support a MEMC setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] maxMEMC      - Maximum MEMC setting value.
 *                          - The minimum value will be 0.
 *
 * @param[out] context_caps - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetMEMCCaps(int * maxMEMC, tvContextCaps_t ** context_caps);

/**
 * @brief Sets the MEMC value.
 *
 * This function sets the MEMC value in the picture profile database for the specific picture mode,
 * primary video format and primary video source. The saved MEMC value shall be applied automatically whenever the
 * specified picture mode, primary video format and primary video source is selected.
 *
 * The MEMC value is applied in the PQ module if the current picture mode and video source match
 * the parameters.
 *
 * If the platform does not support a MEMC setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType     - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode          - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType  - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] memc             - Value of the MEMC to be set.
 *                             - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                             - returned by GetMEMCCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetMEMC(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int memc);

/**
 * @brief Gets the MEMC value.
 *
 * This function gets the MEMC value in the picture profile database for the specific picture mode,
 * primary video format and primary video source.
 *
 * If the platform does not support a MEMC setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType      - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode           - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType   - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] memc             - Value of the MEMC to be set.
 *                              - Valid values are from 0..N where 0=OFF and N is the maximum effect level,
 *                              - returned by GetMEMCCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetMEMC(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int * memc);

/**
 * @brief Gets the multi-point white balance capabilities supported by the platform.
 *
 * This function gets the MultiPointWB capabilities from the MultiPointWB section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The number of supported multi-point white balance (gamma) points used in the HAL is returned in `num_hal_matrix_points`.
 * The HAL must be given this number of points when a white balance gamma adjustment matrix is set.
 * All points in the HAL matrix are evenly spaced from 0.0 to 1.0.
 *
 * The min and max values for red, green and blue values for each point are returned in `rgb_min` and `rgb_max`.
 * This range is shared by the HAL gamma adjustment matrix and the UI gamma adjustment matrix.
 *
 * The UI gamma adjustment matrix may contain a different number of points to the HAL gamma adjustment matrix,
 * primarily to reduce the number of points that need adjustment during user calibration.
 * While it is typical for the HAL matrix to contain 256 or 1024 points, the UI matrix will typically have 11 or 20.
 * Where a UI matrix has a low count (<20) then the interval of each point may not be evenly spaced.
 * The `ui_matrix_positions` receives a pointer to an array of positions related to the UI gamma adjustment matrix.
 *
 * The same capabilities apply to any multi-point white balance gamma matrix; any picture mode, color temperature, video source and video format.
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support multi-point white balance, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] num_hal_matrix_points - The number of points in the HAL gamma matrix.
 * @param[out] rgb_min               - The minimum value for red, green and blue adjustment values.
 * @param[out] rgb_max               - The maximum value for red, green and blue adjustment values.
 * @param[out] num_ui_matrix_points  - The number of points in the UI gamma matrix for customer adjustment.
 * @param[out] ui_matrix_positions   - An array of positions for the UI matrix points.
 *                                     Points to an array with `num_ui_matrix_points` elements with values between 0.0 and 1.0.
 * @param[out] context_caps          - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetMultiPointWBCaps(int * num_hal_matrix_points, int * rgb_min, int * rgb_max, int * num_ui_matrix_points, double ** ui_matrix_positions, tvContextCaps_t ** context_caps);

/**
 * @brief Sets the multi-point white balance red, green and blue values for the whole matrix.
 *
 * This function sets the multi-point white balance values in the picture profile database for the specific picturemode, color temperature,
 * primary video format and primary video source. The matrix values should be applied automatically by whenever the
 * specified picture mode, specified primary video format and specified primary video source is selected.
 *
 * The matrix values are applied in the PQ module if the current picture mode, primary video format and primary video source match the parameters.
 *
 * The red, green and blue values are provided for all points in the matrix.
 * The 'r', 'g' and 'b' parameters point to integer arrays which must contain `num_hal_matrix_points` elements as returned by GetMultiPointWBCaps().
 *
 * If the platform does not support multi-point white balance, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] colorTemp       - Color temperature type value. Valid value will be a member of ::tvColorTemp_t
 * @param[in] pq_mode         - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] videoSrcType    - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] r               - Array of red values. Element values must be `rgb_min` <= r <= `rgb_max` as returned by GetMultiPointWBCaps().
 * @param[in] g               - Array of green values. Element values must be `rgb_min` <=g <= `rgb_max` as returned by GetMultiPointWBCaps().
 * @param[in] b               - Array of blue values. Element values must be `rgb_min` <=b <= `rgb_max` as returned by GetMultiPointWBCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetMultiPointWBMatrix(tvColorTemp_t colorTemp, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, tvVideoSrcType_t videoSrcType, int * r, int * g, int * b);

/**
* @brief Gets the multi-point white balance red, green and blue values for the whole matrix.
*
* This function gets the multi-point white balance values from the picture profile database for the specific picture mode, color temperature,
* primary video format and primary video source.
*
* The red, green and blue values are provided for all points in the matrix.
* The 'r', 'g' and 'b' parameters point to integer arrays which must contain `num_hal_matrix_points` elements as returned by GetMultiPointWBCaps().
*
* If the platform does not support multi-point white balance, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
*
* @param[in] colorTemp         - Color temperature type value. Valid value will be a member of ::tvColorTemp_t
* @param[in] pq_mode           - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
* @param[in] videoFormatType   - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
* @param[in] videoSrcType      - Source input value. Valid value will be a member of ::tvVideoSrcType_t
* @param[in] r                 - Array of red values.  Element values must be `rgb_min` <= r <= `rgb_max` as returned by GetMultiPointWBCaps().
* @param[in] g                 - Array of green values.  Element values must be `rgb_min` <= g <= `rgb_max` as returned by GetMultiPointWBCaps().
* @param[in] b                 - Array of blue values.  Element values must be `rgb_min` <= b <= `rgb_max` as returned by GetMultiPointWBCaps().
*
* @return tvError_t
*
* @retval tvERROR_NONE                     - Success
* @retval tvERROR_INVALID_PARAM            - Input parameter is invalid
* @retval tvERROR_INVALID_STATE            - Interface is not initialized
* @retval tvERROR_OPERATION_NOT_SUPPORTED  - Operation is not supported
* @retval tvERROR_GENERAL                  - Underlying failures - SoC, memory, etc
*
* @pre TvInit() should be called before calling this API
*/
tvError_t GetMultiPointWBMatrix(tvColorTemp_t colorTemp, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, tvVideoSrcType_t videoSrcType, int * r, int * g, int * b);

/**
 * @brief Gets the Dolby Vision PQ Calibration setting capabilities supported by the platform.
 *
 * This function gets the DolbyVisionCalibration capabilities from the DolbyVisionCalibration section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 * The min and max values for Tmax, Tmin, Tgamma, Rx, Ry, Gx, Ry, Bx, By, Wx and Wy are returned.
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The `context_caps` shall return only the Dolby Vision picture modes.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support Dolby Vision PQ Calibration, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] min_values   - Returns a pointer to an structure which contains minimum values of DV calibration params.
 *                          - The returned Pointer must not be freed by the caller.
 *                          - Memory should be allocated in HAL function
 * @param[out] max_values   - Returns a pointer to an structure which contains maximum values of DV calibration params.
 *                          - The returned Pointer must not be freed by the caller.
 *                          - Memory should be allocated in HAL function
 * @param[out] component    - Returns a pointer to an array of platform-supported component type.
 *                          - Values will be members of ::tvDVCalibrationComponent_t.
 *                          - The returned array must not be freed by the caller.
 *                          - Memory should be allocated in HAL function
 * @param[out] num_component - The total number of supported DVCalibration component types.
 *                           - Represents the number of elements in the 'component' array.
 *
 * @param[out] context_caps  - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetDVCalibrationCaps(tvDVCalibrationSettings_t **min_values, tvDVCalibrationSettings_t **max_values, tvDVCalibrationComponent_t **component, size_t *num_component, tvContextCaps_t **context_caps);

/**
 * @brief Sets the Dolby Vision PQ calibration values.
 *
 * This function sets the Dolby Vision PQ calibration values in the picture profile database for the specified picture mode.
 * The saved calibration values shall be applied automatically whenever the specified picture mode is selected.
 *
 * The calibration values are applied in the PQ module if the current picture mode matches the parameters.
 *
 * If the platform does not support Dolby Vision PQ calibration, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType       - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode            - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType    - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] calibration_values - Structure of Dolby Vision PQ calibration values.
 *                               - Valid values are returned by GetDVCalibrationCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetDVCalibration(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, tvDVCalibrationSettings_t * calibration_values);

/**
 * @brief Gets the Dolby Vision PQ calibration values.
 *
 * This function gets the Dolby Vision PQ calibration values in the picture profile database for the specified picture mode.
 *
 * If the platform does not support Dolby Vision PQ calibration, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 * If no Dolby Vision PQ calibration has been set for the specified picture mode, then tvERROR_GENERAL is returned.
 *
 * @param[in] videoSrcType        - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode             - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType     - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] calibration_values - Structure of Dolby Vision PQ calibration values.
 *                                - Valid values are returned by GetDVCalibrationCaps().
 *                                - Memory should be allocated in HAL function
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetDVCalibration(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, tvDVCalibrationSettings_t * calibration_values);

/**
 * @brief Gets the default Dolby Vision PQ calibration values.
 *
 * This function gets the default Dolby Vision PQ calibration values in the picture profile database for the specified picture mode.
 *
 * If the platform does not support Dolby Vision PQ calibration, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType        - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode             - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType     - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] calibration_values - Structure of Dolby Vision PQ calibration values.
 *                                - Valid values are returned by GetDVCalibrationCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetDVCalibrationDefault(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, tvDVCalibrationSettings_t * calibration_values);

/**
 * @brief Gets the CMS capabilities.
 *
 * This function gets the CMS capabilities from the CMS section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support colorTemperature, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] max_hue          - Maximum Hue value.
 *                              - The minimum value will be 0.
 * @param[out] max_saturation   - Maximum Saturation value.
 *                              - The minimum value will be 0.
 * @param[out] max_luma         - Maximum Luma value.
 *                              - The minimum value will be 0.
 * @param[out] color            - Returns a pointer to an array of platform-supported component color.
 *                              - Values will be members of ::tvDataComponentColor_t.
 *                              - The returned array must not be freed by the caller.
 *                              - Memory should be allocated in HAL function
 * @param[out] component        - Returns a pointer to an array of platform-supported component type.
 *                              - Values will be members of ::tvComponentType_t.
 *                              - The returned array must not be freed by the caller.
 *                              - Memory should be allocated in HAL function
 * @param[out] num_color - The total number of supported component colors.
 *                       - Represents the number of elements in the 'color'' array.
 * @param[out] num_component - The total number of supported component types.
 *                           -Represents the number of elements in the 'component' array.
 * @param[out] context_caps     - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCMSCaps (int *max_hue, int *max_saturation,int *max_luma, tvDataComponentColor_t **color, tvComponentType_t **component, size_t* num_color, size_t* num_component, tvContextCaps_t **context_caps);
 
 /**
 * @brief Gets the VideoSource capabilities.
 *
 * This function gets the VideoSource capabilities from the VideoSource section of the pq_capabilities.json.
 *
 * If the platform does not support colorTemperature, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] source       - Returns a pointer to an array of platform-supported video sources.
 *                          - Values will be members of ::tvVideoSrcType_t.
 *                          - The returned array must not be freed by the caller.
 *                          - Memory should be allocated in HAL function
 * @param[out] num_video_source - The total number of supported video sources.
 *                             - Represents the number of elements in the `source` array.
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetVideoSourceCaps( tvVideoSrcType_t **source, size_t* num_video_source);

 /**
 * @brief Gets the VideoFramerate capabilities.
 *
 * This function gets the VideoFramerate capabilities from the VideoFramerate section of the pq_capabilities.json.
 *
 * If the platform does not support colorTemperature, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] framerate    - Returns a pointer to an array of platform-supported video framerates.
 *                          - Values will be members of ::tvVideoFrameRate_t.
 *                          - The returned array must not be freed by the caller.
 *                          - Memory should be allocated in HAL function
 * @param[out] num_video_framerate - The total number of supported video framerates.
 *                             - Represents the number of elements in the `framerate` array.
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetVideoFrameRateCaps( tvVideoFrameRate_t **framerate, size_t* num_video_framerate);

 /**
 * @brief Gets the VideoFormat capabilities.
 *
 * This function gets the VideoFormat capabilities from the VideoFormat section of the pq_capabilities.json.
 *
 * If the platform does not support colorTemperature, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] format       - Returns a pointer to an array of platform-supported video formats.
 *                          - Values will be members of ::tvVideoFormatType_t.
 *                          - The returned array must not be freed by the caller.
 *                          - Memory should be allocated in HAL function
 * @param[out] num_video_format - The total number of supported video formats.
 *                             - Represents the number of elements in the `format` array.
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetVideoFormatCaps(tvVideoFormatType_t **format, size_t* num_video_format);

 /**
 * @brief Gets the VideoResolution capabilities.
 *
 * This function gets the VideoResolution capabilities from the VideoResolution section of the pq_capabilities.json.
 *
 * If the platform does not support colorTemperature, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] resolution   - Returns a pointer to an array of platform-supported video resolutions.
 *                          - Values will be members of ::tvVideoResolution_t.
 *                          - The returned array must not be freed by the caller.
 *                          - Memory should be allocated in HAL function
 * @param[out] num_video_resolution - The total number of supported video resolution.
 *                                  - Represents the number of elements in the `resolution` array.
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetVideoResolutionCaps( tvVideoResolution_t ** resolution, size_t* num_video_resolution);

/**
 * @brief Gets the BacklightMode capabilities.
 *
 * This function gets the BacklightMode capabilities from the BacklightMode section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support backlight, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] backlight_mode - A structure representing the supported backlight modes.
 * @param[out] num_backlight_mode - The total number of supported backlight modes. Represents the number of elements in the backlight_mode array.
 * @param[out] context_caps  - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetBacklightModeCaps(tvBacklightMode_t** backlight_mode, size_t* num_backlight_mode, tvContextCaps_t** context_caps);

/**
 * @brief Saves the BacklightMode value
 *
 * This function saves the BacklightMode value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved BacklightMode value should be applied automatically whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current BacklightMode value applied in PQ module.
 *
 * @param[in] videoSrcType          - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode               - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] value                 - Value of the BacklightMode to be set. Valid value will be member of ::tvBacklightMode_t
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveBacklightMode(tvVideoSrcType_t videoSrcType, int pq_mode, tvVideoFormatType_t videoFormatType, tvBacklightMode_t value);

/**
 * @brief Sets 2Point WhiteBalance across all colorTemperature
 *
 * This function Sets WhiteBalance (Red,Green,Blue Gain/Offset) for the Given colorTemperature,color,control,current picture mode index, current video source,
 * and current video format.
 *
 * Gain                             - Modifies the intensity of Red, Green, and Blue at the brighter level
 * Offset                           - Modifies the intensity of Red, Green, and Blue at the darker level
 *
 * @param[in] colorTemperature      - ColorTemperature value. Valid value will be a member of ::tvColorTemp_t
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
tvError_t Set2PointWB(tvColorTemp_t colorTemperature, tvWBColor_t color, tvWBControl_t control, int value);

/**
 * @brief Gets the 2 PointWhiteBalance.
 *
 *  This function gets the WhiteBalance(Red,Green,Blue Gain/Offset) value for the current video source selected,
 *  current video format played,picture mode selected,given colorTemperature,color and control value.
 *
 *
 *  Gain                            - Modifies the intensity of Red, Green, and Blue at the brighter level
 *  Offset                          - Modifies the intensity of Red, Green, and Blue at the darker level
 *
 * @param[in] colorTemperature      - ColorTemperature value. Valid value will be a member of ::tvColorTemp_t
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
 * @see Set2PointWB()
 */
tvError_t Get2PointWB(tvColorTemp_t colorTemperature, tvWBColor_t color, tvWBControl_t control, int *value);

/**
 * @brief Gets the 2PointWhiteBalance capabilities.
 *
 * This function gets the 2PointWhiteBalance capabilities from the 2PointWhiteBalance section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and platform_support is true,
 * the corresponding pqmode, source, and format entries should be retrieved from the picturemode section
 * of pq_capabilities.json
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support 2PointWB, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] min_gain              - Minimum Gain.
 * @param[out] min_offset            - Minimum Offset.
 * @param[out] max_gain              - Maximum Gain.
 * @param[out] max_offset            - Maximum Offset.
 * @param[out] colorTemperature      - A pointer to an array of the supported colorTemperature components.
 * @param[out] color                 - A pointer to an array of the supported white balance color components.
 * @param[out] component             - A pointer to an array of the supported controls available for white balance adjustments.
 * @param[out] num_colorTemperature  - The total number of supported white balance colorTemperature components.
 *                                   - Represents the number of elements in the 'color' array.
 * @param[out] num_color             - The total number of supported white balance color components.
 *                                   - Represents the number of elements in the 'color' array.
 * @param[out] num_control           - The total number of supported white balance control options.
 *                                   - Represents the number of elements in the 'component' array.
 * @param[out] context_caps          - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t Get2PointWBCaps ( int *min_gain, int *min_offset, int *max_gain, int *max_offset, tvWBColor_t **color, tvColorTemp_t **colorTemperature,  tvWBControl_t **control, size_t* num_colorTemperature, size_t* num_color, size_t* num_control, tvContextCaps_t ** context_caps );

/**
 * @brief Saves 2PointWB
 *
 * This function saves the WhiteBalance in picture profile database for the specific colorTemperature, primary video format type
 * PictureMode and primary video source. The saved Whitebalance value should be applied automatically whenever the
 * specified primary video format is played and specified primary video source is selected.
 * Gain                             - Modifies the intensity of Red, Green, and Blue at the brighter level
 * Offset                           - Modifies the intensity of Red, Green, and Blue at the darker level
 *
 * @param[in] videoSrcType          - Source input value.Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pictureMode           - Picture mode value to be saved. Valid values are as per values returned by
 *                                    ::pic_modes_t.value  parameter from GetTVSupportedPictureModes API.
 * @param[in] videoFormatType       - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] colorTemperature      - ColorTemperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[in] color                 - Color value. Valid value will be a member of ::tvWBColor_t
 * @param[in] control               - Control value. Valid value will be a member of ::tvWBControl_t
 * @param[in] value                 - The WhiteBalance value to be set. Valid range gain  (0 - 2047) and offset (-1024 to 1023)
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

tvError_t Save2PointWB(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType, tvColorTemp_t colorTemperature, tvWBColor_t color, tvWBControl_t control, int value);

/**
 * @brief Gets the default 2PointWhiteBalance.
 *
 *  This function gets the default WhiteBalance(Red,Green,Blue Gain/Offset) value for the given videoSource,
 *  videoFormat,pictureMode,colorTemperature,color and control value.
 *
 *
 *  Gain                            - Modifies the intensity of Red, Green, and Blue at the brighter level
 *  Offset                          - Modifies the intensity of Red, Green, and Blue at the darker level
 *
 * @param[in] videoSrcType          - Source input value.Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pictureMode           - Picture mode value to be saved.Valid values are as per values returned by
 *                                    ::pic_modes_t.value  parmeter from GetTVSupportedPictureModes API.
 * @param[in] videoFormatType       - Video format type value.Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] colorTemperature      - ColorTemperature value. Valid value will be a member of ::tvColorTemp_t
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
 * @see Set2PointWB()
 */
tvError_t GetDefault2PointWB(tvVideoSrcType_t videoSrcType, int pq_mode,tvVideoFormatType_t videoFormatType,tvColorTemp_t colorTemperature, tvWBColor_t color, tvWBControl_t control, int *value);

/**
 * @brief Gets the Backlight Dimming Level capabilities and maximum Dimming Level setting value supported by the platform.
 *
 * This function gets the Dimming Level capabilities from the "Dimming Level" section of the pq_capabilities.json.
 *
 * If this feature is global (`num_contexts == 0`) and `platform_support` is true,
 * the corresponding picture mode, source, and format entries should be retrieved from the "picturemode" section
 * of pq_capabilities.json
 *
 * The Dimming Level setting ranges from 0..N inclusive where 0 is OFF (Fixed Backlight) and N is the maximum dimming effect level
 * supported by the platform. The value of N is returned by this function.
 *
 * Dimming Level 0 refers to the Fixed Backlight mode, where values > 0 refer to different dimming levels supported by
 * Local or Global dimming. At any point in time, the platform shall support either Global or Local dimming (implementation specific).
 *
 * The `context_caps` parameter receives a pointer to a `tvContextCaps_t` structure that lists the different
 * configuration contexts that this feature can be configured for.
 *
 * The capabilities structure returned by this call is allocated by the HAL function and shall
 * be safe to reference for the lifetime of the process.
 *
 * If the platform does not support a Dimming Level setting, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[out] maxDimmingLevel       - Maximum Dimming Level setting value.
 *                                   - The minimum value is always 0.
 * @param[out] context_caps          - A capabilities structure listing the configuration contexts supported.
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */

tvError_t GetBacklightDimmingLevelCaps(int* maxDimmingLevel, tvContextCaps_t** context_caps);
/**
 * @brief Sets the Dimming Level value.
 *
 * This function sets the Dimming Level value for the specific picture mode, primary video format and primary video source.
 * The configured Dimming Level value should be applied automatically whenever the
 * specified picture mode, primary video format and primary video source are selected.
 *
 * The Dimming Level value is applied in the PQ module if the current picture mode, primary video format and
 * primary video source match the parameters.
 *
 * If the platform does not support Dimming Level, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType       - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode            - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType    - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[in] dimmingLevel       - Value of the Dimming Level to be set.
 *                               - Valid values are from 0..N where 0=OFF (Fixed Backlight) and N is the maximum dimming level,
 *                               - returned by GetBacklightDimmingLevelCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SetBacklightDimmingLevel(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int dimmingLevel);
/**
 * @brief Gets the Dimming Level value.
 *
 * This function gets the Dimming Level value for the specific picture mode,
 * primary video format and primary video source.
 *
 * If the platform does not support Dimming Level, then tvERROR_OPERATION_NOT_SUPPORTED is returned.
 *
 * @param[in] videoSrcType        - Source input value. Valid value will be a member of ::tvVideoSrcType_t
 * @param[in] pq_mode             - Picture mode index. Valid value will be a member of ::tvPQModeIndex_t
 * @param[in] videoFormatType     - Video format type value. Valid value will be a member of ::tvVideoFormatType_t
 * @param[out] dimmingLevel       - Value of the Dimming Level.
 *                                - Valid values are from 0..N where 0=OFF (Fixed Backlight) and N is the maximum dimming level,
 *                                - returned by GetBacklightDimmingLevelCaps().
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE - Success
 * @retval tvERROR_INVALID_PARAM - Input parameter is invalid
 * @retval tvERROR_INVALID_STATE - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED - Operation is not supported
 * @retval tvERROR_GENERAL - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetBacklightDimmingLevel(tvVideoSrcType_t videoSrcType, tvPQModeIndex_t pq_mode, tvVideoFormatType_t videoFormatType, int * dimmingLevel);

#ifdef __cplusplus
}
#endif

#endif // End of _TV_SETTINGS_H

/** @} */ // End of TV_Settings_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
