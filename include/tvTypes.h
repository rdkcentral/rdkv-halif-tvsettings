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

#ifndef _TV_TYPES_H
#define _TV_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef short int tvPictureMode_t; /** picture mode integer struct variable */
const tvPictureMode_t tvPictureMode_MAX=0xFF; /** Setting the default value of max picture mode to OXFF */

/**
* A enumeration defining the backlight modes 
*/
typedef enum {
    tvBacklightMode_NONE = 0x00, /** backlight mode - None */
    tvBacklightMode_MANUAL = 0x01, /** backlight mode - manual */
    tvBacklightMode_AMBIENT = 0x02, /** backlight mode -ambient */
    tvBacklightMode_ECO = 0x04, /** backlight mode - eco */
    tvBacklightMode_INVALID = 0x08 /** backlight mode - invalid */
}tvBacklightMode_t;

/** 
* An enumeration defining different HDR video formats 
*/
typedef enum {
    tvVideoHDRFormat_NONE= 0x00, /** HDR video format - None */
    tvVideoHDRFormat_SDR = 0x01, /** HDR video format - SDR */
    tvVideoHDRFormat_HLG = 0x02, /** HDR video format - HLG */
    tvVideoHDRFormat_HDR10 = 0x04,/** HDR video format - HDR10 */
    tvVideoHDRFormat_HDR10PLUS = 0x08,/** HDR video fomat - HDR10plus */
    tvVideoHDRFormat_DV = 0x010,/** HDR video format - DV */
}tvVideoHDRFormat_t;

/**
* An enumeration defining different video resolution values 
*/
typedef enum {
    tvVideoResolution_NONE, 
    tvVideoResolution_720x240,
    tvVideoResolution_2880x240,
    tvVideoResolution_720x288,
    tvVideoResolution_2880x288,
    tvVideoResolution_640x480,
    tvVideoResolution_720x480,
    tvVideoResolution_800x480,
    tvVideoResolution_852x480,
    tvVideoResolution_854x480,
    tvVideoResolution_1440x480,
    tvVideoResolution_2880x480,
    tvVideoResolution_960x540,
    tvVideoResolution_3840x540,
    tvVideoResolution_720x576,
    tvVideoResolution_1440x576,
    tvVideoResolution_2880x576,
    tvVideoResolution_800x600,
    tvVideoResolution_1024x600,
    tvVideoResolution_1280x600,
    tvVideoResolution_1280x720,
    tvVideoResolution_1280x1024,
    tvVideoResolution_1680x720,
    tvVideoResolution_1024x768,
    tvVideoResolution_1280x768,
    tvVideoResolution_1360x768,
    tvVideoResolution_1366x768,
    tvVideoResolution_1440x900,
    tvVideoResolution_1600x900,
    tvVideoResolution_1280x960,
    tvVideoResolution_1920x1080,
    tvVideoResolution_2560x1080,
    tvVideoResolution_3840x1080,
    tvVideoResolution_1600x1200,
    tvVideoResolution_1920x1200,
    tvVideoResolution_2160x1200,
    tvVideoResolution_2400x1200,
    tvVideoResolution_2560x1440,
    tvVideoResolution_3440x1440,
    tvVideoResolution_3840x2160,
    tvVideoResolution_4096x2160,
}tvVideoResolution_t;

/**
* A structure defining different tv resolution parameters 
*/
typedef struct {
    int frameHeight; /** frame height of the tv resolution */
    int frameWidth; /** frame width of the tv resolution */
    bool isInterlaced; /** checks whether the tv resolution is interlaced */
    tvVideoResolution_t resolutionValue; /** represents the tv resolution struct value */
}tvResolutionParam_t;

/**
* An enumeration defining different types of framerates 
*/
typedef enum {
    tvVideoFrameRate_NONE,
    tvVideoFrameRate_24,
    tvVideoFrameRate_25,
    tvVideoFrameRate_30,
    tvVideoFrameRate_50,
    tvVideoFrameRate_60,
    tvVideoFrameRate_23dot98,
    tvVideoFrameRate_29dot97,
    tvVideoFrameRate_59dot94,
}tvVideoFrameRate_t;

