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
#include <string>
#include "tvError.h"
#include "tvTypes.h"
#include <vector>
#ifdef __cplusplus
extern "C"
{
#endif
#define MAX_STRING_SIZE (15)
#define CONTROL_COUNT (2)
#define PIC_MODES_SUPPORTED_MAX   (15)
#define PIC_MODE_NAME_MAX (25)
#define DIMMING_MODE_NAME_SIZE    (25)
#define DIMMING_MODE_MAX          (10)
#define GAIN_MIN         (0)
#define GAIN_MAX         (2047)
#define OFFSET_MIN       (-1024)
#define OFFSET_MAX       (1024)
#define BACKLIGHT_CURVE_MAX_INDEX     (101)
#define EXPECTED_FILE_SIZE (512)
#define GENERIC_MODE_CONFIG_FILE  "/etc/tv/allmodes.conf"

typedef void (*tvVideoFormatChangeCB)(tvVideoHDRFormat_t format,void *userData);

typedef void (*tvVideoContentChangeCB)(tvContentType_t mode,void *userData);

typedef struct pic_modes{
    char name[PIC_MODE_NAME_MAX];
    short int value;
}pic_modes_t;

typedef struct
{
    void *userdata;
    tvVideoFormatChangeCB cb;
}tvVideoFormatCallbackData;

typedef struct
{
    void *userdata;
    tvVideoContentChangeCB cb;
}tvVideoContentCallbackData;

typedef enum {
    mfrColorTemp_STANDARD = 0,
    mfrColorTemp_COLD,
    mfrColorTemp_WARM,
    mfrColorTemp_USER,
    mfrColorTemp_MAX
}fp_mfrColorTemp_t;

typedef enum input_source_offset_e {
    HDMI_OFFSET_NEW = 0,
    TV_OFFSET_NEW   = 4,
    AV_OFFSET_NEW   = 8,
    MAX_OFFSET_NEW
} input_source_offset_t;

typedef struct getWBInfo {
    char wbControls[CONTROL_COUNT][MAX_STRING_SIZE];
    char wbGain[CONTROL_COUNT][MAX_STRING_SIZE];
    char wbOffset[CONTROL_COUNT][MAX_STRING_SIZE];
}getWBInfo_t;

#ifndef __BL_PARA__
#define __BL_PARA__
typedef struct bl_para_s{
    int mBacklightSDR;
    int mBacklightHDR;
}bl_para_t;
#endif

typedef struct tvBacklightInfo_s{
    int sdrBLCurve[BACKLIGHT_CURVE_MAX_INDEX];
    int hdrBLCurve[BACKLIGHT_CURVE_MAX_INDEX];
    int defaultBLSDR;
    int defaultBLHDR;
}tvBacklightInfo_t;

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
 */
tvError_t tvInit();
/**
 * @brief Sync the calibrated data to driver
 *
 * This function is to read the calibration data from serialization area and sync to driver during init.
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
tvError_t tvSD3toCriSyncInit();

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
tvError_t tvTerm();
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
 * video format played and picture mode selected
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
 * @brief Sets the brightness value to driver register(s)
 *
 * This function updates the new brightness value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @brief Sets the contrast value to driver register(s)
 *
 * This function updates the new contrast value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected.
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
 * @brief Sets the sharpness value to driver register(s)
 *
 * This function updates the new sharpness value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @brief Sets the saturation value to driver register(s)
 *
 * This function updates the new saturation value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @brief Sets the hue value to driver register(s)
 *
 * This function updates the new hue value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @brief Sets the color temperature to driver register(s)
 *
 * This function updates the new color temperature value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @brief Sets the aspect ratio
 *
 * This function updates the new aspect ratio value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @brief Gets the current tint value
 *
 * This function gets the current tint value for the primary video
 * source selected,primary video format played and picture mode selected
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
tvError_t GetTint(int *tint);
/**
 * @brief Sets the tint value to driver register(s)
 *
 * This function updates the new tint value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected.
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
tvError_t SetTint(int tint);

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
tvError_t GetCurrentVideoFormat(tvVideoHDRFormat_t *format);
/**
 * @brief Gets the current video resolution
 *
 * This function gets the video resolution of the current primary video played on TV
 *
 * @param[out] res - Resolution
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
tvError_t GetVideoResolution(tvResolutionParam_t *res);
/**
 * @brief Gets current video framerate
 *
 * This function gets the video frame rate of the current primary video played on TV
 *
 * @param[out] format - Format
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
tvError_t GetVideoFrameRate(tvVideoFrameRate_t *format);
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
tvError_t setWakeupConfig(const tvWakeupSrcType_t src_type, const bool value);

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
 * @brief Set the rgain value.
 *
 * This function sets the rgain value for specfic color temperature.
 *
 * @param[in] colorTemp - color temperature
 * @param[in] rgain - rgain
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
tvError_t SetColorTemp_Rgain(tvColorTemp_t colorTemp, int rgain);
/**
 * @brief Get the ggain value.
 *
 * This function gets the ggain value for specfic color temperature.
 *
 * @param[in] colorTemp - color temperature
 * @param[in] rgain - rgain
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
tvError_t GetColorTemp_Rgain(tvColorTemp_t colorTemp, int* rgain);
/**
 * @brief Set the ggain value.
 *
 * This function sets the ggain value for specfic color temperature.
 *
 * @param[in] colorTemp - color temperature
 * @param[in] ggain - ggain
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
tvError_t SetColorTemp_Ggain(tvColorTemp_t colorTemp, int ggain);
/**
 * @brief Get the ggain value.
 *
 * This function gets the ggain value for specfic color temperature.
 *
 * @param[in] colorTemp - color temperature
 * @param[in] ggain - ggain
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
tvError_t GetColorTemp_Ggain(tvColorTemp_t colorTemp, int* ggain);
/**
 * @brief Set the bgain value.
 *
 * This function sets the bgain value for specfic color temperature.
 *
 * @param[in] colorTemp - Color Temperature
 * @param[in] bgain - Bgain value
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
tvError_t SetColorTemp_Bgain(tvColorTemp_t colorTemp, int bgain);
/**
 * @brief Get the bgain value.
 *
 * This function gets the bgain value for specfic color temperature.
 *
 * @param[in] colorTemp - Color Temperature
 * @param[out] bgain - bgain
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
tvError_t GetColorTemp_Bgain(tvColorTemp_t colorTemp, int* bgain);
/**
 * @brief Set the rpostoffset value.
 *
 * This function sets the rpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp - Color Temperature
 * @param[in] rpostoffset - rpostoffset
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
tvError_t SetColorTemp_R_post_offset(tvColorTemp_t colorTemp, int rpostoffset);
/**
 * @brief Get the rpostoffset value.
 *
 * This function gets the rpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp - Color Temperature
 * @param[in] rpostoffset - rpostoffset
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
tvError_t GetColorTemp_R_post_offset(tvColorTemp_t colorTemp, int* rpostoffset);
/**
 * @brief Set the gpostoffset value.
 *
 * This function sets the gpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp - Color Temperature
 * @param[out] gpostoffset - gpostoffset
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
tvError_t SetColorTemp_G_post_offset(tvColorTemp_t colorTemp, int gpostoffset);
/**
 * @brief Get the gpostoffset value.
 *
 * This function gets the gpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp - Color Temperature
 * @param[in] gpostoffset - gpostoffset
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
tvError_t GetColorTemp_G_post_offset(tvColorTemp_t colorTemp, int* gpostoffset);
/**
 * @brief Set the bpostoffset value.
 *
 * This function sets the bpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp - Color Temperature
 * @param[out] bpostoffset - bpostoffset
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
tvError_t SetColorTemp_B_post_offset(tvColorTemp_t colorTemp, int bpostoffset);
/**
 * @brief Get the gpostoffset value.
 *
 * This function gets the gpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp - Color Temperature
 * @param[in] bpostoffset - bpostoffset
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
tvError_t GetColorTemp_B_post_offset(tvColorTemp_t colorTemp, int* bpostoffset);

/**
 * @brief Gets the supported picture modes and their count
 *
 * This function get the array of picture modes supported and their count
 *
 * @param[out] pictureModes              - List of available picture modes. Valid values are as per values returned by pic_modes_t.name and pic_modes_t.values parameter.
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
 * @brief Registers the video format change callback
 *
 * This function registers a callback for video format change event.
 * Once registered, the callback function will be called by the TV Settings HAL implementation
 * whenever the system detects a change in video format of the primary video currently played.
 *
 * @param[in] cbData                - Callback data. Please refer ::tvVideoFormatCallbackData
 *
 * @pre TvInit() should be called before calling this API
 */
void RegisterVideoFormatChangeCB(tvVideoFormatCallbackData& cbData);
/**
 * @brief Registers the VideoContent FMM change callback
 *
 * This function registers a callback for the playback Filmmaker mode change event.
 * Once registered, the callback function will be called by the TV Settings HAL implementation
 * When the system detects SEI content_type 0x01 and content_subtype 0x00, the FMM enter event is raised.
 * When the system detects SEI content_type is other than 0x01 or content_subtype is other than 0x00, the FMM exit event is raised.
 * This applies only to IP video sources and Tuner video sources.
 *
 * @param[in] cbData                - Callback data. Please refer::tvVideoContentCallbackData
 *
 *
 * @pre TvInit() should be called before calling this API
 */
void RegisterVideoContentChangeCB(tvVideoContentCallbackData &cbData);
/**
 * @brief tv Video Resolution ChangeCB
 *
 *
 * @pre TvInit() should be called before calling this API
 */
typedef void (*tvVideoResolutionChangeCB)(tvResolutionParam_t resolutionStruct,void *userData);
typedef struct
{
    void *userdata;
    tvVideoResolutionChangeCB cb;
}tvVideoResolutionCallbackData;

/**
 * @brief Registers the Video resolution change callback.
 *
 * This function registers a callback for playback content video resolution change event.
 * Once registered, the callback function will be called by the TV Settings HAL implementation
 * whenever the system detects resolution change for the primary video currently played.
 *
 * @param[in] cbData                - Callback data. Please refer ::tvVideoResolutionCallbackData
 *
 *
 * @pre TvInit() should be called before calling this API
 */
void RegisterVideoResolutionChangeCB(tvVideoResolutionCallbackData& cbData);
/**
 * @brief tv Video FrameRate Change CB
 *
 *
 * @pre TvInit() should be called before calling this API
 */
typedef void (*tvVideoFrameRateChangeCB)(tvVideoFrameRate_t frameRate,void *userData);
typedef struct
{
    void *userdata;
    tvVideoFrameRateChangeCB cb;
}tvVideoFrameRateCallbackData;

/**
 * @brief Registers the Video framerate change callback
 *
 * This function registers a callback for playback content video frame rate change event.
 * Once registered, the callback function will be called by the TV Settings HAL implementation
 * whenever the system detects frame rate change for the primary video currently played.
 *
 * @param[in] cbData                - Callback function. Please refer ::tvVideoFrameRateCallbackData
 *
 *
 * @pre TvInit() should be called before calling this API
 */
void RegisterVideoFrameRateChangeCB(tvVideoFrameRateCallbackData& cbData);
/**
 * @brief Gets the supported DV modes and their count
 *
 * This function returns the supported Dolby Vision modes and their count
 *
 * @param[out] dvModes - hdr 10 modes
 * @param[in] count - count
 *
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
tvError_t GetTVSupportedDVModes(pic_modes_t *dvModes[],unsigned short *count);

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
tvError_t SetTVDolbyVisionMode(const char * dolbyMode);
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
tvError_t GetTVDolbyVisionMode(char *dolbyMode);
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
tvError_t SetTVHLGMode(const char * hlgMode);
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
tvError_t SetTVHDR10Mode(const char * hdr10Mode);
/**
 * @brief Gets the current current HLG mode
 *
 * This function gets the current HLG mode value for the primary video source selected,
 * primary video format played and picture mode selected.
 *
 * @param[out] hlgMode - HLG mode to get
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
tvError_t GetTVHLGMode(char *hlgMode);
/**
 * @brief Gets the current current HDR10 mode
 *
 * This function gets the current HDR10 mode value for the primary video source selected,
 * primary video format played and picture mode selected.
 *
 * @param[out] hdr10Mode - HDR mode to get
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
tvError_t GetTVHDR10Mode(char *hdr10Mode);
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
tvError_t GetTVSupportedHLGModes(pic_modes_t *dvModes[],unsigned short *count);
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
tvError_t GetTVSupportedHDR10Modes(pic_modes_t *dvModes[],unsigned short *count);

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
 * @param[in] sourceId             - SourceId value.
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
tvError_t SetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int rgain,int sourceId, int saveOnly);
/**
 * @brief Gets the current rgain value.
 *
 * This function gets the current rgain value for a specific color temperature and source offset.
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] rgain               - Rgain Value. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value.
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
tvError_t GetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int* rgain,int sourceId);
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
 * @param[in] sourceId             - SourceId value.
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
tvError_t SetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int ggain,int sourceId, int saveOnly);
/**
 * @brief Gets the current ggain value for a specfic color temperature and source
 *
 * This function gets the ggain value for a specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] ggain               - Ggain Value. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value.
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
tvError_t GetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int* ggain,int sourceId);
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
 * @param[in] sourceId             - SourceId value.
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
tvError_t SetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int bgain,int sourceId, int saveOnly);
/**
 * @brief Gets the current bgain value for a specfic color temperature and source
 *
 * This function gets the bgain value for a specfic color temperature and source
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] bgain               - Bgain Value. Valid range is (0 - 2047)
 * @param[in] sourceId             - SourceId value.
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
tvError_t GetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int* bgain,int sourceId);
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
 * @param[in] sourceId             - SourceId value.
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
tvError_t SetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int rpostoffset,int sourceId, int saveOnly);
/**
 * @brief Gets the current rpostoffset value
 *
 * This function gets the current rpostoffset value for a specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] rpostoffset         - Rpostoffset Value. Valid range is (-1024 to +1023)
 * @param[in] sourceId             - SourceId value.
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int* rpostoffset,int sourceId);
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
 * @param[in] sourceId             - SourceId value.
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
tvError_t SetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int gpostoffset,int sourceId, int saveOnly);
/**
 * @brief Gets the current gpostoffset value for a specfic color temperature and source
 *
 * This function gets the gpostoffset value for a specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] gpostoffset         - Gpostoffset Value. Valid range is (-1024 to +1023)
 * @param[in] sourceId             - SourceId value.
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
tvError_t GetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int* gpostoffset,int sourceId);
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
 * @param[in] sourceId             - SourceId value.
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
tvError_t SetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int bpostoffset,int sourceId, int saveOnly);
/**
 * @brief Gets the current bpostoffset value for a specfic color temperature and source
 *
 * This function gets the bpostoffset value for a specfic color temperature and source
 *
 * @param[in] colorTemp            - Color temperature value. Valid value will be a member of ::tvColorTemp_t
 * @param[out] bpostoffset         - Bpostoffset Value. Valid range is (-1024 to +1023)
 * @param[in] sourceId             - SourceId value.
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - Input parameter is invalid
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int* bpostoffset,int sourceId);
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
tvError_t setWBctrl(char *inputSrc, char *colorTemp,char *color, char *ctrl, int value);
/**
 * @brief Gets the current white balance control.
 *
 * This function gets the white balance for a specific source, color, color temperature and control.
 *
 * @param[in] inputSrc -  Input source
 * @param[in] colortemp - color temperature value
 * @param[in] color - color values (red, blue or green)
 * @param[in] ctrl - control values (gain or offset)
 * @param[in] value - pointer to store value which will be returned by driver
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
tvError_t getWBctrl(char *inputSrc, char *colortemp, char *color, char *ctrl, int *value);
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
tvError_t getWbInfo(getWBInfo_t* params, std::vector<std::string> &selector, std::vector<std::string> &colorTmp, std::vector<std::string> &input);
/**
 * @brief Enable/disable WB mode.
 *
 * This function enables or disables white balance mode.
 *
 * @param[in] value - value
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
tvError_t enableWBmode(bool value);
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
 * @brief Sets current component saturation
 *
 * This function updates the component saturation value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @pre TvInit() and SetCMSState() should be called before calling this API
 *
 * @see SetCMSState()
 */
tvError_t SetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int saturation);
/**
 * @brief Gets current component saturation
 *
 * This function returns the current component saturation for the specific color, for the primary video source selected,
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
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int *saturation);
/**
 * @brief Sets current component hue
 *
 * This function updates the component hue value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @pre TvInit() and SetCMSState() should be called before calling this API
 *
 * @see SetCMSState()
 */
