/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2022 Sky UK
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
* @defgroup tvsettings
* @{
* @defgroup APIs
* @{
**/


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
/** 
* A structure representing the pic modes
*/
typedef struct pic_modes{
    char name[PIC_MODE_NAME_MAX]; /**< pic modes array */
    short int value;/**< pic mode value */
}pic_modes_t;

/** 
* structure represents Video format call back data
*/
typedef struct
{
    void *userdata; /**< user data received from call back */
    tvVideoFormatChangeCB cb;/**< callback data */
}tvVideoFormatCallbackData;

/**
* structure represents colour temperature
*/ 
typedef enum {
    mfrColorTemp_STANDARD = 0, /**< standard color temperature */
    mfrColorTemp_COLD, /**< cold color temperature */
    mfrColorTemp_WARM, /**< warm color temperature */
    mfrColorTemp_USER, /** User color Temperature */
    mfrColorTemp_MAX /** Max Color Temperature */
}fp_mfrColorTemp_t;

/** 
* Structure representing the input source offset
**/
typedef enum input_source_offset_e {
    HDMI_OFFSET_NEW = 0, /** HDMI offset */
    TV_OFFSET_NEW   = 4, /** TV offset */
    AV_OFFSET_NEW   = 8, /** AV offset */
    MAX_OFFSET_NEW /** Max offset */
} input_source_offset_t;

/**
* Structure Representing the White Balanace Info
*/
typedef struct getWBInfo {
    char wbControls[CONTROL_COUNT][MAX_STRING_SIZE]; /** White Balance Controls */
    char wbGain[CONTROL_COUNT][MAX_STRING_SIZE]; /**White Balance Gain */
    char wbOffset[CONTROL_COUNT][MAX_STRING_SIZE]; /** White Balance Offset */
}getWBInfo_t;

#ifndef __BL_PARA__
#define __BL_PARA__
/**
* Structure representing the backlight parameters
*/
typedef struct bl_para_s{
    int mBacklightSDR; /** Backlight SDR */
    int mBacklightHDR; /** Backlight HDR */
}bl_para_t;
#endif

/**
* Structure representing the backlight info 
*/
typedef struct tvBacklightInfo_s{
    int sdrBLCurve[BACKLIGHT_CURVE_MAX_INDEX]; /** Backlight curve SDR */
    int hdrBLCurve[BACKLIGHT_CURVE_MAX_INDEX]; /** Backlight curve HDR */
    int defaultBLSDR; /** backlight SDR default value */
    int defaultBLHDR; /** backlight HDR default value */
}tvBacklightInfo_t;

/**
 * @brief Initialize the TV Settings HAL API
 * This function should initiliaze the tv settings hal api's and set the config mode from the file
 *
 * @param [in]  :  None
 * @param [out] :  None
 *
 * @return Error Code:  If error code is returned, Initialization failed
 * @warning  This API is Not thread safe.
 * @see tvTerm()
 *
 */

tvError_t tvInit();
/**
 * @brief Initialize the TV Settings HAL API
 * This function should initiliaze the tv settings hal api's and set the config mode from the file
 *
 * @param [in]  :  None
 * @param [out] :  None
 *
 * @return Error Code:  If error code is returned, Initialization failed
 * @warning  This API is Not thread safe.
 *
 */
tvError_t tvSD3toCriSyncInit();

/**
 * @brief Initialize the TV Settings HAL API
 * This function should initiliaze the tv settings hal api's and set the config mode from the file
 *
 * @param [in]   None
 * @param [out]  None
 *
 * @return Error Code:  If error code is returned, Initialization failed
 * @warning  This API is Not thread safe.
 *
 */
tvError_t tvTerm();

/**
 * @brief Get the TV Pciture Mode
 * This function will get the tv picture mode currently set.
 *
 * @param [in]    None 
 * @param [out]   pictureMode returns the picturemode currently set
 *
 * @return returns on success : no error
 *                 on failure : default value
 * @pre  tvInit() should be called before calling this API.
 * @see SetTVPictureMode()
 */
tvError_t GetTVPictureMode(char *pictureMode);

/**
 * @brief Set the TV Pciture Mode
 * This function updates the picture mode to driver
 *
 * @param[in] pictureMode indicates the mode type of picture 
 * @param [out]  None
 *
 * @return returns on success : no error
 *                 on failure : default value
 * @pre  tvInit() should be called before calling this API.
 * @see GetTVPictureMode()
 */
tvError_t SetTVPictureMode(const char * pictureMode);

/**
 * @brief This function gets the back light from PQ
 *
 * @param[in] None 
 * @param[out] backlight indicates the pointer variable
 *
 * @return returns on success : no error
 *                 on failure : default value
 * @pre  tvInit() should be called before calling this API.
 * @see SetBacklight()
 */
tvError_t GetBacklight(int *backlight);

/**
 * @brief This function updates the back light to PQ
 *
 * @param[in] backlight indicates the back light value of TV
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetBacklight()
 */
tvError_t SetBacklight(int backlight);

/**
 * @brief This function updates the brightness to driver
 *
 * @param[in] brightness indicates the value of brightness
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetBrightness()
 */
tvError_t SetBrightness(int brightness);

/**
 * @brief This function gets the brightness from driver
 *
 * @param[in] None
 * @param[out] *brightness indicates the pointer variable
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 * @pre  tvInit() should be called before calling this API.
 * @see SetBrightness()
 */
tvError_t GetBrightness(int *brightness);

/**
 * @brief  This function updates the contrast to driver
 *
 * @param[in] contrast indicates the contrast value
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetContrast()
 */
tvError_t SetContrast(int contrast);

/**
 * @brief This function gets the contrast from driver
 *
 * @param[in] None
 * @param[out] *contrast indicates the pointer variable
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 * @pre  tvInit() should be called before calling this API.
 * @see SetContrast()
 */
tvError_t GetContrast(int *contrast);

/**
 * @brief This function updtes the sharpness to driver
 *
 * @param[in] sharpness indicates the sharpness value
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetSharpness()
 */
tvError_t SetSharpness(int sharpness);

/**
 * @brief  This function gets the sharpness from driver
 *
 * @param[in] None
 * @param[out] sharpness indicates the pointer variable
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 * @pre  tvInit() should be called before calling this API.
 * @see SetSharpness()
 */
tvError_t GetSharpness(int *sharpness);

/**
 * @brief This function updates the saturation to driver
 *
 * @param[in] saturation indicates the saturation value
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetSaturation()
 */
tvError_t SetSaturation(int saturation);

/**
 * @brief This function gets the saturation from driver
 *
 * @param[in] None
 * @param[out] saturation indicates the pointer
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetSaturation()
 */
tvError_t GetSaturation(int *saturation);

/**
 * @brief This function updates the hue to driver
 *
 * @param[in] hue indicates the value of hue
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetHue()
 */
tvError_t SetHue(int hue);

/**
 * @brief This function gets the hue from driver
 *
 * @param[in] None
 * @param[out] hue indicates the pointer variable
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetHue()
 */
tvError_t GetHue(int *hue);

/**
 * @brief This function updates the color temperature to driver
 *
 * @param[in] colorTemp indicates the value of colorTemp
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemperature()
 */
tvError_t SetColorTemperature(tvColorTemp_t colorTemp);

/**
 * @brief This function gets the color tmperature from driver
 *
 * @param[in] None
 * @param[out] colorTemp indicates the pointer variable to enum tvColorTemp_t
 *
 * @return Returns on success : no error
                   if amlTvClient is null : invalid state
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemperature()
 */
tvError_t GetColorTemperature(tvColorTemp_t *colorTemp);

/**
 * @brief This function updates the Aspect ratio to driver
 *
 * @param[in] dispMode indicates the value of aspect ratio
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 * @see GetAspectRatio()
 */
tvError_t SetAspectRatio(tvDisplayMode_t dispMode);

/**
 * @brief This function gets the aspect ratio from driver
 *
 * @param[in] None
 * @param[out] dispMode indicates the pointer variable to enum tvDisplayMode_t
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 * @pre  tvInit() should be called before calling this API.
 * @see SetAspectRatio()
 */
tvError_t GetAspectRatio(tvDisplayMode_t *dispMode);

/**
 * @brief This function updates the back light to PQ
 *
 * @param[in] backlight indicates the back light value of TV
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetBacklight()
 */
tvError_t GetTint(int *tint);

/**
 * @brief This function updates the back light to PQ
 *
 * @param[in] backlight indicates the back light value of TV
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetBacklight()
 */
tvError_t SetTint(int tint);

/**
 * @brief This function gets all supported backlight modes of TV
 *
 * @param[in] None
 * @param[out] blMode indicates the pointer to modes
 *
 * @return Returns on success : no error
 *                  if amlTvClient is null : invalid state
 * @pre  tvInit() should be called before calling this API.
 * @see GetCurrentBacklightMode(),SetCurrentBacklightMode()
 */
tvError_t GetSupportedBacklightModes(int *blModes);

/**
 * @brief This function gets the backlight mode
 *
 * @param[in] None
 * @param[out] blMode indicates the pointer variable
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 * @pre  tvInit() should be called before calling this API.
 * @see GetSupportedBacklightModes(),SetCurrentBacklightMode()
 */
tvError_t GetCurrentBacklightMode(tvBacklightMode_t *blMode);

/**
 * @brief This function sets the backlight mode
 *
 * @param[in] blMode indicates the back light mode of TV
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in tvBacklightMode_t : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetSupportedBacklightModes(),GetCurrentBacklightMode()
 */
tvError_t SetCurrentBacklightMode(tvBacklightMode_t blMode);

/**
 * @brief This function gets the current video format
 *
 * @param[in] None
 * @param[out] format indicates the pointer variable
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentVideoFormat(tvVideoHDRFormat_t *format);

/**
 * @brief This function gets the current video resolution
 *
 * @param[in] None
 * @param[out] res indicates the video resolution 
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetVideoResolution(tvResolutionParam_t *res);

/**
 * @brief This function gets the current video Frame Rate.
 *
 * @param[in] None
 * @param[out] format indicates the video Frame Rate
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetVideoFrameRate(tvVideoFrameRate_t *format);

/**
 * @brief This function sets the config for deepsleep wakeup
 *
 * @param[in] src_type indicates the way of waking up.
 * @param[in] value indicates whether the given src_type is enabled or disabled.
 * @param[out] None
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
*/
tvError_t setWakeupConfig(const tvWakeupSrcType_t src_type, const bool value);

/**
 * @brief This function updates the RGB color value for the pattern to driver
 *
 * @param[in] r indicates red colour value of the pattern
 * @param[in] g indicates green colour value of the pattern
 * @param[in] b indicates blue colour value of the pattern
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetRGBPattern()
 */

tvError_t SetRGBPattern(int r,int g, int b) ;

/**
 * @brief This function gets the RGB pattern value  from driver
 *
 * @param[in] None
 * @param[out] r indicates the red value of the pattern from driver
 * @param[out] g indicates the green value of the pattern from driver
 * @param[out] b indicates the blue value of the pattern from driver
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetRGBPattern()
 */
tvError_t GetRGBPattern(int *r,int *g,int *b);

/**
 * @brief This function updates the YUV  color value  to driver
 *
 * @param[in] YUVValue indicates yuv values for the pattern
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetGrayPattern()
 */
tvError_t SetGrayPattern(int YUVValue);

/**
 * @brief This function gets the GetGrayPattern  pattern value  from driver
 *
 * @param[in] None
 * @param[out] YUVValue  indicates the pointer variable
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetGrayPattern()
 */
tvError_t GetGrayPattern(int* YUVValue);

/**
 * @brief This function sets the while balance Red Gain
 *
 * @param[in] colorTemp indicates the colour temperature
 * @param[out] rgain indicates the red gain value.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_Rgain()
 */
tvError_t SetColorTemp_Rgain(tvColorTemp_t colorTemp, int rgain);

/**
 * @brief This function gets the while balance Red Gain
 *
 * @param[in] colorTemp indicates the colorTemp of TV color.
 * @param[out] rgain indicates the  white balance red gain
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_Rgain()
 */
tvError_t GetColorTemp_Rgain(tvColorTemp_t colorTemp, int* rgain);

/**
 * @brief This function sets the white balance green gain.
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] ggain indicates the white balance green gain.
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_Ggain()
 */
tvError_t SetColorTemp_Ggain(tvColorTemp_t colorTemp, int ggain);

/**
 * @brief This function gets the green gain of color.
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[out] ggain returns the green gain  color set for white balance.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_Ggain()
 */
tvError_t GetColorTemp_Ggain(tvColorTemp_t colorTemp, int* ggain);

/**
 * @brief This function sets the white balance blue gain.
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] ggain indicates the white balance blue gain.
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_Bgain()
 */
tvError_t SetColorTemp_Bgain(tvColorTemp_t colorTemp, int bgain);
/**
 * @brief This function gets the blue gain of color.
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[out] ggain returns the blue gain  color set for white balance.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_Bgain()
 */
tvError_t GetColorTemp_Bgain(tvColorTemp_t colorTemp, int* bgain);
/**
 * @brief This function sets the whitebalance Red post offset
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] rpostoffset sets the red post offset 
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_R_post_offset()
 */
tvError_t SetColorTemp_R_post_offset(tvColorTemp_t colorTemp, int rpostoffset);

/**
 * @brief This function gets the Red post offset of white balance
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[out] rpostoffset returns the red post offset set for white balance.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_R_post_offset()
 */
tvError_t GetColorTemp_R_post_offset(tvColorTemp_t colorTemp, int* rpostoffset);

/**
 * @brief This function sets the whitebalance Green post offset
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] gpostoffset sets the green post offset 
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_G_post_offset()
 */
tvError_t SetColorTemp_G_post_offset(tvColorTemp_t colorTemp, int gpostoffset);

/**
 * @brief This function gets the green post offset of white balance
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[out] gpostoffset returns the green post offset set for white balance.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_G_post_offset()
 */
tvError_t GetColorTemp_G_post_offset(tvColorTemp_t colorTemp, int* gpostoffset);

/**
 * @brief This function sets the whitebalance Blue post offset
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] bpostoffset sets the blue post offset 
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_B_post_offset()
 */
tvError_t SetColorTemp_B_post_offset(tvColorTemp_t colorTemp, int bpostoffset);

/**
 * @brief This function gets the blue post offset of white balance
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[out] bpostoffset returns the blue post offset set for white balance.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_B_post_offset()
 */
tvError_t GetColorTemp_B_post_offset(tvColorTemp_t colorTemp, int* bpostoffset);

/**
 * @brief This function get the picture mode from the driver
 *
 * @param[in] None
 * @param[out] pictureModes returns the list of available picture modes of type tvPictureMode_t
 * @param[out] count returns the number of available picture modes
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedPictureModes(pic_modes_t *pictureModes[],unsigned short *count);

/**
 * @brief This function register a callback for video format update
 *
 * @param[in] cbData callback function
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
void RegisterVideoFormatChangeCB(tvVideoFormatCallbackData& cbData);

typedef void (*tvVideoResolutionChangeCB)(tvResolutionParam_t resolutionStruct,void *userData);
typedef struct
{
    void *userdata;
    tvVideoResolutionChangeCB cb;
}tvVideoResolutionCallbackData;

/**
 * @brief This function register a callback for video resolution update
 *
 * @param[in] cbData callback function
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
void RegisterVideoResolutionChangeCB(tvVideoResolutionCallbackData& cbData);

typedef void (*tvVideoFrameRateChangeCB)(tvVideoFrameRate_t frameRate,void *userData);
typedef struct
{
    void *userdata;
    tvVideoFrameRateChangeCB cb;
}tvVideoFrameRateCallbackData;
/**
 * @brief This function register a callback for video frame rate update
 *
 * @param[in] cbData callback function
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
void RegisterVideoFrameRateChangeCB(tvVideoFrameRateCallbackData& cbData);

/**
 * @brief This function returns the supported DV modes.
 *
 * @param[in] None
 * @param[out] dvModes[] returns the list of available DV modes.
 * @param[out] count returns the number  of available DV modes.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedDVModes(pic_modes_t *dvModes[],unsigned short *count);

/**
 * @brief This function sets the Dolby vision mode
 *
 * @param[in] dolbyMode indicates the dolbymode to be set on TV.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 * @see GetTVDolbyVisionMode()
 */
tvError_t SetTVDolbyVisionMode(const char * dolbyMode);

/**
 * @brief This function returns the dolbymode currently set on TV
 *
 * @param[in] None
 * @param[out] dolbyMode returns the dolby mode currently set
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 * @see SetTVDolbyVisionMode()
 */
tvError_t GetTVDolbyVisionMode(char *dolbyMode);

/**
 * @brief This function sets the given hlg mode to TV.
 *
 * @param[in] hlgmode indicates the hlgmode to be set.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 * @see GetTVHLGMode()
 */
tvError_t SetTVHLGMode(const char * hlgMode);

/**
 * @brief This function sets the given hdr10 mode to TV.
 *
 * @param[in] hdr10mode indicates the required hdr10mode to be set.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 * @see GetTVHDR10Mode()
 */
tvError_t SetTVHDR10Mode(const char * hdr10Mode);

/**
 * @brief This function returns the HLD mode currently set
 *
 * @param[in] None
 * @param[out] hlgMode returns the current hlgmode set.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 * @see SetTVHLGMode()
 */
tvError_t GetTVHLGMode(char *hlgMode);

/**
 * @brief This function returns the current HDR10mode set.
 *
 * @param[in] None
 * @param[out] hdr10Mode returns the current hdr10Mode set.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 * @see SetTVHDR10Mode()
 */
tvError_t GetTVHDR10Mode(char *hdr10Mode);

/**
 * @brief This function returns the supported HLG modes from TV
 *
 * @param[in] None
 * @param[out] dvModes returns the list of supported HLG modes.
 * @param[out] count returns the number of supported HLG modes.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedHLGModes(pic_modes_t *dvModes[],unsigned short *count);

/**
 * @brief This function returns the supported HDR10modes in TV.
 *
 * @param[in] None
 * @param[out] dvModes returns the list of supported hdr10modes.
 * @param[out] count returns the number of supported hdr10modes.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedHDR10Modes(pic_modes_t *dvModes[],unsigned short *count);

/**
 * @brief This function sets the dynamic contrast mode
 * @param[in] dynamicContrastEnable dynamic contrast mode to be set.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 * @see GetDynamicContrast()
 */
tvError_t SetDynamicContrast(const char *dynamicContrastEnable);

/**
 * @brief This function returns whether dynamic contrast mode currently set or not
 *
 * @param[in] None
 * @param[out] isDynamicContrastEnabled returns the string disabled/enabled for dynamic contrast mode.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 * @see SetDynamicContrast()
 */
tvError_t GetDynamicContrast(char *isDynamicContrastEnabled);

/**
 * @brief This function sets the R gain on White Balanace for given source.
 *
 * @param[in] colorTemp indicates the colorTemp
 * @param[in] rgain red gain on white balance
 * @param[in] sourceId source ID of the source for which red gain to be set
 * @param[in] saveOnly indicates whether the parameter to be saved.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int rgain,int sourceId, int saveOnly);

/**
 * @brief This function Gets the R gain on White Balanace for given source.
 *
 * @param[in] colorTemp indicates the colorTemp
 * @param[in] sourceId source ID of the source for which red gain to be set
 * @param[out] rgain returns the R gain on white balance.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int* rgain,int sourceId);
/**
 * @brief This function sets the G gain on White Balanace for given source.
 *
 * @param[in] colorTemp indicates the colorTemp
 * @param[in] ggain green gain on white balance
 * @param[in] sourceId source ID of the source for which green gain to be set
 * @param[in] saveOnly indicates whether the parameter to be saved.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int ggain,int sourceId, int saveOnly);

/**
 * @brief This function Gets the G gain on White Balanace for given source.
 *
 * @param[in] colorTemp indicates the colorTemp
 * @param[in] sourceId source ID of the source for which green gain to be set
 * @param[out] ggain returns the G gain on white balance.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int* ggain,int sourceId);

/**
 * @brief This function sets the B gain on White Balanace for given source.
 *
 * @param[in] colorTemp indicates the colorTemp
 * @param[in] bgain blue gain on white balance
 * @param[in] sourceId source ID of the source for which blue gain to be set
 * @param[in] saveOnly indicates whether the parameter to be saved.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int bgain,int sourceId, int saveOnly);
/**
 * @brief This function Gets the B gain on White Balanace for given source.
 *
 * @param[in] colorTemp indicates the colorTemp
 * @param[in] sourceId source ID of the source for which blue gain to be set
 * @param[out] bgain returns the Blue gain on white balance.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int* bgain,int sourceId);

/**
 * @brief This function sets the whitebalance Red post offset for given source
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] rpostoffset sets the red post offset 
 * @param[in] sourceId indicates the source id of the source for which the Red post offset to be set.
 * @param[in] saveOnly indicates whether the parameters needs to be saved.
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_R_post_offset_onSource()
 */
tvError_t SetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int rpostoffset,int sourceId, int saveOnly);

/**
 * @brief This function gets the Red post offset of white balance for given source
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] sourceId indicates the source id of the source for which the Red post offset needs to be get.
 * @param[out] rpostoffset returns the red post offset set for white balance for the specific source.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_R_post_offset_onSource()
 */
tvError_t GetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int* rpostoffset,int sourceId);

