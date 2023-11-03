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
* @defgroup TV_Types_H TV Types Header
* @{
**/

#ifndef _TV_TYPES_H
#define _TV_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef short int tvPictureMode_t;             //!< Picture mode struct variable 
const tvPictureMode_t tvPictureMode_MAX=0xFF;  //!< Setting the default value of max picture mode to OXFF 

/**
 * Enumeration defining the supported FMM modes
 *
 */
typedef enum
{
    tvContentType_NONE= 0x00,
    tvContentType_FMM = 0x01,
}tvContentType_t;

/**
 * Enumeration defining the supported backlight modes
 * 
 */
typedef enum
{
    tvBacklightMode_NONE = 0x00,               //!< No backlight
    tvBacklightMode_MANUAL = 0x01,             //!< backlight mode is manual
    tvBacklightMode_AMBIENT = 0x02,            //!< backlight mode is ambient
    tvBacklightMode_ECO = 0x04,                //!< backlight mode is eco
    tvBacklightMode_INVALID = 0x08            //!< backlight mode is invalid
}tvBacklightMode_t;

typedef enum
{
    tvVideoHDRFormat_NONE= 0x00,                  //!< No video format 
    tvVideoHDRFormat_SDR = 0x01,                  //!< video format is SDR 
    tvVideoHDRFormat_HLG = 0x02,                  //!< video format is HLG 
    tvVideoHDRFormat_HDR10 = 0x04,                //!< video format is HDR10 
    tvVideoHDRFormat_HDR10PLUS = 0x08,            //!< video format is HDR10plus 
    tvVideoHDRFormat_DV = 0x010                  //!< video format is DV 
}tvVideoHDRFormat_t;

/**
 *  Enumeration defining supported video resolution values 
 */
typedef enum
{
    tvVideoResolution_NONE,                    //!< No Resolution
    tvVideoResolution_720x240,                 //!< Resolution is 720x240
    tvVideoResolution_2880x240,                //!< Resolution is 2880x240
    tvVideoResolution_720x288,                 //!< Resolution is 720x288
    tvVideoResolution_2880x288,                //!< Resolution is 2880x288
    tvVideoResolution_640x480,                 //!< Resolution is 640x480
    tvVideoResolution_720x480,                 //!< Resolution is 720x480
    tvVideoResolution_800x480,                 //!< Resolution is 800x48
    tvVideoResolution_852x480,                 //!< Resolution is 852x480
    tvVideoResolution_854x480,                 //!< Resolution is 854x480
    tvVideoResolution_1440x480,                //!< Resolution is 1440x480
    tvVideoResolution_2880x480,                //!< Resolution is 2880x480
    tvVideoResolution_960x540,                 //!< Resolution is 960x540
    tvVideoResolution_3840x540,                //!< Resolution is 3840x540
    tvVideoResolution_720x576,                 //!< Resolution is 720x576
    tvVideoResolution_1440x576,                //!< Resolution is 1440x576
    tvVideoResolution_2880x576,                //!< Resolution is 2880x576
    tvVideoResolution_800x600,                 //!< Resolution is 800x600
    tvVideoResolution_1024x600,                //!< Resolution is 1024x600
    tvVideoResolution_1280x600,                //!< Resolution is 1280x600
    tvVideoResolution_1280x720,                //!< Resolution is 1280x720
    tvVideoResolution_1280x1024,               //!< Resolution is 1280x1024
    tvVideoResolution_1680x720,                //!< Resolution is 1680x720
    tvVideoResolution_1024x768,                //!< Resolution is 1024x768
    tvVideoResolution_1280x768,                //!< Resolution is 1280x768
    tvVideoResolution_1360x768,                //!< Resolution is 1360x768
    tvVideoResolution_1366x768,                //!< Resolution is 1366x76
    tvVideoResolution_1440x900,                //!< Resolution is 1440x900
    tvVideoResolution_1600x900,                //!< Resolution is 1600x900
    tvVideoResolution_1280x960,                //!< Resolution is 1280x960
    tvVideoResolution_1920x1080,               //!< Resolution is 1920x1080
    tvVideoResolution_2560x1080,               //!< Resolution is 2560x1080
    tvVideoResolution_3840x1080,               //!< Resolution is 3840x1080
    tvVideoResolution_1600x1200,               //!< Resolution is 1600x1200
    tvVideoResolution_1920x1200,               //!< Resolution is 1920x1200
    tvVideoResolution_2160x1200,               //!< Resolution is 2160x1200
    tvVideoResolution_2400x1200,               //!< Resolution is 2400x1200
    tvVideoResolution_2560x1440,               //!< Resolution is 2560x1440
    tvVideoResolution_3440x1440,               //!< Resolution is 3440x1440
    tvVideoResolution_3840x2160,               //!< Resolution is 3840x2160
    tvVideoResolution_4096x2160                //!< Resolution is 4096x2160
}tvVideoResolution_t;

/**
 * Structure for TV resolution parameters 
 */
typedef struct
{
    int frameHeight;                            //!< Frame height of the TV resolution
    int frameWidth;                             //!< Frame width of the TV resolution 
    bool isInterlaced;                          //!< Checks whether the TV resolution is interlaced
    tvVideoResolution_t resolutionValue;        //!< Represents the struct TV resolution value
}tvResolutionParam_t;

/**
 *  Enumeration defining supported types of frame rates 
 */
typedef enum
{
    tvVideoFrameRate_NONE,                      //!< No frame rate
    tvVideoFrameRate_24,                        //!< Frame rate is 24
    tvVideoFrameRate_25,                        //!< Frame rate is 25
    tvVideoFrameRate_30,                        //!< Frame rate is 30
    tvVideoFrameRate_50,                        //!< Frame rate is 50
    tvVideoFrameRate_60,                        //!< Frame rate is 60
    tvVideoFrameRate_23dot98,                   //!< Frame rate is 23.98
    tvVideoFrameRate_29dot97,                   //!< Frame rate is 29.97
    tvVideoFrameRate_59dot94                   //!< Frame rate is 59.94
}tvVideoFrameRate_t;

/**
 *  Enumeration defining supported display modes 
 */
typedef enum
{
    tvDisplayMode_4x3 = 0,                      //!< Display mode is 4x3
    tvDisplayMode_16x9,                         //!< Display mode is 16x9
    tvDisplayMode_FULL,                         //!< Display mode is Full
    tvDisplayMode_NORMAL,                       //!< Display mode is Normal
    tvDisplayMode_AUTO,                         //!< Display mode is Auto
    tvDisplayMode_DIRECT,                       //!< Display mode is Direct
    tvDisplayMode_ZOOM,                          //!< Display mode is Zoom
    tvDisplayMode_MAX                           //!< End of enum
}tvDisplayMode_t;

/**
 * Enumeration defining supported color temperature 
 */
typedef enum
{
    tvColorTemp_STANDARD = 0,                   //!< Color Temperature is Standard
    tvColorTemp_WARM,                           //!< Color Temperature is Warm
    tvColorTemp_COLD,                           //!< Color Temperature is Cold
    tvColorTemp_USER,                           //!< User defined color temperature
    tvColorTemp_MAX                             //!< End of enum
}tvColorTemp_t;

/**
 * Enumeration defining supported wakeup source types 
 */
typedef enum
{
    tvWakeupSrc_VOICE = 0,                     //!< Wake up source is Voice
    tvWakeupSrc_PRESENCE_DETECTION,            //!< Wake up source is Presence detection
    tvWakeupSrc_BLUETOOTH,                     //!< Wake up source is bluetooth
    tvWakeupSrc_WIFI,                          //!< Wake up source is Wifi
    tvWakeupSrc_IR,                            //!< Wake up source is IR
    tvWakeupSrc_POWER_KEY,                     //!< Wake up source is Powerkey
    tvWakeupSrc_TIMER,                         //!< Wake up source is Timer
    tvWakeupSrc_CEC,                           //!< Wake up source is CEC
    tvWakeupSrc_LAN,                           //!< Wake up source is LAN
    tvWakeupSrc_MAX                            //!< End of enum
}tvWakeupSrcType_t;

/**
 * Structure defining supported parameters in tv color
 */
typedef struct _tvDataColor
{
     unsigned int r_gain;                       //!< Color Data is r_gain
     unsigned int g_gain;                       //!< Color Data is g_gain
     unsigned int b_gain;                       //!< Color Data is b_gain
     int r_offset;                              //!< Color Data is r_offset
     int g_offset;                              //!< Color Data is g_offset
     int b_offset;                              //!< Color Data is b_offset
}tvDataColor_t;

/**
 * Structure defining supported parameters in SSM color 
 */
typedef struct _tvDataColorSSM
{
    unsigned int en;                           //!< Enable value
    int r_pre_offset;                          //!< Red pre offset
    int g_pre_offset;                          //!< Green pre offset
    int b_pre_offset;                          //!< Blue pre offset
    unsigned int r_gain;                       //!< Red gain
    unsigned int g_gain;                       //!< Green gain
    unsigned int b_gain;                       //!< Bue gain
    int r_post_offset;                         //!< Red post offset
    int g_post_offset;                         //!< Green post offset
    int b_post_offset;                         //!< Blue post offset
} tvDataColorSSM_t;

/**
 * Enumeration defining supported RGB values 
 */
typedef enum _tvRGBType
{
    TYPE_INVALID = -1,                          //!< RGB type is invalid
    R_GAIN = 0,                                 //!< RGB type is RGain
    G_GAIN,                                     //!< RGB type is GGain
    B_GAIN,                                     //!< RGB type is BGain
    R_POST_OFFSET,                              //!< RGB type is ROffset
    G_POST_OFFSET,                              //!< RGB type is GOffset
    B_POST_OFFSET,                              //!< RGB type is BOffset
    RGB_TYPE_MAX                               //!< End of enum
} tvRGBType_t;

/**
 * Enumeration defining supported TV component colors 
 */
typedef enum
{
    tvDataColor_NONE= 0,                        //!< No color
    tvDataColor_RED = 1,                        //!< Color is Red
    tvDataColor_GREEN = 2,                      //!< Color is Green
    tvDataColor_BLUE = 4,                       //!< Color is Blue
    tvDataColor_YELLOW = 8,                     //!< Color is Yellow
    tvDataColor_CYAN = 16,                      //!< Color is Cyan
    tvDataColor_MAGENTA = 32,                   //!< Color is Megenta
    tvDataColor_MAX = 64                        //!< End of enum
}tvDataComponentColor_t;

/**
 * Enumeration defining supported conent format type 
 */
typedef enum
{
    tvContentFormatType_NONE= 0x00,             //!< No Content Format
    tvContentFormatType_SDR = 0x01,             //!< Content Format type is SDR
    tvContentFormatType_HLG = 0x02,             //!< Content Format type is HLG
    tvContentFormatType_HDR10 = 0x03,           //!< Content Format type is HDR10
    tvContentFormatType_HDR10PLUS = 0x04,       //!< Content Format type is HDR10PLUS
    tvContentFormatType_DOVI = 0x05,            //!< Content Format type is DOVI
    tvContentFormatType_MAX                     //!< End of enum
}tvContentFormatType_t;

#ifndef __VE_HDR_TYPE__
#define __VE_HDR_TYPE__

/** 
 * Enumeration defining supported hdr types 
 */
typedef enum tvhdr_type_e
{
    HDR_TYPE_NONE      = 0,                     //!< No HDR Type
    HDR_TYPE_HDR10     = 1,                     //!< HDR Type is HDR10
    HDR_TYPE_HDR10PLUS = 2,                     //!< HDR Type is HDR10PLUS
    HDR_TYPE_DOVI      = 3,                     //!< HDR Type is DOVI
    HDR_TYPE_PRIMESL   = 4,                     //!< HDR Type is PRIMESL
    HDR_TYPE_HLG       = 5,                     //!< HDR Type is HLG
    HDR_TYPE_SDR       = 6,                     //!< HDR Type is SDR
    HDR_TYPE_MVC       = 7,                     //!< HDR Type is MVC
    HDR_TYPE_MAX                               //!< End of enum
} tvhdr_type_t;
#endif // __VE_HDR_TYPE__

/** 
 * Enumeration defining supported component color types 
 */
typedef enum
{
    COLOR_ENABLE  = 0,                          //!< Color is Enable
    COLOR_RED,                                  //!< Color is Red
    COLOR_GREEN,                                //!< Color is Green
    COLOR_BLUE,                                 //!< Color is Blue
    COLOR_CYAN,                                 //!< Color is Cyan
    COLOR_MAGENTA,                              //!< Color is Megenta
    COLOR_YELLOW                               //!< Color is Yellow
}tvcomponent_color_type_t;

/**
 * Enumeration defining supported component states 
 */
typedef enum
{
    COMPONENT_DISABLE = 0,                      //!< State is Disable
    COMPONENT_ENABLE,                           //!< State is Enable
    COMPONENT_RESET                            //!< State is Reset
}tvcomponent_state_t;

/** 
 * Enumeration defining supported CMS tunel 
 */
typedef enum
{
    COLOR_STATE=0,                              //!< CMS tunel is State
    COLOR_HUE,                                  //!< CMS tunel is Hue
    COLOR_SATURATION,                           //!< CMS tunel is Saturation
    COLOR_LUMA                                 //!< CMS tunel is Luma
}tvCMS_tunel_t;

/**
 * Enumeration defining supported source save types 
 */
typedef enum tvSourceSaveConfig
{
    SOURCE_SAVE_FOR_ALL = 0,                    //!< Save type is save all
    SOURCE_SAVE_FOR_INDIVIDUAL,                 //!< Save type is save individual
    SOURCE_SAVE_FOR_GROUPED ,                   //!< Save type is save grouped
    SOURCE_SAVE_FOR_MAX                         //!< End of enum
}tvSourceSaveConfig_t;

/**
 * Enumeration defining supported content format save types 
 */
typedef enum tvSaveFormatsConfig
{
    CONTENT_FORMAT_SAVE_FOR_ALL=0,              //!< Save type is save all
    CONTENT_FORMAT_SAVE_FOR_CURRENT,            //!< Save type is save current format
    CONTENT_FORMAT_SAVE_FOR_GROUPED,            //!< Save type is save grouped format
    CONTENT_FORMAT_SAVE_FOR_DV_ONLY,            //!< Save type is save DV format
    CONTENT_FORMAT_SAVE_FOR_NON_DV,             //!< Save type is save non DV format
    CONTENT_FORMAT_SAVE_FOR_HDR10_ONLY,         //!< Save type is save HDR10 format
    CONTENT_FORMAT_SAVE_FOR_HLG_ONLY,           //!< Save type is save HLG format
    CONTENT_FORMAT_SAVE_MAX                     //!< End of enum
}tvSaveFormatsConfig_t;

/** 
 * Enumeration defining supported picture mode save types 
 */
typedef enum tvSavePicModesConfig
{
    PIC_MODE_SAVE_FOR_ALL=0,                   //!< Save type is save all
    PIC_MODE_FORMAT_SAVE_FOR_CURRENT,          //!< Save type is save current
    PIC_MODE_FORMAT_SAVE_MAX                   //!< End of enum
}tvSavePicModesConfig_t;

/** 
 * Enumeration defining supported PQ params 
 */
typedef enum tvPQParameterIndex
{
    PQ_PARAM_BRIGHTNESS  = 0,                  //!< Param is brightness
    PQ_PARAM_CONTRAST  ,                       //!< Param is contrast
    PQ_PARAM_SHARPNESS ,                       //!< Param is sharpness
    PQ_PARAM_SATURATION ,                      //!< Param is saturation
    PQ_PARAM_BACKLIGHT  ,                      //!< Param is backlight
    PQ_PARAM_HUE  ,                            //!< Param is hue
    PQ_PARAM_ASPECT_RATIO  ,                   //!< Param is aspect ratio
    PQ_PARAM_CMS  ,                            //!< Param is CMS
    PQ_PARAM_DOLBY_MODE,                       //!< Param is dolby mode
    PQ_PARAM_COLOR_TEMPERATURE	,              //!< Param is color temperature
    PQ_PARAM_LDIM,                             //!< Param is LDIM
    PQ_PARAM_HDR10_MODE,                       //!< Param is HDR10
    PQ_PARAM_HLG_MODE,                         //!< Param is HLG
    PQ_PARAM_LOCALDIMMING_LEVEL,               //!< Param is local dimming level
    PQ_PARAM_LOWLATENCY_STATE,                 //!< Param is low latency state
    PQ_PARAM_DIMMINGMODE                       //!< Param is dimming mode
}tvPQParameterIndex_t;

/**
 *  Enumeration defining the various supported dolby modes 
 */
typedef enum
{
    tvDolbyMode_Dark=0,                         //!< Dolby mode is Dark
    tvDolbyMode_Bright,                         //!< Dolby mode is Bright
    tvHDR10Mode_Dark=3,                         //!< HDR1HLG mode is Gamede Dark
    tvHDR10Mode_Bright,                         //!< HDR10 mode is bright
    tvHLGMode_Dark=6,                           //!< HLG mode is Dark
    tvHLGMode_Bright,                           //!< HLG mode is Bright
    tvDolbyMode_Game=9,                         //!< Dolby mode is Game
    tvHDR10Mode_Game,                           //!< HDR10 mode is Game
    tvHLGMode_Game,                             //!< End of enum
    tvMode_Max = 28
}tvDolbyMode_t;


/**
 * Enumeration defining the supported dimming modes 
 */
typedef enum
{
  tvDimmingMode_Fixed=0,                        //!< Mode is Fixed
  tvDimmingMode_Local,                          //!< Mode is Local
  tvDimmingMode_Global                         //!< Mode is Global
}tvDimmingMode_t;


#ifndef __TV_SOURCE_INPUT__
#define __TV_SOURCE_INPUT__
/**
 * Enumeration defining supported source types 
 */

typedef enum tv_source_input_e
{
    SOURCE_INVALID = -1,                //!< Source is all
    SOURCE_TV = 0,                      //!< Source is TV
    SOURCE_AV1,                         //!< Source is AV1
    SOURCE_AV2,                         //!< Source is AV2
    SOURCE_YPBPR1,                      //!< Source is YPBPR1
    SOURCE_YPBPR2,                      //!< Source is YPBPR1
    SOURCE_HDMI1,                       //!< Source is HDMI1
    SOURCE_HDMI2,                       //!< Source is HDMI2
    SOURCE_HDMI3,                       //!< Source is HDMI3
    SOURCE_HDMI4,                       //!< Source is HDMI4
    SOURCE_VGA,                         //!< Source is VGA
    SOURCE_MPEG,                        //!< Source is MPEG
    SOURCE_DTV,                         //!< Source is DTV
    SOURCE_SVIDEO,                      //!< Source is SVIDEO
    SOURCE_IPTV,                        //!< Source is IPTV
    SOURCE_DUMMY,                       //!< Source is DUMMY
    SOURCE_SPDIF,                       //!< Source is SPDIF
    SOURCE_ADTV,                        //!< Source is ADTV
    SOURCE_MAX                          //!< End of enum
}tv_source_input_t;

#endif

#ifdef __cplusplus
}
#endif

#endif //_TV_TYPES_H

/** @} */ // End of TV_Types_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