tvError_t SetCurrentComponentHue(tvDataComponentColor_t blHueColor, int hue);
/**
 * @brief Gets current component hue
 *
 * This function returns the current component hue for the specific color, for the primary video source selected,
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
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentComponentHue(tvDataComponentColor_t blHueColor, int *hue);
/**
 * @brief Sets the current component luma value
 *
 * This function updates the component luma value to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected
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
 * @pre TvInit() and SetCMSState() should be called before calling this API
 *
 * @see SetCMSState()
 */
tvError_t SetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int Luma);
/**
 * @brief Gets the current component luma
 *
 * This function returns the current component luma for the specific color, for the primary video source selected,
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
 * @pre TvInit() should be called before calling this API
 */
tvError_t GetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int *Luma);
/**
 * @brief Gets supported backlight dimming modes of the system.  To be deprecated soon.
 *
 * This function returns all the supported backlight dimming modes.
 *
 * @param[out] dimmingModes    - array of dimming modes names. Valid values are "fixed", "local" and "global"
 * @param[out] count            - Count of supported dimming modes. Min should be 1
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
tvError_t GetTVSupportedDimmingModes(char **dimmingModes,unsigned short *count);
/**
 * @brief Sets the backlight dimming mode.
 *
 * This function updates the new dimming mode to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected.
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
 * @brief Get TV Backlight Global Factor
 *
 * This function get the current applied Backlight Global Factor
 *
 * @param[out] value  - value
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
tvError_t GetTVBacklightGlobalFactor(int * value);
/**
 * @brief Set TV Backlight Global Factor
 *
 * This function controls the backlight through backlight global factor.
 *
 * @param[in] value  - value
 * @param[in] rangeMidPointValue - Range Mid point value
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
tvError_t SetTVBacklightGlobalFactor(int value, int rangeMidPointValue);
/**
 * @brief Get TV Picture Mode Index
 *
 * This function returns the current selected picture mode index value.
 *
 * @param[in] pictureMode - Picture Mode
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
tvPictureMode_t GetTVPictureModeIndex(const char * pictureMode);
/**
 * @brief Get Current Content Format
 *
 * This function gets the video format value of the current primary video played on TV
 *
 * @return tvVideoHDRFormat_t
 *
 * @retval HDR format
 *
 * @pre TvInit() should be called before calling this API
 */