/**
 * @brief This function sets the whitebalance green post offset for given source
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] gpostoffset sets the green post offset 
 * @param[in] sourceId indicates the source id of the source for which the green post offset to be set.
 * @param[in] saveOnly indicates whether the parameters needs to be saved.
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_R_post_offset_onSource()
 */
tvError_t SetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int gpostoffset,int sourceId, int saveOnly);

/**
 * @brief This function gets the Green post offset of white balance for given source
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] sourceId indicates the source id of the source for which the Green post offset needs to be get.
 * @param[out] rpostoffset returns the green post offset set for white balance for the specific source.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_G_post_offset_onSource()
 */
tvError_t GetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int* gpostoffset,int sourceId);

/**
 * @brief This function sets the whitebalance Blue post offset for given source
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] bpostoffset sets the blue post offset 
 * @param[in] sourceId indicates the source id of the source for which the blue post offset to be set.
 * @param[in] saveOnly indicates whether the parameters needs to be saved.
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see GetColorTemp_B_post_offset_onSource()
 */
tvError_t SetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int bpostoffset,int sourceId, int saveOnly);

/**
 * @brief This function gets the Blue post offset of white balance for given source
 *
 * @param[in] colorTemp indicates the color temperature of the TV.
 * @param[in] sourceId indicates the source id of the source for which the Blue post offset needs to be get.
 * @param[out] bpostoffset returns the blue post offset set for white balance for the specific source.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 if not in range 0-100 : invalid param
 * @pre  tvInit() should be called before calling this API.
 * @see SetColorTemp_B_post_offset_onSource()
 */