/**
* An enumeration defining different display modes 
*/
typedef enum {
    tvDisplayMode_4x3 = 0,
    tvDisplayMode_16x9,
    tvDisplayMode_FULL,
    tvDisplayMode_NORMAL,
    tvDisplayMode_AUTO,
    tvDisplayMode_DIRECT,
    tvDisplayMode_ZOOM,
    tvDisplayMode_MAX
}tvDisplayMode_t;

/**
* An enumeration defining different color temperature 
*/
typedef enum {
    tvColorTemp_STANDARD = 0,
    tvColorTemp_WARM,
    tvColorTemp_COLD,
    tvColorTemp_USER,
    tvColorTemp_MAX
}tvColorTemp_t;

/**
* An enum defining different wakeup source types
*/
typedef enum {
    tvWakeupSrc_VOICE = 0,
    tvWakeupSrc_PRESENCE_DETECTION,
    tvWakeupSrc_BLUETOOTH,
    tvWakeupSrc_WIFI,
    tvWakeupSrc_IR,
    tvWakeupSrc_POWER_KEY,
    tvWakeupSrc_TIMER,
    tvWakeupSrc_CEC,
    tvWakeupSrc_LAN,
    tvWakeupSrc_MAX
}tvWakeupSrcType_t;

/**
* An enumeration defining different parameters in tv data color
*/
typedef struct _tvDataColor {
     unsigned int r_gain;
     unsigned int g_gain;
     unsigned int b_gain;
     int r_offset;
     int g_offset;
     int b_offset;
}tvDataColor_t;

/**
* An enumeration defining different data color for SSM
*/
typedef struct _tvDataColorSSM {
    unsigned int en;
    int r_pre_offset;  // s11.0, range -1024~+1023, default is 0
    int g_pre_offset;  // s11.0, range -1024~+1023, default is 0
    int b_pre_offset;  // s11.0, range -1024~+1023, default is 0
    unsigned int r_gain;        // u1.10, range 0~2047, default is 1024 (1.0x)
    unsigned int g_gain;        // u1.10, range 0~2047, default is 1024 (1.0x)
    unsigned int b_gain;        // u1.10, range 0~2047, default is 1024 (1.0x)
    int r_post_offset; // s11.0, range -1024~+1023, default is 0
    int g_post_offset; // s11.0, range -1024~+1023, default is 0
    int b_post_offset; // s11.0, range -1024~+1023, default is 0
} tvDataColorSSM_t;

/**
* An enum defining different types of gains of RGB type
*/
typedef enum _tvRGBType {
    TYPE_INVALID = -1,
    R_GAIN = 0,
    G_GAIN,
    B_GAIN,
    R_POST_OFFSET,
    G_POST_OFFSET,
    B_POST_OFFSET,
    RGB_TYPE_MAX,
} tvRGBType_t;

/**
* An enum defining different component colors
*/
typedef enum {
    tvDataColor_NONE= 0,
    tvDataColor_RED = 1,
    tvDataColor_GREEN = 2,
    tvDataColor_BLUE = 4,
    tvDataColor_YELLOW = 8,
    tvDataColor_CYAN = 16,
    tvDataColor_MAGENTA = 32,
    tvDataColor_MAX = 64
}tvDataComponentColor_t;

/**
* An enum defining different content format types
*/
typedef enum {
    tvContentFormatType_NONE= 0x00,
    tvContentFormatType_SDR = 0x01,
    tvContentFormatType_HLG = 0x02,
    tvContentFormatType_HDR10 = 0x03,
    tvContentFormatType_HDR10PLUS = 0x04,
    tvContentFormatType_DOVI = 0x05,
    tvContentFormatType_MAX 
}tvContentFormatType_t;