tvVideoHDRFormat_t GetCurrentContentFormat(void);
/**
 * @brief Get Supported Content Formats
 *
 * This function returns all the supported content formats.
 *
 * @param[out] contentFormats - content formats
 * @param[out] numberOfFormats - number Of Formats
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
tvError_t GetSupportedContentFormats(unsigned int * contentFormats,unsigned short *numberOfFormats);
/**
 * @brief Reset Brightness
 *
 * This function reset Brightness value to default value for all formats (or) current format.
 *
 * @param[in] defaultValue - Default values
 * @param[in] resetForAllFormats - reset for all formats
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetBrightness(int defaultValue,bool resetForAllFormats);
/**
 * @brief Reset Contrast
 *
 * This function reset Contrast value to default value for all formats (or) current format.
 *
 * @param[in] defaultValue - Default values
 * @param[in] resetForAllFormats - reset for all formats
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetContrast(int defaultValue,bool resetForAllFormats);
/**
 * @brief Reset Sharpness
 *
 * This function reset Sharpness value to default value for all formats (or) current format.
 *
 * @param[in] defaultValue - Default values
 * @param[in] resetForAllFormats - reset for all formats
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetSharpness(int defaultValue,bool resetForAllFormats);
/**
 * @brief Reset Saturation
 *
 * This function reset Saturation value to default value for all formats (or) current format.
 *
 * @param[in] defaultValue - Default values
 * @param[in] resetForAllFormats - reset for all formats
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetSaturation(int defaultValue,bool resetForAllFormats);
/**
 * @brief Reset Hue
 *
 * This function reset Hue value to default value for all formats (or) current format.
 *
 * @param[in] defaultValue - Default values
 * @param[in] resetForAllFormats - reset for all formats
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetHue(int defaultValue,bool resetForAllFormats);
/**
 * @brief Reset Backlight
 *
 * This function reset Backlight value to default value for all formats (or) current format.
 *
 * @param[in] defaultValue - Default values
 * @param[in] resetForAllFormats - reset for all formats
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetBacklight(int defaultValue,bool resetForAllFormats);
/**
 * @brief Reset Color Tempearture
 *
 * This function reset Color Tempearture value to default value for all formats (or) current format.
 *
 * @param[in] defaultValue - Default values
 * @param[in] resetForAllFormats - reset for all formats
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetColorTemperature(int defaultValue,bool resetForAllFormats);
/**
 * @brief Reset Component Saturation
 *
 * This function reset Component Saturation value to default value for all formats (or) current format.
 *
 * @param[in] color - saturation color
 * @param[in] defaultValue - Default values
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetComponentSaturation(int color,int defaultValue);
/**
 * @brief Reset Component Luma
 *
 * This function reset Component luma value to default value for all formats (or) current format.
 *
 * @param[in] color - Luma color
 * @param[in] defaultValue - Default values
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetComponentLuma(int color,int defaultValue);
/**
 * @brief Reset Component hue
 *
 * This function reset Component Hue value to default value for all formats (or) current format.
 * 
 * @param[in] color - Hue color
 * @param[in] defaultValue - default value
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t ResetComponentHue(int color,int defaultValue);
/**
 * @brief Check if current format is SDR.
 *
 * This function checks whether the current content format is SDR or not.
 *
 * @return bool
 *
 * @retval True or False
 *
 * @pre TvInit() should be called before calling this API
 */