tvError_t GetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int* bpostoffset,int sourceId);

/**
 * @brief This function sets the white balance for specific color, color Temp, control and value.
 *
 * @param[in] inputSrc indicates the source of input (HDMI, TV, AV)
 * @param[in] color  indicates the color to be set (red, blue, green)
 * @param[in] ctrl indicates the control to be done (gain or offset)
 * @param[in] value  indicates the values to be set for the specific control.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t setWBctrl(char *inputSrc, char *colorTemp,char *color, char *ctrl, int value);

/**
 * @brief This function gets the white balance for specific color, color Temp, control and value.
 *
 * @param[in] inputSrc indicates the source of input (HDMI, TV, AV)
 * @param[in] color  indicates the color to be set (red, blue, green)
 * @param[in] ctrl indicates the control to be done (gain or offset)
 * @param[out] value  indicates the pointer returned by driver to store the value.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t getWBctrl(char *inputSrc, char *colortemp, char *color, char *ctrl, int *value);

/**
 * @brief This function gets the White balance info into the vectors
 *
 * @param[in] None
 * @param[out] params indicates the pointer to the struct getWBInfo_t parameters.
 * @param[out] selector indicates the vector which tells whether to take colorTmp or input vector params.
 * @param[out] colorTmp indicates the vector which carries colorTmp details.
 * @param[out] input indicates the vector which carries the input details.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t getWbInfo(getWBInfo_t* params, std::vector<std::string> &selector, std::vector<std::string> &colorTmp, std::vector<std::string> &input);

/**
 * @brief This function enables or disables White balance in the sysfs.
 *
 * @param[in] value indicates whether to enable or disable
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t enableWBmode(bool value);

/**
 * @brief This function get the supported saturation color from the driver.
 *
 * @param[in] None
 * @param[out] blComponentColor returns the supported component color
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetSupportedComponentColor(int *blComponentColor);

/**
 * @brief This function sets the current component saturation
 *
 * @param[in] blSaturationColor indicates the saturation color to be set
 * @param[in] saturation  indicates the saturation value to set 
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int saturation);

/**
 * @brief This function returns the current component saturation
 *
 * @param[in] blSaturationColor indicates the saturation color to be changed
 * @param[out] saturation returns the saturation value of the color
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int *saturation);

/**
 * @brief This function sets the Hue to the component.
 *
 * @param[in] blHueColor indicates the hue color to be set.
 * @param[in] hue indicates the hue value.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetCurrentComponentHue(tvDataComponentColor_t blHueColor, int hue);

/**
 * @brief This function returns the hue value of the current component.                                 
 *
 * @param[in] blHueColor indicates the hue color of the component
 * @param[out] hue returns the hue value of the component
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentComponentHue(tvDataComponentColor_t blHueColor, int *hue);

/**
 * @brief This function set the luma color to the component
 *
 * @param[in] blLumaColor indicates the luma color to the set
 * @param[in] Luma indicates the luma color value to be set
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int Luma);

/**
 * @brief This function returns the luma value of the component.
 *
 * @param[in] blLumaColor indicates the luma color of the component
 * @param[out] Luma indicates the Luma value to be set.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int *Luma);

/**
 * @brief This function returns the supported dimming modes of TV.
 *
 * @param[in] None
 * @param[out] dimmingModes returns the dimming modes of the TV
 * @param[out] count returns the number of supported dimming modes.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVSupportedDimmingModes(char **dimmingModes,unsigned short *count);

/**
 * @brief This function sets the TV dimming mode.
 *
 * @param[in] dimmingMode indicates the dimmingMode to be set
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetTVDimmingMode(const char *dimmingMode);

/**
 * @brief This function returns the TV backlight global factor.
 *
 * @param[in] None
 * @param[out] value returns the value of the backlight global factor.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVBacklightGlobalFactor(int * value);

/**
 * @brief This function sets the TV backlight global factor
 *
 * @param[in] value indicates the value of the backlight global factor
 * @param[in] rangeMidPointValue indicates the mid point value of the range
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetTVBacklightGlobalFactor(int value, int rangeMidPointValue);

/**
 * @brief This function returns the current picture mode index
 *
 * @param[in] None
 * @param[out] pictureMode indicates the picture mode index value
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvPictureMode_t GetTVPictureModeIndex(const char * pictureMode);

/**
 * @brief This function returns the current content format
 *
 * @param[in] None
 * @param[out] returns the content format of type tvVideoHDRFormat_t
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvVideoHDRFormat_t GetCurrentContentFormat(void);

/**
 * @brief This function returns the supported content formats
 *
 * @param[in] None
 * @param[out] contentFormats returns the supported content formats
 * @param[out] numberOfFormats returns the number of supported content formats.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetSupportedContentFormats(unsigned int * contentFormats,unsigned short *numberOfFormats);

/**
 * @brief This function reset the brightness to default value.
 *
 * @param[in] defaultValue indicates the default value to be set.
 * @param[in] resetForAllFormats indicates whether to reset for all formats or not.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetBrightness(int defaultValue,bool resetForAllFormats);

/**
 * @brief This function reset the contrast to default value.
 *
 * @param[in] defaultValue indicates the default value to be set.
 * @param[in] resetForAllFormats indicates whether to reset for all formats or not.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetContrast(int defaultValue,bool resetForAllFormats);

/**
 * @brief This function reset the sharpness to default value.
 *
 * @param[in] defaultValue indicates the default value to be set.
 * @param[in] resetForAllFormats indicates whether to reset for all formats or not.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetSharpness(int defaultValue,bool resetForAllFormats);

/**
 * @brief This function reset the saturation to default value.
 *
 * @param[in] defaultValue indicates the default value to be set.
 * @param[in] resetForAllFormats indicates whether to reset for all formats or not.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetSaturation(int defaultValue,bool resetForAllFormats);

/**
 * @brief This function reset the hue to default value.
 *
 * @param[in] defaultValue indicates the default value to be set.
 * @param[in] resetForAllFormats indicates whether to reset for all formats or not.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetHue(int defaultValue,bool resetForAllFormats);

/**
 * @brief This function reset the backlight to default value.
 *
 * @param[in] defaultValue indicates the default value to be set.
 * @param[in] resetForAllFormats indicates whether to reset for all formats or not.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetBacklight(int defaultValue,bool resetForAllFormats);

/**
 * @brief This function reset the color Temperature to default value.
 *
 * @param[in] defaultValue indicates the default value to be set.
 * @param[in] resetForAllFormats indicates whether to reset for all formats or not.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetColorTemperature(int defaultValue,bool resetForAllFormats);

/**
 * @brief This function reset the component saturation to default value.
 *
 * @param[in] color indicates the color for which saturation to be set
 * @param[in] defaultValue indicates the default value to be set.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetComponentSaturation(int color,int defaultValue);

/**
 * @brief This function reset the component Luma to default value.
 *
 * @param[in] color indicates the color for which Luma to be set
 * @param[in] defaultValue indicates the default value to be set.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetComponentLuma(int color,int defaultValue);

/**
 * @brief This function reset the component Hue to default value.
 *
 * @param[in] color indicates the color for which Hue to be set
 * @param[in] defaultValue indicates the default value to be set.
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ResetComponentHue(int color,int defaultValue);

/**
 * @brief This function checks whether the current content format is SDR
 * @param[in] None
 * @param[out] bool value indicates whether the content format is SDR - True or False
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
bool isCurrentHDRTypeIsSDR(void);

/**
 * @brief This function returns the panel ID
 * @param[in] None
 * @param[out] panelid indicates the panel ID
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int GetPanelID(char* panelid);

/**
 * @brief This function returns the default panel ID
 * @param[in] None
 * @param[out] panelID carries the default panel ID
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
void GetDefaultPanelID(char *panelID);

/**
 * @brief This function saves the color Temperature value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which color temperature to be saved
 * @param[in] pq_mode indicates the pq mode for which color temperature is set
 * @param[in] hdr_type indicates the hdr type for which the color temperature to be saved.
 * @param[in] value indicates the value of the color temperature to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveColorTemperature(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the backlight value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which backlight to be saved
 * @param[in] pq_mode indicates the pq mode for which backlight is set
 * @param[in] hdr_type indicates the hdr type for which the backlight to be saved.
 * @param[in] value indicates the value of the backlight to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveBacklight(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the contrast value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which contrast to be saved
 * @param[in] pq_mode indicates the pq mode for which contrast is set
 * @param[in] hdr_type indicates the hdr type for which the contrast to be saved.
 * @param[in] value indicates the value of the contrast to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveContrast(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the saturation value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which saturation to be saved
 * @param[in] pq_mode indicates the pq mode for which saturation is set
 * @param[in] hdr_type indicates the hdr type for which the saturation to be saved.
 * @param[in] value indicates the value of the saturation to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveSaturation(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the sharpness value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which sharpness to be saved
 * @param[in] pq_mode indicates the pq mode for which sharpness is set
 * @param[in] hdr_type indicates the hdr type for which the sharpness to be saved.
 * @param[in] value indicates the value of the sharpness to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveSharpness(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the brightness value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which brightness to be saved
 * @param[in] pq_mode indicates the pq mode for which brightness is set
 * @param[in] hdr_type indicates the hdr type for which the brightness to be saved.
 * @param[in] value indicates the value of the brightness to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveBrightness(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the hue value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which hue to be saved
 * @param[in] pq_mode indicates the pq mode for which hue is set
 * @param[in] hdr_type indicates the hdr type for which the hue to be saved.
 * @param[in] value indicates the value of the hue to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveHue(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the dynamic backlight value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which dynamic backlight to be saved
 * @param[in] pq_mode indicates the pq mode for which dynamic backlight is set
 * @param[in] hdr_type indicates the hdr type for which the dynamic backlight to be saved.
 * @param[in] value indicates the value of the dynamic backlight to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveDynamicBacklight(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the display mode value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which display mode to be saved
 * @param[in] pq_mode indicates the pq mode for which display mode is set
 * @param[in] hdr_type indicates the hdr type for which the display mode to be saved.
 * @param[in] value indicates the value of the display mode to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveDisplayMode(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function saves the CMS value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which CMS to be saved
 * @param[in] pq_mode indicates the pq mode for which CMS is set
 * @param[in] hdr_type indicates the hdr type for which the CMS to be saved.
 * @param[in] value indicates the value of the CMS to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveCMS(int sourceInput, int pq_mode,int hdr_type,int tunnel_type,int color_type,int value);

/**
 * @brief This function saves the dolby mode value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] sourceInput indicates the source input for which dolby mode to be saved
 * @param[in] pq_mode indicates the pq mode for which dolby mode is set
 * @param[in] hdr_type indicates the hdr type for which the dolby mode to be saved.
 * @param[in] value indicates the value of the dolby mode to be saved
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveDolbyMode(int sourceInput, int pq_mode,int hdr_type,int value);

/**
 * @brief This function returns the number of supported modes
 * @param[in] None
 * @param[out] int value returns the number of supported modes
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int GetNumberOfModesupported(void);

/**
 * @brief This function returns the current PQ index
 * @param[in] None
 * @param[out] int value returns with current PQ index
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int GetCurrentPQIndex(void);

/**
 * @brief This function saves the dynamic backlight value for the 
 specific pq_mode for specific hdr_type for the given sourceInput
 * @param[in] None
 * @param[out]  pic_mode_index returns the array of all supported  pic mode index
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
void GetAllSupportedPicModeIndex(int pic_mode_index[]);

/**
 * @brief This function returns the default CMS value
 * @param[in] color_tunel_type indicates the color tunel type for which the CMS default value to be returned.
 * @param[out] returns the CMS default value
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int GetCMSDefault(tvCMS_tunel_t color_tunel_type);

/**
 * @brief This function returns the dolby mode index
 * @param[in] None
 * @param[out] dolbyMode indicates the dolbymode index.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int GetDolbyModeIndex(const char * dolbyMode);

/**
 * @brief This function converts the video format to HDR format.
 * @param[in] videoFormat indicates the videoFormat to be converted to HDR Format
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int ConvertVideoFormatToHDRFormat(tvVideoHDRFormat_t videoFormat);

/**
 * @brief This function converts the TV color to Vendor color
 * @param[in] blComponentColor indicates the component color to be converted to vendor color
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int ConvertTVColorToVendorColor(tvDataComponentColor_t blComponentColor);

/**
 * @brief This function converts the HDR format to content format
 * @param[in] hdrFormat indicates the hdrFormat to Content Format
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int ConvertHDRFormatToContentFormat(tvhdr_type_t hdrFormat);

/**
 * @brief This function returns the custom PQ mode index
 * @param[in] None
 * @param[out] returns the int value of custom PQ mode index
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int GetCustomPQModeIndex(void);

/**
 * @brief This function sets the CMS state for the specific tunel type and color type and component state
 * @param[in] tunelType indicates the tunel type
 * @param[in] colorType indicates the color type
 * @param[in] componentState indicates the component state
 * @param[out] None
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetCMSState(tvCMS_tunel_t tunelType,tvcomponent_color_type_t colorType,tvcomponent_state_t componentState);

/**
 * @brief This function checks if the White balance parameters are equal to default value.
 * @param[in] wbvalue indicates the white balance value struct member of type tvDataColor_t
 * @param[in] colorType indicates the color type
 * @param[out] bool True/False indicates whether the white balance is user default or not
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
bool isWBUserDfault(tvDataColor_t wbvalue);

/**
 * @brief This function gets the White balance RGB type
 * @param[in] None
 * @param[out] color indicates the color of white balance RGB type(red, green or blue)
 * @param[out] ctrl indicates the control whether gain or offset.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
int GetWBRgbType(const char *color, const char * ctrl);

/**
 * @brief This function checks the user White balance value on init
 * @param[in] None
 * @param[out] tvDataColor_t type struct - returns the user WB value on init.
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
tvDataColor_t GetUSerWBValueOnInit(void);

/**
 * @brief This function checks if two white balance value are same.
 * @param[in] wbvalueThis indicates one struct member of type tvDataColor_t
 * @param[in] wbvalueThat indicates the struct member of type tvDataColor_t
 * @param[out] bool True/False indicates whether wbvalueThis and wbvalueThat are equal or not
 *
 * @return Returns on success : no error
 * @pre  tvInit() should be called before calling this API.
 */
