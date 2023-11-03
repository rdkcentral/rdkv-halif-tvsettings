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
* @defgroup TV_Settings_H TV Settings Header
* @{
**/

#ifndef _TV_SETTINGS_H
#define _TV_SETTINGS_H

#include <stdbool.h>
#include <string>
#include <inttypes.h>
#include "tvError.h"
#include "tvTypes.h"

#include <vector> 

#ifdef __cplusplus 
extern "C"
{
#endif

#define MAX_STRING_SIZE (15)                //!< Defines the maximum size of string
#define CONTROL_COUNT (2)                   //!< Defines the maximum WB control count

#define PIC_MODES_SUPPORTED_MAX   (15)      //!< Defines the maximum pic modes supported
#define PIC_MODE_NAME_MAX (25)              //!< Defines the maximum picture mode name length
#define DIMMING_MODE_NAME_SIZE    (25)      //!< Defines the maximum mode name size
#define DIMMING_MODE_MAX          (10)      //!< Defines the maximum dimming mode

#define GAIN_MIN         (0)                //!< Defines the minimum gain value
#define GAIN_MAX         (2047)             //!< Defines the maximum gain value
#define OFFSET_MIN       (-1024)            //!< Defines the minimum offset value
#define OFFSET_MAX       (1024)             //!< Defines the maximum offset value
#define BACKLIGHT_CURVE_MAX_INDEX     (101) //!< Defines the maximum backlight curve array length
#define EXPECTED_FILE_SIZE (512)             //!< Defines the maximum file size
#define GENERIC_MODE_CONFIG_FILE  "/etc/tv/allmodes.conf"    //!< Defines the config file

/**
 * @brief Callback for tvVideoFormatChangeCB
 *
 * This callback is triggered when a video format change is encountered.
 *
 * @param[in] format   			- Type of content format
 * @param[in] userData 			- Data of the content
 *
 */
typedef void (*tvVideoFormatChangeCB)(tvVideoHDRFormat_t format,void *userData);

/**
 * @brief Callback for tvVideoContentChangeCB
 *
 * This callback is triggered when a video content change is encountered.
 *
 * @param[in] mode                      - Types of FMM mode
 * @param[in] userData                  - Data of the content
 *
 */
typedef void (*tvVideoContentChangeCB)(tvContentType_t mode,void *userData);

/**
 * @brief Callback for tvVideoResolutionChangeCB.
 *
 * This callback is triggered when a video resolution change is encountered.
 *
 * @param[in] resolutionStruct    - Resolution parameter
 * @param[in] userData            - Data of the content
 *
 */
typedef void (*tvVideoResolutionChangeCB)(tvResolutionParam_t resolutionStruct,void *userData);

/**
 * @brief Callback for tvVideoFrameRateChangeCB.
 *
 * This callback is triggered when a video framerate change is encountered.
 *
 * @param[in] frameRate            - framerate parameter
 * @param[in] userData             - Data of the content
 *
 */
typedef void (*tvVideoFrameRateChangeCB)(tvVideoFrameRate_t frameRate,void *userData);

/** 
 * @brief Structure for the pic modes and value.@n
   The value contains the index and parameter is applicable only for get/set of picmodes.
 */
typedef struct 
{
    char name[PIC_MODE_NAME_MAX];           //!< Pic modes name
    short int value;                        //!< Pic mode value
}pic_modes_t;

/** 
 * @brief Structure for video format call back data. 
 */
typedef struct
{ 
    void *userdata;                         //!< User data received from call back
    tvVideoFormatChangeCB cb;               //!< Callback function pointer
}tvVideoFormatCallbackData;

/**
 * @brief Structure for FMM content call back data.
 */
typedef struct
{
    void *userdata;                         //!< User data received from call back
    tvVideoContentChangeCB cb;              //!< Callback function pointer
}tvVideoContentCallbackData;

/** 
 * @brief Structure for video resolution callback data. 
 */
typedef struct
{
    void *userdata;                         //!< Data of content
    tvVideoResolutionChangeCB cb;           //!< Callback function pointer
}tvVideoResolutionCallbackData;

/** 
 * @brief Structure for video framerate callback data. 
 */
typedef struct
{
    void *userdata;                         //!< Data of content
    tvVideoFrameRateChangeCB cb;            //!< Callback function pointer
}tvVideoFrameRateCallbackData;

/** 
 * @brief Structure for the white balanace Information. 
 */
/* Structure for the White Balanace Info. */
typedef struct 
{
    char wbControls[CONTROL_COUNT][MAX_STRING_SIZE]; //!< White Balance Controls
    char wbGain[CONTROL_COUNT][MAX_STRING_SIZE];     //!< White Balance Gain value
    char wbOffset[CONTROL_COUNT][MAX_STRING_SIZE];   //!< White Balance Offset value
}getWBInfo_t;

/* An enumeration defining different mfr color temperature */
typedef enum
{
    mfrColorTemp_STANDARD = 0,             //!< Temperature standard
    mfrColorTemp_COLD,                     //!< Temperature cold
    mfrColorTemp_WARM,                     //!< Temperature warm
    mfrColorTemp_USER,                     //!< Temperature user
    mfrColorTemp_MAX                       //!< End of enum
}fp_mfrColorTemp_t;

/* An enumeration defining different source offset */
typedef enum input_source_offset_e
{
    HDMI_OFFSET_NEW = 0,                  //!< HDMI offset
    TV_OFFSET_NEW,                        //!< TV offset
    AV_OFFSET_NEW,                        //!< AV offset
    MAX_OFFSET_NEW                        //!< End of enum
} input_source_offset_t;

/**
 * @brief  Init TV Settings HAL.
 * 
 * This function is to initialize the TV Setting HAL APIs.
 *
 * @return tvError_t 
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @see tvTerm()
 *
 */
tvError_t tvInit();

/**
 * @brief Deinit TV Settings HAL.
 * 
 * This function should terminate the TV Settings HAL API's.
 * 
 * @return tvError_t 
 * @retval tvERROR_NONE              - Success
* @retval tvERROR_INVALID_STATE      - Interface is not terminated
 * 
 */
tvError_t tvTerm();

/**
 * @brief Get the TV Picture Mode.
 * 
 * This function will get the current selected tv picture mode.
 * 
 * @param[out] pictureMode         - Current picturemode ("Entertainment", "Dynamic", "Expert", "Movie", "Sports", "Graphics")
 *
 * @return tvError_t
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetTVPictureMode()
 */
tvError_t GetTVPictureMode(char *pictureMode);

/**
 * @brief Set the TV Picture Mode.
 * 
 * This function updates the picture mode.
 * 
 * @param[in] pictureMode           - Picture mode to be set ("Entertainment", "Dynamic", "Expert", "Movie", "Sports", "Graphics")
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting picture mode
 * @retval tvERROR_INVALID_PARAM    - When the set value is not valid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @pre  tvInit() should be called before calling this API.
 * @see GetTVPictureMode()
 */
tvError_t SetTVPictureMode(const char * pictureMode);

/**
 * @brief Get the backlight value.
 * 
 * This function gets the current backlight value.
 *
 * @param[out] backlight           - Current backlight value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_GENERAL         - Error while getting backlight value
 * @retval tvERROR_INVALID_PARAM   - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetBacklight()
 */
tvError_t GetBacklight(int *backlight);

/**
 * @brief Set the backlight value.
 * 
 * This function updates the new backlight value.
 *
 * @param[in] backlight            - Backlight value to be set(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_GENERAL         - Error while setting backlight value
 * @retval tvERROR_INVALID_PARAM   - When the set value is not valid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 * @see GetBacklight()
 */
tvError_t SetBacklight(int backlight);

/**
 * @brief Set the brightness value.
 * 
 * This function updates the brightness.
 *
 * @param[in] brightness             - Brightness value to be set(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_GENERAL           - Error while setting brightness
 * @retval tvERROR_INVALID_PARAM     - When the set value is not valid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetBrightness()
 */
tvError_t SetBrightness(int brightness);

/**
 * @brief Get the brightness value.
 * 
 * This function gets the current brightness.
 *
 * @param[out] brightness            - Current brightness value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetBrightness()
 */
tvError_t GetBrightness(int *brightness);

/**
 * @brief Set the contrast value.
 * 
 * This function updates the contrast value.
 *
 * @param[in] contrast               - Contrast value to be set(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_GENERAL           - Error while setting contrast 
 * @retval tvERROR_INVALID_PARAM     - When the set value is not valid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * @pre  tvInit() should be called before calling this API.
 * @see GetContrast()
 */
tvError_t SetContrast(int contrast);

/**
 * @brief Get the contrast value.
 * 
 * This function gets the current contrast value.
 *
 * @param[out] contrast               - Current contrast value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_INVALID_PARAM      - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetContrast()
 */
tvError_t GetContrast(int *contrast);

/**
 * @brief Set the sharpness value.
 * 
 * This function updates the sharpness value.
 *
 * @param[in] sharpness                - Sharpness value to be set(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                - Success
 * @retval tvERROR_GENERAL             - Error while setting sharpness
 * @retval tvERROR_INVALID_PARAM       - When the set value is not valid
 * @retval tvERROR_INVALID_STATE       - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetSharpness()
 */
tvError_t SetSharpness(int sharpness);

/**
 * @brief Get the sharpness value.
 * 
 * This function gets the current sharpness value.
 *
 * @param[out] sharpness              - Current sharpness value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE               - Success 
 * @retval tvERROR_INVALID_PARAM      - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetSharpness()
 */
tvError_t GetSharpness(int *sharpness);

/**
 * @brief Set the saturation value.
 * 
 * This function updates the saturation value.
 *
 * @param[in] saturation              - Saturation value to be set(0 - 100)
 *                                    
 * @return tvError_t                  
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_GENERAL            - Error while setting saturation
 * @retval tvERROR_INVALID_PARAM      - When the set value is not valid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetSaturation()
 */
tvError_t SetSaturation(int saturation);

/**
 * @brief Get the saturation value.
 * 
 * This function gets the current saturation value.
 *
 * @param[out] saturation              - Current saturation value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                - Success
 * @retval tvERROR_INVALID_PARAM       - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE       - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetSaturation()
 */
tvError_t GetSaturation(int *saturation);

/**
 * @brief Set the hue value.
 * 
 * This function updates the hue value.
 *
 * @param[in] hue                     - Hue value to be set(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_GENERAL            - Error while setting hue
 * @retval tvERROR_INVALID_PARAM      - When the set value is not valid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetHue()
 */
tvError_t SetHue(int hue);

/**
 * @brief Get the hue value.
 * 
 * This function gets the current hue value.
 *
 * @param[out] hue                    - Current hue value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE               - Success
 * @retval tvERROR_INVALID_PARAM      - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetHue()
 */
tvError_t GetHue(int *hue);

/**
 * @brief Set the color temperature value.
 * 
 * This function updates the color temperature value.
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_GENERAL           - Error while setting color temperature
 * @retval tvERROR_INVALID_PARAM     - When the set value is not valid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemperature()
 */
tvError_t SetColorTemperature(tvColorTemp_t colorTemp);

/**
 * @brief Get the color temperature values.
 * 
 * This function gets the current color tmperature value.
 *
 * @param[out] colorTemp             - Current color temperature(tvColorTemp_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemperature()
 */
tvError_t GetColorTemperature(tvColorTemp_t *colorTemp);

/**
 * @brief Set the aspect ratio.
 * 
 * This function updates the Aspect ratio.
 * @param[in] dispMode                - Display mode value(tvDisplayMode_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - When thread creation failure
 * @retval tvERROR_INVALID_PARAM             - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetAspectRatio()
 */
tvError_t SetAspectRatio(tvDisplayMode_t dispMode);

/**
 * @brief Get the aspect ratio.
 * 
 * This function gets the aspect ratio
 *
 * @param[out] dispMode             - Display mode value(tvDisplayMode_t)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetAspectRatio()
 */
tvError_t GetAspectRatio(tvDisplayMode_t *dispMode);

/**
 * @brief Get the supported backlight modes.
 * 
 * This function gets all supported backlight modes of TV.
 * @param[out] blModes                - Supported backlight modes(tvBacklightMode_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE               - Success
  * @retval tvERROR_INVALID_PARAM     - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE      - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetCurrentBacklightMode(),SetCurrentBacklightMode()
 */
tvError_t GetSupportedBacklightModes(int *blModes);

/**
 * @brief Get current blacklight mode.
 * 
 * This function gets the current backlight mode.
 *
 * @param[out] blMode                - Current backlight mode(tvBacklightMode_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_INVALID_PARAM     - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetSupportedBacklightModes(),SetCurrentBacklightMode()
 */
tvError_t GetCurrentBacklightMode(tvBacklightMode_t *blMode);

/**
 * @brief Set the backlight mode.
 * 
 * This function sets the backlight mode.
 *
 * @param[in] blMode                         - Backlight mode to be set(tvBacklightMode_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting backlightmode/Backlight value read from table is 0
 * @retval tvERROR_INVALID_PARAM             - When the set value is not valid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized 
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - When a baclight value is currently not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetSupportedBacklightModes(),GetCurrentBacklightMode()
 */
tvError_t SetCurrentBacklightMode(tvBacklightMode_t blMode);

/**
 * @brief Get current video format.
 * 
 * This function gets the video format value of the current content played on TV.
 *
 * @param[out] format                         - Current video format(tvVideoHDRFormat_t)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentVideoFormat(tvVideoHDRFormat_t *format);

/**
 * @brief Get the current video resolution.
 * 
 * This function gets the video resolution of the current content played on TV.
 *
 * @param[out] res                          - Video resolution value(tvResolutionParam_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                     - Success
 * @retval tvERROR_INVALID_PARAM            - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE            - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetVideoResolution(tvResolutionParam_t *res);

/**
 * @brief Get current video framerate.
 * 
 * This function gets the video frame rate of the current content played on TV.
 *
 * @param[out] format                       - Video frame rate value(tvVideoFrameRate_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                     - Success
 * @retval tvERROR_INVALID_PARAM            - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE            - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetVideoFrameRate(tvVideoFrameRate_t *format);

/**
 * @brief Set wakeup configuration.
 * 
 * This function enable/disable specific deepsleep wakeup reason.
 *
 * @param[in] src_type                     - Wakeup source type(tvWakeupSrcType_t)
 * @param[in] value                        - Enable/disable wakeup source
 * 
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Wakeup Configuration write failed
 * @retval tvERROR_INVALID_PARAM             - When the set value is not valid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
*/
tvError_t setWakeupConfig(const tvWakeupSrcType_t src_type, const bool value);

/**
 * @brief Set the RGB values.
 * 
 * This function sets the primary color level at 8bit resolution(0 - 255). This pattern goes through videopipeline.
 *
 * @param[in] r                    - Red level of input pattern
 * @param[in] g                    - Green level of input pattern
 * @param[in] b                    - Blue level of input pattern
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting RGB values
 * @retval tvERROR_INVALID_PARAM    - When the set value is not valid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetRGBPattern(int r,int g, int b) ;

/**
 * @brief Get the RGB values.
 * 
 * This function gets the current primary color level(0 - 255).
 *
 * @param[out] r                    - Red level of input pattern
 * @param[out] g                    - Green level of input pattern
 * @param[out] b                    - Blue level of input pattern
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetRGBPattern(int *r,int *g,int *b);

/**
 * @brief Set the gray pattern value.
 * This function sets the various gray pattern levels.
 *
 * @param[in] YUVValue              - Gray level of input pattern(0 - 255)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting gray pattern values
 * @retval tvERROR_INVALID_PARAM    - When the set value is not valid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetGrayPattern(int YUVValue);

/**
 * @brief Get the gray pattern value.
 * 
 * This function gets the current gray pattern level.
 *
 * @param[out] YUVValue              - Gray level of input pattern(0 - 255)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting gray pattern values
 * @retval tvERROR_INVALID_PARAM    - When the parameter is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetGrayPattern(int* YUVValue);

/**
 * @brief Set the rgain value.
 * 
 * This function sets the rgain value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[in] rgain                  - Value(0 - 2047)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Rgain(tvColorTemp_t colorTemp, int rgain);

/**
 * @brief Get the rgain value.
 * 
 * This function gets the rgain value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[out] rgain                 - Value(0 - 2047)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Rgain(tvColorTemp_t colorTemp, int* rgain);

/**
 * @brief Set the ggain value.
 * 
 * This function sets the ggain value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[in] ggain                  - Value(0 - 2047)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Ggain(tvColorTemp_t colorTemp, int ggain);

/**
 * @brief Get the ggain value.
 * 
 * This function gets the ggain value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[out] ggain                 - Value(0 - 2047)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Ggain(tvColorTemp_t colorTemp, int* ggain);

/**
 * @brief Set the bgain value.
 * 
 * This function sets the bgain value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[in] bgain                  - Value(0 - 2047)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Bgain(tvColorTemp_t colorTemp, int bgain);

/**
 * @brief Get the bgain value.
 * 
 * This function gets the bgain value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[out] bgain                 - Value(0 - 2047)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Bgain(tvColorTemp_t colorTemp, int* bgain);

/**
 * @brief Set the rpostoffset value.
 * 
 * This function sets the rpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[in] rpostoffset            - Value(-1024 - 1024)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_R_post_offset(tvColorTemp_t colorTemp, int rpostoffset);

/**
 * @brief Get the rpostoffset value.
 * 
 * This function gets the rpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[out] rpostoffset           - Value(-1024 - 1024)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_R_post_offset(tvColorTemp_t colorTemp, int* rpostoffset);

/**
 * @brief Set the gpostoffset value.
 * 
 * This function sets the gpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[in] gpostoffset            - Value(-1024 - 1024)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_G_post_offset(tvColorTemp_t colorTemp, int gpostoffset);

/**
 * @brief Get the gpostoffset value.
 * 
 * This function gets the gpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[out] gpostoffset           - Value(-1024 - 1024)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_G_post_offset(tvColorTemp_t colorTemp, int* gpostoffset);

/**
 * @brief Set the bpostoffset value.
 * 
 * This function sets the bpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[in] bpostoffset            - Value(-1024 - 1024)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_B_post_offset(tvColorTemp_t colorTemp, int bpostoffset);

/**
 * @brief Get the bpostoffset value.
 * 
 * This function gets the bpostoffset value for specfic color temperature.
 *
 * @param[in] colorTemp              - Color temperature value to be set(tvColorTemp_t)
 * @param[out] bpostoffset           - Value(-1024 - 1024)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_B_post_offset(tvColorTemp_t colorTemp, int* bpostoffset);

/**
 * @brief Set the rgain value for the source.
 * 
 * This function sets the rgain value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[in] rgain                - Value(0 - 2047)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * @param[in] saveOnly             - save(0 or 1)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int rgain, int sourceId, int saveOnly);

/**
 * @brief Get the rgain value for the source.
 * 
 * This function gets the rgain value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[out] rgain               - Value(0 - 2047)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int* rgain,int sourceId);

/**
 * @brief Set the ggain value for the source.
 * 
 * This function sets the ggain value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[in] ggain                - Value(0 - 2047)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * @param[in] saveOnly             - save(0 or 1)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int ggain,int sourceId, int saveOnly);

/**
 * @brief Get the ggain value for the source.
 * 
 * This function gets the ggain value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[out] ggain               - Value(0 - 2047)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int* ggain,int sourceId);

/**
 * @brief Set the bgain value for the source.
 * 
 * This function sets the bgain value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[in] bgain                - Value(0 - 2047)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * @param[in] saveOnly             - save(0 or 1)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int bgain,int sourceId, int saveOnly);
/**
 * @brief Get the bgain value for the source.
 * 
 * This function gets the bgain value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[out] bgain               - Value(0 - 2047)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int* bgain,int sourceId);

/**
 * @brief Set the rpostoffset value for the source.
 * 
 * This function sets the rpostoffset value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[in] rpostoffset          - Value(-1024 - 1024)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * @param[in] saveOnly             - save(0 or 1)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int rpostoffset,int sourceId, int saveOnly);

/**
 * @brief Get the rpostoffset value for the source.
 * 
 * This function gets the rpostoffset value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[out] rpostoffset         - Value(-1024 - 1024)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int* rpostoffset,int sourceId);

/**
 * @brief Set the gpostoffset value for the source.
 * 
 * This function sets the gpostoffset value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[in] gpostoffset          - Value(-1024 - 1024)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * @param[in] saveOnly             - save(0 or 1)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int gpostoffset,int sourceId, int saveOnly);

/**
 * @brief Get the gpostoffset value for the source.
 * 
 * This function gets the gpostoffset value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[out] gpostoffset         - Value(-1024 - 1024)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int* gpostoffset,int sourceId);

/**
 * @brief Set the bpostoffset value for the source.
 * 
 * This function sets the bpostoffset value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[in] bpostoffset          - Value(-1024 - 1024)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * @param[in] saveOnly             - save(0 or 1)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the value
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int bpostoffset,int sourceId, int saveOnly);

/**
 * @brief Get the bpostoffset value for the source.
 * 
 * This function gets the bpostoffset value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature value to be set(tvColorTemp_t)
 * @param[out] bpostoffset         - Value(-1024 - 1024)
 * @param[in] sourceId             - SourceId value to be set (0 - 2)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int* bpostoffset,int sourceId);

/**
 * @brief Get supported picture modes.tvResolutionParam_t
 * 
 * This function get the array of picture modes supported.
 *
 * @param[out] pictureModes               - List of available picture modes("Entertainment", "Dynamic", "Expert", "Movie", "Sports", "Graphics")
 * @param[out] count                      - Number of Supported picture modes 
 *
 * @return tvError_t
 * @retval tvERROR_NONE                   - Success
 * @retval tvERROR_GENERAL                - When the picture modes count is 0
 * @retval tvERROR_INVALID_PARAM          - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE          - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedPictureModes(pic_modes_t *pictureModes[],unsigned short *count);

/**
 * @brief Register video format change callback.
 * 
 * This function register a callback for playback content video format change.
 *
 * @param[in] cbData                - Callback data
 * 
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t RegisterVideoFormatChangeCB(tvVideoFormatCallbackData& cbData);

/**
 * @brief Register VideoContent FMM change callback.
 *
 * This function register a callback for playback FMM mode change.
 *
 * @param[in] cbData                - Callback data
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t RegisterVideoContentChangeCB(tvVideoContentCallbackData &cbData);

/**
 * @brief Register Video resolution change callback.
 * 
 * This function register a callback for playback content video resolution change.
 *
 * @param[in] cbData                - Callback data
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t RegisterVideoResolutionChangeCB(tvVideoResolutionCallbackData& cbData);

/**
 * @brief Register Video resolution change callback.
 * 
 * This function register a callback for playback content video frame rate change.
 *
 * @param[in] cbData                - Callback function
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t RegisterVideoFrameRateChangeCB(tvVideoFrameRateCallbackData& cbData);

/**
 * @brief Get supported DV modes.
 * 
 * This function returns the supported DV modes.
 *
 * @param[out] dvModes[]            - List of available DV modes ("dark", "bright").
 * @param[out] count                - Count  of available DV modes.(max count value is 2)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - When the count of supported modes is 0
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedDVModes(pic_modes_t *dvModes[],unsigned short *count);

/**
 * @brief Set dolby vision mode.
 * 
 * This function sets the Dolby vision mode.
 *
 * @param[in] dolbyMode              - Dolby vision mode to be set(dark, bright)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting DV mode
 * @retval tvERROR_INVALID_PARAM             - When the set value is not valid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetTVDolbyVisionMode()
 */
tvError_t SetTVDolbyVisionMode(const char * dolbyMode);

/**
 * @brief Get dolby vision mode.
 * 
 * This function returns the dolbymode currently set.
 *
 * @param[out] dolbyMode              - Current Dolby vision mode(dark, bright)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_GENERAL                   - Error while getiing DV mode
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see SetTVDolbyVisionMode()
 */
tvError_t GetTVDolbyVisionMode(char *dolbyMode);

/**
 * @brief Set HLG mode
 * 
 * This function sets the given HLG mode.
 *
 * @param[in] hlgMode               - HLG mode to be set(dark, bright)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting HLG mode
 * @retval tvERROR_INVALID_PARAM             - When the set value is not valid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetTVHLGMode(const char * hlgMode);

/**
 * @brief Set HDR10 mode.
 * 
 * This function sets the given HDR10 mode.
 *
 * @param[in] hdr10Mode             - HDR10 mode to be set(dark, bright)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting HDR mode
 * @retval tvERROR_INVALID_PARAM             - When the set value is not valid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetTVHDR10Mode(const char * hdr10Mode);

/**
 * @brief Get the supported HLG modes.
 * 
 * This function returns the supported HLG modes
 *
 * @param[out] dvModes             - List of supported HLG modes.(dark, bright)
 * @param[out] count               - Count of supported HLG modes.(max count value is 2)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - When the count of supported modes is 0
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedHLGModes(pic_modes_t *dvModes[],unsigned short *count);

/**
 * @brief Get the supported HDR10 modes.
 * 
 * This function returns the supported HDR10modes
 *
 * @param[out] dvModes            - List of supported hdr10modes.(dark, bright)
 * @param[out] count              - Count of supported hdr10modes.(max count value is 2)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - When the count of supported modes is 0
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedHDR10Modes(pic_modes_t *dvModes[],unsigned short *count);

/**
 * @brief Set Dynamic contrast.
 * 
 * This function enables/disables the dynamic contrast mode.
 * 
 * @param[in] mode  - Dynamic contrast mode to be enabled/disabled(true, false)
 *
 * @return tvError_t
 * @retval tvERROR_NONE              - Success
 * @retval tvERROR_GENERAL           - Error while setting dynamic contrast
 * @retval tvERROR_INVALID_STATE     - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetDynamicContrast()
 */
tvError_t SetDynamicContrast(bool mode);

/**
 * @brief Get Dynamic contrast mode.
 * 
 * This function returns whether dynamic contrast mode enabled/disabled.
 *
 * @param[out] mode        - Current dynamic contrast mode(true, false)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                   - Success
 * @retval tvERROR_GENERAL                - Error while getting dynamic contrast
 * @retval tvERROR_INVALID_PARAM          - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE          - Interface is not initialized

 *
 * @pre  tvInit() should be called before calling this API.
 * @see SetDynamicContrast()
 */
tvError_t GetDynamicContrast(bool *mode);

/**
 * @brief Set white balance control.
 * 
 * This function sets the white balance for specific color, color Temp, control.
 *
 * @param[in] inputSrc                    - Source of input ("HDMI", "TV", "AV")
 * @param[in] colorTemp                   - Color temperature value("custom", "normal", "cool", "warm")
 * @param[in] color                       - Color to be set ("red", "blue", "green")
 * @param[in] ctrl                        - Control to be set ("gain", "offset")
 * @param[in] value                       - Values to be set for the specific control(gain: 0 to 2047, offset: -1024 to 1024)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                   - Success
 * @retval tvERROR_GENERAL                - Error while setting color temperature
 * @retval tvERROR_INVALID_PARAM          - When the set value is not valid
 * @retval tvERROR_INVALID_STATE          - When the input value is not valid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t setWBctrl(char *inputSrc, char *colorTemp,char *color, char *ctrl, int value);

/**
 * @brief Get white balance control
 * 
 * This function gets the white balance for specific color, color Temp, control.
 *
 * @param[in] inputSrc                    - Source of input ("HDMI", "TV", "AV")
 * @param[in] colorTemp                   - Color temperature value("custom", "normal", "cool", "warm")
 * @param[in] color                       - Color to be set ("red", "blue", "green")
 * @param[in] ctrl                        - Control to be set ("gain", "offset")
 * @param[in] value                       - Values to be set for the specific control(gain: 0 to 2047, offset: -1024 to 1024)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                    - Success
 * @retval tvERROR_INVALID_PARAM           - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE           - When the input value is not valid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t getWBctrl(char *inputSrc, char *colortemp, char *color, char *ctrl, int *value);

/**
 * @brief Get the white balance info
 * 
 * This function gets the White balance info into the vectors
 *
 * @param[out] params               - WB info param(wbControls :("gain", "offset"), wbGain: (0 to 2047), wbOffset: (-1024 to 1024))
 * @param[out] selector             - selector vector("color temp", "input")
 * @param[out] colorTmp             - Color temperature vector("custom", "normal", "cool", "warm")
 * @param[out] input                - Input source vector("TV", "HDMI", "AV")
 *
 * @return tvError_t
 * @retval tvERROR_NONE                    - Success
 * @retval tvERROR_INVALID_PARAM           - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE           - When the input value is not valid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t getWbInfo(getWBInfo_t* params, std::vector<std::string> &selector, std::vector<std::string> &colorTmp, std::vector<std::string> &input);

/**
 * @brief Enable/disable WB mode.
 * 
 * This function enables or disables white balance mode.
 *
 * @param[in] value                        - Enable/disable WB mode (true, false)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                    - Success
 * @retval tvERROR_GENERAL                 - Error while setting WB mode
 * @retval tvERROR_INVALID_STATE           - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t enableWBmode(bool value);

/**
 * @brief Get Supported Component color.
 * 
 * This function gets the supported component color. @n
 * The output has the list of supported color where each bit position represents color from tvDataComponentColor_t.
 *
 * @param[out] blComponentColor           - Component color(tvDataComponentColor_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetSupportedComponentColor(int *blComponentColor);

/**
 * @brief Set current component saturation.
 * 
 * This function sets the current component saturation for the specific color.
 * @param[in] blSaturationColor          - Component color(tvDataComponentColor_t)
 * @param[in] saturation                 - Saturation value to set(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting current saturation
 * @retval tvERROR_INVALID_PARAM             - When the set value is not valid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int saturation);

/**
 * @brief Get current component saturation.
 * 
 * This function returns the current component saturation for the specific color.
 *
 * @param[in] blSaturationColor         - Component color(tvDataComponentColor_t)
 * @param[out] saturation               - Saturation value of the color(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int *saturation);

/**
 * @brief Set current component hue.
 * 
 * This function sets the current component hue for the specific color.
 *
 * @param[in] blHueColor               - Component color(tvDataComponentColor_t)
 * @param[in] hue                      - Hue value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting current hue
 * @retval tvERROR_INVALID_PARAM             - When the set value is not valid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetCurrentComponentHue(tvDataComponentColor_t blHueColor, int hue);

/**
 * @brief Get current component hue.
 * 
 * This function returns the hue value for the specific color                                 
 *
 * @param[in] blHueColor              - Componenct color(tvDataComponentColor_t)
 * @param[out] hue                    - Hue value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentComponentHue(tvDataComponentColor_t blHueColor, int *hue);

/**
 * @brief Set the current component luma value.
 * 
 * This function set the current component luma value for the specific color.
 *
 * @param[in] blLumaColor            - Componenct color(tvDataComponentColor_t)
 * @param[in] Luma                   - Luma value(0 - 30)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting current luma
 * @retval tvERROR_INVALID_PARAM             - When the set value is not valid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int Luma);

/**
 * @brief Get the current component luma.
 * 
 * This function returns the luma value for the specific color.
 *
 * @param[in] blLumaColor          - Color component(tvDataComponentColor_t)
 * @param[out] Luma                - Luma value(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int *Luma);

/**
 * @brief Get supported dimming modes.
 * 
 * This function returns the supported dimming modes of TV.
 *
 * @param[out] dimmingModes        - List of dimming modes of the TV(local, fixed, global)
 * @param[out] count               - count of supported dimming modes.(Max count value is 3)
 *
 * @return tvError_t
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_GENERAL         - When the supported count is 0
 * @retval tvERROR_INVALID_PARAM   - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized

 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedDimmingModes(char **dimmingModes,unsigned short *count);

/**
 * @brief Set the dimming mode.
 * 
 * This function sets the TV dimming mode.
 *
 * @param[in] dimmingMode           - Dimming mode to be set(local, fixed, global)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting dimming mode
 * @retval tvERROR_INVALID_PARAM    - When the set value is not valid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetTVDimmingMode(const char *dimmingMode);

/**
 * @brief Get picture mode index.
 * 
 * This function returns the current picture mode index value.
 *
 * @param[in] pictureMode           - picturemode ("Entertainment", "Dynamic", "Expert", "Movie", "Sports", "Graphics")
 *
 * @return tvPictureMode_t     (0 - 9)
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvPictureMode_t GetTVPictureModeIndex(const char * pictureMode);

/**
 * @brief Get current content format.
 * 
 * This function returns the current video format that is set.
 *
 * @retval tvVideoHDRFormat_t
 * @retval tvVideoFormat_NONE		- 0x00
 * @retval tvVideoFormat_SDR 		- 0x01
 * @retval tvVideoFormat_HLG 		- 0x02
 * @retval tvVideoFormat_HDR10 		- 0x04
 * @retval tvVideoFormat_HDR10PLUS  - 0x08
 * @retval tvVideoFormat_DV 		- 0x010
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvVideoHDRFormat_t GetCurrentContentFormat(void);

/**
 * @brief Get supported content formats.
 * 
 * This function returns all the supported content formats.
 *
 * @param[out] contentFormats       - List of supported content formats(tvVideoHDRFormat_t)
 * @param[out] numberOfFormats      - Count of supported content formats. 
 * 
 * @return tvError_t
 * @retval tvERROR_NONE            - Success
 * @retval tvERROR_INVALID_PARAM   - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE   - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetSupportedContentFormats(unsigned int * contentFormats,unsigned short *numberOfFormats);

/**
 * @brief Save color temperature values to driver.
 * 
 * This function saves the color temperature value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the color temperature(tvColorTemp_t)
 *                                    
 * @return tvError_t                  
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving color temperature
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveColorTemperature(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,tvColorTemp_t value);

/**
 * @brief Save backlight value to driver.
 * 
 * This function saves the backlight value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 * 
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the backlight(0 - 100)
 *                                    
 * @return tvError_t                  
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving backlight
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveBacklight(tv_source_input_t sourceInput, int pq_mode	,tvhdr_type_t hdr_type,int value);

/**
 * @brief Save contrast value to driver.
 * 
 * This function saves the contrast value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 * 
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the contrast(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving contrast
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveContrast(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,int value);

/**
 * @brief Save saturation value to driver.
 * 
 * This function saves the saturation value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 * 
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the saturation(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving saturation
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveSaturation(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,int value);

/**
 * @brief Save sharpness value to driver.
 * 
 * This function saves the sharpness value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 * 
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the sharpness(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving sharpness
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveSharpness(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,int value);

/**
 * @brief Save brightness value to driver.
 * 
 * This function saves the brightness value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the brightness(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving brightness
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveBrightness(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,int value);

/**
 * @brief Save hue value to driver.
 * 
 * This function saves the hue value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the hue(0 - 100)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving hue
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveHue(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,int value);

/**
 * @brief Save dynamic backlight value to driver.
 * 
 * This function saves the dynamic backlight value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the dynamic backlight(tvDimmingMode_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving dynamic backlight
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *  
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveDynamicBacklight(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,tvDimmingMode_t value);

/**
 * @brief Save display mode value to driver.
 * 
 * This function saves the display mode value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the display mode(tvDisplayMode_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while saving display mode
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveDisplayMode(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,tvDisplayMode_t value);

/**
 * @brief Save CMS value to driver.
 * 
 * This function saves the CMS value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] tunnel_type           - Tunnel type value(tvCMS_tunel_t)
 * @param[in] color_type            - Color type value(tvcomponent_color_type_t)
 * @param[in] value                 - Value of the CMS(Hue and saturation: 0 - 100, Luma: 0 -30)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while saving CMS
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized 
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveCMS(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,tvCMS_tunel_t tunnel_type,tvcomponent_color_type_t color_type,int value);

/**
 * @brief Save dolby mode value to driver.
 * 
 * This function saves the dolby mode value for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the dolby mode(dark, bright)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while saving dolby mode
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveDolbyMode(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,int value);

/**
 * @brief Get count of supported modes.
 * 
 * This function returns the number of supported picture modes. The number should be greater than zero.
 *
 * @param[in] pqmode                - total Number of Pq Modes support available in config file
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized  
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetNumberOfModesupported(int *pqmode);

/**
 * @brief Get current PQ index.
 * 
 * This function returns the current PQ index value.
 * @param[in] pqIndex                -  Pq Modes Index value in config file
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized  
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentPQIndex(int *pqIndex);

/**
 * @brief Get supported picture mode index.
 * 
 * This function gets all the supported picture mode index.
 *
 * @param[out]  pic_mode_index      - List of all supported  pic mode index  ( 0 to 9)
 * 
 * @pre  tvInit() should be called before calling this API.
 */
void GetAllSupportedPicModeIndex(int pic_mode_index[]);

/**
 * @brief Get CMS default value
 * 
 * This function returns the default CMS value
 * 
 * @param[in] color_tunel_type      - Color tunel type(tvCMS_tunel_t)
 *
 * @return int
 * @retval 15                       - Luma default value
 * @retval 50                       - Hue or saturation default value
 * @retval -1                       - When the parameter value is invalid
 *  
 * @pre tvInit() should be called before calling this API.
 */
int GetCMSDefault(tvCMS_tunel_t color_tunel_type);

/**
 * @brief Get dolby mode index.
 * 
 * This function returns the dolby mode index.
 * 
 * @param[out] dolbyMode            - Dolbymode index(dark, bright)
 *
 * @return int
 * @retval 0                        - tvDolbyMode_Dark
 * @retval 1                        - tvDolbyMode_Bright
 * @retval -1                       - When the parameter value is invalid
 *
 * @pre  tvInit() should be called before calling this API.
 */
int GetDolbyModeIndex(const char * dolbyMode);

/**
 * @brief Set the CMS state.
 * 
 * This function sets the CMS state for the specific tunel type, color type and component state
 *
 * @param[in] tunelType             - Tunel type(tvCMS_tunel_t)
 * @param[in] colorType             - Color type(tvcomponent_color_type_t)
 * @param[in] componentState        - Component state(tvcomponent_state_t)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting CMS state
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetCMSState(tvCMS_tunel_t tunelType,tvcomponent_color_type_t colorType,tvcomponent_state_t componentState);

/**
 * @brief Set color temperature.
 * 
 * This function updates the color temperature for user.
 *
 * @param[in] rgbType               - RGB type(tvRGBType_t)
 * @param[in] value                 - Color temperature value(gain: 0 to 2047, offset: -1024 to 1024)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting color temperature
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemperatureUser(tvRGBType_t rgbType, int value);

/**
 * @brief Save color temperature.
 * 
 * This function saves the color temperature for user to driver.
 *
 * @param[in] rgbType               - RGB type(tvRGBType_t)
 * @param[in] value                 - Color temperature value(gain: 0 - 2047, offset: -1024 - 1024)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while save color temperature
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveColorTemperatureUser(tvRGBType_t rgbType, int value);

/**
 * @brief Get HLG mode.
 * 
 * This function returns HLG mode index.
 *
 * @param[in] hlgMode               - HLG mode(dark, bright)
 *
 * @return int
 * @retval 6                        - tvHLGMode_Dark
 * @retval 7                        - tvHLGMode_Bright
 * @retval -1                       - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
int GetHLGModeIndex(const char * hlgMode);

/**
 * @brief Get HDR10 mode index.
 * 
 * This function returns HDR10 mode index.
 *
 * @param[out] hdr10Mode            - HDR10Mode index(dark, bright)
 *
 * @return int
 * @retval 3                        - tvHDR10Mode_Dark
 * @retval 4                        - tvHDR10Mode_Bright
 * @retval -1                       - When the parameter value is invalid
 * 
 * @pre  tvInit() should be called before calling this API.
 */
int GetHDR10ModeIndex(const char * hdr10Mode);

/**
 * @brief Set backlight fade value.
 * 
 * This function will fade the backlight value from current to the new value in the given duration.
 *
 * @param[in] from                  - Current backlight value (0 - 100)
 * @param[in] to                    - New backlight value to be set (0 - 100)
 * @param[in] duration              - Time duration for which the backlight needs to be faded to reach new value.(0 - 10000)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_GENERAL          - Error in setting the value
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetBacklightFade(int from,int to,int duration);

/**
 * @brief Enable or disable gamma mode.
 * 
 * This function enables or disables the gamma mode.
 *
 * @param[in] mode                - Gamma mode(0 or 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_GENERAL          - Error while write to sysfs
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetGammaMode(int mode);

/**
 * @brief Set the dimming level.
 * 
 * This function sets the dimming level value.
 *
 * @param[in] localDimmingLevel                -  Dimming level (0 - 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting dimming level
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetLocalDimmingLevel(int localDimmingLevel);

/**
 * @brief Get the dimming level.
 * 
 * This function gets the dimming level value.
 *
 * @param[out] localDimmingLevel                -  Dimming level (0 - 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetLocalDimmingLevel(int *localDimmingLevel);

/**
 * @brief Save local dimming level value to driver.
 * 
 * This function saves the local dimming level value for the specific picture mode, hdr type and source type. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the local dimming level(0 - 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE                      - Success
 * @retval tvERROR_GENERAL                   - Error while setting dimming level
 * @retval tvERROR_INVALID_PARAM             - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE             - Interface is not initialized
 * @retval tvERROR_OPERATION_NOT_SUPPORTED   - Operation is not supported
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveLocalDimmingLevel(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,int value);

/**
 * @brief Save low latency state to driver.
 * 
 * This function saves the low latency state for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 *
 * @param[in] sourceInput           - Source input value(tv_source_input_t)
 * @param[in] pq_mode               - PQ mode value read from config file 
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the low latency index(0 or 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting latency state
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveLowLatencyState(tv_source_input_t sourceInput, int pq_mode,tvhdr_type_t hdr_type,int value );

/**
 * @brief Set low latency state
 *
 * This function sets the low latency state
 *
 * @param[in] lowLatencyIndex       - Value of the low latency state(0 or 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting latency state
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetLowLatencyState( int lowLatencyIndex );

/**
 * @brief Get low latency state
 *
 * This function gets the low latency state
 *
 * @param[in] lowlatencystate       - Value of the low latency state(0 or 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting latency state
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetLowLatencyState(int *lowlatencystate);

/**
 * @brief Set the gamma calibrated values
 *
 * This function sets the gamma calibrated values(0 - 65535) for the primary colors.
 *
 * @param[in] pData_R       - Array of gamma red values (0 - 65535)
 * @param[in] pData_G       - Array of gamma green values (0 - 65535)
 * @param[in] pData_B       - Array of gamma blue values (0 - 65535)
 * @param[in] size          - size of each array(256)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting the gamma values
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetGammaTable(unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);

/**
 * @brief Get the gamma calibrated values
 *
 * This function gets the gamma calibrated values(0 - 65535) for the primary colors for a specific color temperature.
 *
 * @param[in] colortemp       - Color temperature (tvColorTemp_t)
 * @param[out] pData_R        - Array of gamma red values (0 - 65535)
 * @param[out] pData_G        - Array of gamma green values (0 - 65535)
 * @param[out] pData_B        - Array of gamma blue values (0 - 65535)
 * @param[out] size           - size of each array(256)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while geting the gamma values
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetGammaTable(int colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);

/**
 * @brief Save the gamma calibrated values to driver
 *
 * This function saves the gamma calibrated values(0 - 65535) for the primary colors for a specific color temperature.
 *
 * @param[in] colortemp       - Color temperature (tvColorTemp_t)
 * @param[in] pData_R         - Array of gamma red values (0 - 65535)
 * @param[in] pData_G         - Array of gamma green values (0 - 65535)
 * @param[in] pData_B         - Array of gamma blue values (0 - 65535)
 * @param[in] size            - size of each array(256)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while geting the gamma values
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveGammaTable(int colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);

/**
 * @brief Set the gamma pattern.
 *
 * This function sets the primary color level at 10bit resolution(0 - 1023).
 *
 * @param[in] is_10_bit                  - value is 10 bit(0) or not(1)
 * @param[in] R_Value                    - Red level of input pattern (0 - 1023).
 * @param[in] G_Value                    - Green level of input pattern (0 - 1023).
 * @param[in] B_Value                    - Blue level of input pattern (0 - 1023).
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting gamma pattern
 * @retval tvERROR_INVALID_PARAM    - When the parameter value is invalid
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 *
 * @pre  tvInit() should be called before calling this API.
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