#ifndef __VE_HDR_TYPE__
#define __VE_HDR_TYPE__
/**
* An enum defining different hdr types
*/
typedef enum tvhdr_type_e {
    HDR_TYPE_NONE      = 0,
    HDR_TYPE_HDR10     = 1,
    HDR_TYPE_HDR10PLUS = 2,
    HDR_TYPE_DOVI      = 3,
    HDR_TYPE_PRIMESL   = 4,
    HDR_TYPE_HLG       = 5,
    HDR_TYPE_SDR       = 6,
    HDR_TYPE_MVC       = 7,
    HDR_TYPE_MAX,
} tvhdr_type_t;
#endif
/**
* An enum defining different component color types
*/
typedef enum tvcomponent_color_type_e
{
    COLOR_ENABLE  = 0,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_YELLOW,
}tvcomponent_color_type_t;

/**
* An enum defining different component states
*/
typedef enum tvcomponent_state_e
{
    COMPONENT_DISABLE = 0,
    COMPONENT_ENABLE,
    COMPONENT_RESET,
}tvcomponent_state_t;

/**
* An enum defining different CMS tunel
*/
typedef enum tvCMS_tunel_e 
{
    COLOR_STATE=0,
    COLOR_HUE,
    COLOR_SATURATION,
    COLOR_LUMA
}tvCMS_tunel_t;
/**
* An enum defining different types of saving the tv source config
*/
typedef enum tvSourceSaveConfig {
    SOURCE_SAVE_FOR_ALL = 0,
    SOURCE_SAVE_FOR_INDIVIDUAL,
    SOURCE_SAVE_FOR_GROUPED ,
    SOURCE_SAVE_FOR_MAX
}tvSourceSaveConfig_t;

/**
* An enum defining the different types of saving the tv source config for various content format
*/
typedef enum tvSaveFormatsConfig {
    CONTENT_FORMAT_SAVE_FOR_ALL=0,
    CONTENT_FORMAT_SAVE_FOR_CURRENT,
    CONTENT_FORMAT_SAVE_FOR_GROUPED,
    CONTENT_FORMAT_SAVE_FOR_DV_ONLY,
    CONTENT_FORMAT_SAVE_FOR_NON_DV,
    CONTENT_FORMAT_SAVE_FOR_HDR10_ONLY,
    CONTENT_FORMAT_SAVE_FOR_HLG_ONLY,
    CONTENT_FORMAT_SAVE_MAX
}tvSaveFormatsConfig_t;

/**
* An enum defining the different types of saving the pic modes config
*/
typedef enum tvSavePicModesConfig {
    PIC_MODE_SAVE_FOR_ALL=0,
    PIC_MODE_FORMAT_SAVE_FOR_CURRENT,
    PIC_MODE_FORMAT_SAVE_MAX
}tvSavePicModesConfig_t;

/**
* An enum defining the PQ parameters Index
*/
typedef enum tvPQParameterIndex {
    PQ_PARAM_BRIGHTNESS  = 0,
    PQ_PARAM_CONTRAST  ,
    PQ_PARAM_SHARPNESS , 
    PQ_PARAM_SATURATION ,
    PQ_PARAM_BACKLIGHT  ,
    PQ_PARAM_HUE  ,
    PQ_PARAM_ASPECT_RATIO  ,
    PQ_PARAM_CMS  ,
    PQ_PARAM_DOLBY_MODE,
    PQ_PARAM_COLOR_TEMPERATURE	,
    PQ_PARAM_LDIM,
    PQ_PARAM_HDR10_MODE,
    PQ_PARAM_HLG_MODE
}tvPQParameterIndex_t;

/**
* An enum defining the various dolby modes
*/
typedef enum {
    tvDolbyMode_Dark=0,
    tvDolbyMode_Bright,
    tvHDR10Mode_Dark=3,
    tvHDR10Mode_Bright,
    tvHLGMode_Dark=6,
    tvHLGMode_Bright,
    tvMode_Max = 28
}tvDolbyMode_t;

/**
* An enum defining the different dimming modes
*/
typedef enum {
  tvDimmingMode_Fixed=0,
  tvDimmingMode_Local,
  tvDimmingMode_Global
}tvDimmingMode_t;

#ifdef __cplusplus
}
#endif

#endif //_TV_TYPES_H