bool areEqual(tvDataColor_t wbvalueThis,tvDataColor_t wbvalueThat);

/**
 * @brief This function updates the color temperature to driver from user
 *
 * @param[in] rgbType indicates the type of rgb
 * @param[in] value indicates the value of rgbtype
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetColorTemperatureUser(int rgbType, int value);

/**
 * @brief This function saves the color temperature to driver from user
 *
 * @param[in] rgbType indicates the type of rgb
 * @param[in] value indicates the value of rgbtype
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveColorTemperatureUser(int rgbType, int value);

/**
 * @brief This function updates the backlight info to driver
 *
 * @param[in] backlightDefaults indicates the backlight info to be set
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetBacklightInfo(tvBacklightInfo_t backlightDefaults);

/**
 * @brief This function returns the driver equivalent backlight for current format
 *
 * @param[in] backlight indicates the backlight info to be set
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
int GetDriverEquivalentBLForCurrentFmt(int backlight);

/**
 * @brief This function returns HLG mode index from driver
 *
 * @param[in] None
 * @param[out] hlgMode indicates the hlgmode index
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
int GetHLGModeIndex(const char * hlgMode);

/**
 * @brief This function returns HDR10 mode index from driver
 *
 * @param[in] None
 * @param[out] hdr10Mode indicates the hdr10Mode index
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
int GetHDR10ModeIndex(const char * hdr10Mode);

/**
 * @brief This function sets the faded backlight to driver
 *
 * @param[in] from indicates the from time from when the backlight to be faded.
 * @param[in] to indicates the to time till when the backlight to be faded.
 * @param[in] duration  indicates the duration for which the backlight to be faded.
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetBacklightFade(int from,int to,int duration);

/**
 * @brief This function reads all the config modes from the file
 *
 * @param[in] file indicates the file to be read
 * @param[in] searchstring indicates the string to be searched from the file
 * @param[out] cpybuffer indicates the buffer read from the file
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t ReadAllModeConfigfile(const char *file, char *cpybuffer, const char *searchstring);


/**
 * @brief This function splits the buffer and stores the available modes from the buffer
 *
 * @param[in] buffer the buffer to be read for string splitting
 * @param[out] availableModes indicates the availableModes read from buffer after splitting it
 * @param[out] totalcount indicates the total count of the string read.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
void splitstringsfrombuffer(char *buffer, char *availableModes, unsigned short *totalcount);


/**
 * @brief This function splits the buffer and stores the available modes from the buffer
 *
 * @param[in] buffer the buffer to be read for string splitting
 * @param[out] availableModes indicates the array of availableModes read from buffer after splitting it
 * @param[out] totalcount indicates the total count of the string read.
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
void splitstringsandvaluefrombuffer(char *buffer, pic_modes_t *availableModes[], unsigned short *totalcount);

/**
 * @brief This function sets the gamma mode to driver
 *
 * @param[in] mode indicates the gamme mode to be set
 * @param[out] None
 *
 * @return Returns on success : no error
 *                 if amlTvClient is null : invalid state
 *                 in case of default : default value
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetGammaMode(int mode);

#ifdef __cplusplus
}
#endif

#endif //_TV_SETTINGS_H

/** @} */
/** @} */