bool isCurrentHDRTypeIsSDR(void);
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
int GetPanelID(char* panelid);
/**
 * @brief Get the default panel ID
 *
 * This function return the default panelid.
 *
 * @param[out] panelID - Panel ID
 *
 *
 * @pre TvInit() should be called before calling this API
 */
void GetDefaultPanelID(char *panelID);
/**
 * @brief Saves the color temperature value
 *
 * This function saves the color temperature value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved color temperature value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current color temperature value applied in PQ module.
 *
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr format type value.
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
tvError_t SaveColorTemperature(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Saves the backlight value.
 *
 * This function saves the backlight value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved backlight value should be applied automatically whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current backlight value in backlight HW.
 *
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr format type value.
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
tvError_t SaveBacklight(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Saves the contrast value
 *
 * This function saves the contrast value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved contrast value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current contrast value applied in PQ module.
 *
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr format type value.
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
tvError_t SaveContrast(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Saves the saturation value
 *
 * This function saves the sharpness value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved saturation value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current saturation value applied in PQ module.
 *
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr format type value.
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
tvError_t SaveSaturation(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Saves the sharpness value
 *
 * This function saves the sharpness value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved sharpness value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current sharpness value applied in PQ module.
 *
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr format type value.
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
tvError_t SaveSharpness(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Saves the brightness value
 *
 * This function saves the brightness value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved brightness value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current brightness value applied in PQ module.
 *
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr format type value.
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
 */
tvError_t SaveBrightness(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Saves the hue value
 *
 * This function saves the hue  value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved hue value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current hue value applied in PQ module.
 *
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr type value.
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
tvError_t SaveHue(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Saves the DynamicBacklight mode
 *
 * This function saves the backlight dimming mode(DynamicBacklight) in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved backlight dimming mode should be applied automatically whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current backlight dimming mode.
 * If peak brightness capablity of the panel changes as a result of dimming mode change in future reload the edid accordingly
 * to update VSVDB string if current video format is handled via Dolby Vision core.
 *
 * @param[in] sourceInput            - Source input value.
 * @param[in] pq_mode                - Picture mode index.
 * @param[in] hdr_type               - hdr type value.
 * @param[in] value                  - Value of the DynamicBacklight(tvDimmingMode_t)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveDynamicBacklight(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Saves the DisplayMode value
 *
 * This function saves the aspect ratio(DisplayMode) value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved aspect ratio value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in current aspect ratio value applied in PQ module.
 *
 * @param[in] sourceInput            - Source input value.
 * @param[in] pq_mode                - Picture mode index.
 * @param[in] hdr_type               - hdr type value.
 * @param[in] value                  - Value of AspectRatio(tvDisplayMode_t)
 *
 * @return tvError_t
 *
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_GENERAL          - Underlying failures - SoC, memory, etc
 *
 * @pre TvInit() should be called before calling this API
 */
tvError_t SaveDisplayMode(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Save the CMS value
 *
 * This function saves the CMS value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved hue value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played, specified primary video source is selected
 * and the CMS state is enabled for that combination.
 * There will be no change in current CMS value applied in PQ module.
 *
 * @param[in] sourceInput            - Source input value.
 * @param[in] pq_mode                - Picture mode index.
 * @param[in] hdr_type               - hdr type value.
 * @param[in] tunnel_type            - tunnel type value.
 * @param[in] color_type             - Color type value.
 * @param[in] value                  - Value of the CMS to be set.
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
tvError_t SaveCMS(int sourceInput, int pq_mode,int hdr_type,int tunnel_type,int color_type,int value);
/**
 * @brief Saves the dolby mode value
 *
 * This function saves the dolby mode value in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved dolby mode value should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format(if handled via Dolby core) is played
 * and specified primary video source is selected. There will be no change in current dolby mode value in Dolby Vision core.
 *
 * @param[in] sourceInput            - Source input value.
 * @param[in] pq_mode                - Picture mode index.
 * @param[in] hdr_type               - hdr type value.
 * @param[in] value                  - Value of the CMS to be set.
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
tvError_t SaveDolbyMode(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief GetNumberOfModesupported
 *
 * This function returns the number of supported picture modes.
 *
 * @return int
 *
 * @retval numberModesSupported
 *
 * @pre TvInit() should be called before calling this API
 */
int GetNumberOfModesupported(void);
/**
 * @brief Get current PQ Mode index.
 *
 * This function returns the current PQ index value.
 *
 * @return int
 *
 * @retval picModeValue
 *
 * @pre TvInit() should be called before calling this API
 */
int GetCurrentPQIndex(void);
/**
 * @brief Get All Supported PicMode Index
 *
 * This function gets all the supported picture mode index.
 *
 * @param[out] pic_mode_index
 *
 * @pre TvInit() should be called before calling this API
 */
void GetAllSupportedPicModeIndex(int pic_mode_index[]);
/**
 * @brief Gets the current CMS default value. To be deprecated soon.
 *
 * This function returns the default CMS value
 *
 * @param[out] color_tunel_type      - color_tunel_type.
 *
 * @return int
 *
 * @retval 15                       - Luma default value
 * @retval 50                       - Hue or saturation default value
 * @retval -1                       - Input parameter is invalid
 *
 * @pre tvInit() should be called before calling this API
 */
int GetCMSDefault(tvCMS_tunel_t color_tunel_type);
/**
 * @brief Get Dolby Mode Index
 *
 * This function returns the dolby mode index.
 *
 * @param[in] dolbyMode
 *
 * @return int
 *
 * @retval Dolbymode value
 *
 * @pre TvInit() should be called before calling this API
 */
int GetDolbyModeIndex(const char * dolbyMode);
/**
 * @brief Returns ::tvhdr_type_t enum for given ::tvVideoHDRFormat_t enum. To be deprecated soon.
 *
 * This function converts the video format to HDR format.
 *
 * @param[in] videoFormat            - Video format. Valid values can be member of ::tvVideoHDRFormat_t
 *
 * @return int - Valid values can be member of ::tvhdr_type_t
 *
 * @pre tvInit() should be called before calling this API
 */
int ConvertVideoFormatToHDRFormat(tvVideoHDRFormat_t videoFormat);
/**
 * @brief Convert TV color to vendor color.
 *
 * This function converts the TV color to Vendor color value
 *
 * @param[in] blComponentColor - blComponentColor
 *
 * @return int
 *
 * @retval component color
 *
 * @pre TvInit() should be called before calling this API
 */
int ConvertTVColorToVendorColor(tvDataComponentColor_t blComponentColor);
/**
 * @brief Convert HDR to content format.
 *
 * This function converts the vendor HDR format to tv format value.
 *
 * @param[in] hdrFormat - hdrformat
 *
 * @return int
 *
 * @retval hdr format
 *
 * @pre TvInit() should be called before calling this API
 */
int ConvertHDRFormatToContentFormat(tvhdr_type_t hdrFormat);
/**
 * @brief Get Custom mode index.
 *
 * This function return the custom pqmode index
 *
 * @return int
 *
 * @retval pic mode values
 *
 * @pre TvInit() should be called before calling this API
 */
int GetCustomPQModeIndex(void);

/**
 * @brief Sets and save's the CMS state
 *
 * This function enable or disable the CMS state. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved CMS state value should be applied automatically whenever the  current picture mode, current primary video format
 *
 * @param[in] tunelType             - Tunnel Type
 * @param[in] colorType             - Color Type
 * @param[in] componentState        - Component State
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
tvError_t SetCMSState(tvCMS_tunel_t tunelType,tvcomponent_color_type_t colorType,tvcomponent_state_t componentState);
/**
 * @brief Check the given WB values are default or not
 *
 * This function checks if the white balance parameters are equal to default value.
 *
 * @param[in] wbvalue - wb value
 *
 * @return bool
 *
 * @retval True or false
 *
 * @pre TvInit() should be called before calling this API
 */
bool isWBUserDfault(tvDataColor_t wbvalue);
/**
 * @brief Get WB RGB type.
 *
 * This function gets the white balance RGB type for specific color and control value.
 *
 * @param[in] color - color
 * @param[in] ctrl - ctrl
 *
 * @return int
 *
 * @retval rgb_type
 *
 * @pre TvInit() should be called before calling this API
 */
int GetWBRgbType(const char *color, const char * ctrl);
/**
 * @brief Get WB values on init.
 *
 * This function gets the user white balance value on init.
 *
 * @return tvDataColor_t
 *
 * @retval wb values
 *
 * @pre TvInit() should be called before calling this API
 */
tvDataColor_t GetUSerWBValueOnInit(void);
/**
 * @brief Check WB values are equal.
 *
 * This function checks if two white balance values are same.
 *
 * @param[in] wbvalueThis - value this
 * @param[in] wbvalueThat - value that
 *
 * @return bool
 *
 * @retval True or False
 *
 * @pre TvInit() should be called before calling this API
 */
bool areEqual(tvDataColor_t wbvalueThis,tvDataColor_t wbvalueThat);
/**
 * @brief Set Color Temperature User
 *
 * This function update RGB(WhiteBalance) values for user colortemperature
 *
 * @param[in] rgbType - rgb type
 * @param[in] value - value
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
tvError_t SetColorTemperatureUser(int rgbType, int value);
/**
 * @brief Saves the color temperature to driver cache. To be deprecated soon.
 *
 * This function saves the color temperature for user to driver cache file
 *
 * @param[in] rgbType               - RGB type. Valid value will be a member of ::tvRGBType_t
 * @param[in] value                 - Color temperature value to be set. Valid range : for gain (0 to 2047) , for offset (-1024 to 1024)
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
tvError_t SaveColorTemperatureUser(int rgbType, int value);
/**
 * @brief Set backlight info.
 *
 * This function updates the backlight curve details to HAL
 *
 * @param[in] backlightDefaults - backlightDefaults to set
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
tvError_t SetBacklightInfo(tvBacklightInfo_t *backlightDefaults);
/**
 * @brief Get Driver BL value for current format.
 *
 * This function returns the driver equivalent backlight for current backlight value.
 *
 * @param[in] backlight - Backlight
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
int GetDriverEquivalentBLForCurrentFmt(int backlight);
/**
 * @brief Get HLG mode Index.
 *
 * This function returns HLG mode index.
 *
 * @param[in] hlgMode - hlg mode
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
int GetHLGModeIndex(const char * hlgMode);
/**
 * @brief Get HDR10 mode index.
 *
 * This function returns HDR10 mode index.
 *
 * @param[in] hdr10Mode  - hdr10mode
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
int GetHDR10ModeIndex(const char * hdr10Mode);

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
tvError_t ReadAllModeConfigfile(const char *file, char *cpybuffer, const char *searchstring);
/**
 * @brief Parse buffer and return string values & total count
 *
 * This function parses the buffer returned through ReadAllModeConfigfile() and returns the string value and their count.
 *
 * @param[in] buffer - Buffer to split
 * @param[in] availableModes - avilable modes
 * @param[out] totalcount - total count
 *
 *
 * @pre TvInit() should be called before calling this API
 */
void splitstringsfrombuffer(char *buffer, char *availableModes, unsigned short *totalcount);
/**
 * @brief Parse buffer and return string values,index & total count
 *
 * This function parses the buffer returned through ReadAllModeConfigfile() and returns the string value,index and their count.
 *
 * @param[in] buffer - Buffer to split
 * @param[in] availableModes - avilable modes
 * @param[out] totalcount - total count
 *
 * @pre TvInit() should be called before calling this API
 */
void splitstringsandvaluefrombuffer(char *buffer, pic_modes_t *availableModes[], unsigned short *totalcount);
/**
 * @brief Enable or disable gamma mode.
 *
 * This function enables or disables the gamma mode.
 *
 * @param[in] mode - Mode
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
tvError_t SetGammaMode(int mode);

/**
 * @brief Sets the local dimming level
 *
 * This function updates the new local dimming level to hardware. The change is applied for current primary video source selected,
 * video format played and picture mode selected and if successful will be saved in override picture profile database.
 * The saved local dimming level value should be applied automatically whenever the  current picture mode, current primary video format
 * If peak brightness capablity of the panel changes as a result of local dimming level change reload the edid accordingly
 * to update VSVDB string if current video format is handled via Dolby Vision core.
 *
 * @param[in] localDimmingLevel                -  Dimming level to set.
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
tvError_t SetLocalDimmingLevel(int localDimmingLevel);
/**
 * @brief Gets the current dimming level
 *
 * This function gets the current local dimming level for the primary video source selected,
 * primary video format played and picture mode selected.
 *
 * @param[out] localDimmingLevel               - Current Dimming level returned.
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
tvError_t GetLocalDimmingLevel(int *localDimmingLevel);
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
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr type value.
 * @param[in] value                 - Value of the local dimming level to be set.
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
tvError_t SaveLocalDimmingLevel(int sourceInput, int pq_mode,int hdr_type,int value);
/**
 * @brief Switch EDID
 *
 * This Function updates the EDID for given picture mode
 *
 * @param[in] pqmode - picture quality mode
 *
 * @pre TvInit() should be called before calling this API
 */
void SwitchEDID(int pqmode);
/**
 * @brief Set the EDID and dimming level
 *
 * This function Update  EDID and set dimming level for current Picture mode
 *
 * @param[in] dimmingLevel - Dimming level
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
tvError_t UpdateEDIDAndSetDimmingLevel(int dimmingLevel);
/**
 * @brief Get LDIM and EDID level
 *
 * This function gets the LDIM and EDID level for given video format and dimmingMode
 *
 * @param[in]  dimmingMode - Dimming mode
 * @param[in]  format      - Format
 * @param[out] dimmingLevel - Dimming Level
 * @param[out] edidLevel    - EDID level
 *
 *
 * @pre TvInit() should be called before calling this API
 */
void GetLDIMAndEDIDLevel(int dimmingMode,int format,int *dimmingLevel, int *edidLevel);

/**
 * @brief Saves the low latency index
 *
 * This function saves the low latency index in picture profile database for the specific picture mode, primary video format type
 * and primary video source. The saved low latency index should be applied automatically by whenever the
 * specified picture mode is selected, specified primary video format is played and specified primary video source is selected.
 * There will be no change in low latency index value applied in PQ module.
 *
 * @param[in] sourceInput           - Source input value.
 * @param[in] pq_mode               - Picture mode index.
 * @param[in] hdr_type              - hdr value.
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
tvError_t SaveLowLatencyState( int sourceInput, int pq_mode,int hdr_type,int value );
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
 * @brief Gets the current gamma calibrated values from gamma HW for current selected colour temperature.
 *
 * This function gets the current gamma calibrated values(0 - 65535) for the primary colors for a current color temperature.
 *
 * @param[in] colortemp       - Color temperature.
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
tvError_t GetGammaTable(int colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);
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
tvError_t SaveGammaTable(int colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);

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
#ifdef __cplusplus
}
#endif

#endif // End of _TV_SETTINGS_H

/** @} */ // End of TV_Settings_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK