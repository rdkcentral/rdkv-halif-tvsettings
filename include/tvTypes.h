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
* @defgroup TV_Types_H TV Types Header
* @{
**/


#ifndef _TV_TYPES_H
#define _TV_TYPES_H

#include "tvTypesODM.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define PIC_MODES_SUPPORTED_MAX   (15)      //!< Defines the maximum pic modes supported
#define PIC_MODE_NAME_MAX (25)              //!< Defines the maximum picture mode name length
#define VIDEO_SRC_NAME_MAX (25)
#define VIDEO_FORMAT_NAME_MAX (25)
#define DIMMING_MODE_NAME_SIZE    (25)      //!< Defines the maximum mode name size
#define DIMMING_MODE_MAX          (10)      //!< Defines the maximum dimming mode

#define GAIN_MIN         (0)                //!< Defines the minimum gain value
#define GAIN_MAX         (2047)             //!< Defines the maximum gain value
#define OFFSET_MIN       (-1024)            //!< Defines the minimum offset value
#define OFFSET_MAX       (1024)             //!< Defines the maximum offset value

/**
 * @brief Enumeration defining the supported FMM modes
 *
 */
typedef enum
{
    tvContentType_NONE= 0x00,                 //!< Content type is NONE
    tvContentType_FMM = 0x01,                 //!< Content type is FMM
    tvContentType_MAX                         //!< End of enum
}tvContentType_t;

/**
 * @brief Enumeration defining the supported backlight modes
 * 
 */
typedef enum
{
    tvBacklightMode_NONE = 0x00,               //!< No backlight
    tvBacklightMode_MANUAL = 0x01,             //!< backlight mode is manual
    tvBacklightMode_AMBIENT = 0x02,            //!< backlight mode is ambient
    tvBacklightMode_ECO = 0x04,                //!< backlight mode is eco
    tvBacklightMode_INVALID = 0x08,            //!< backlight mode is invalid
    tvBacklightMode_MAX = 0x10                 //!< End of enum
}tvBacklightMode_t;

/**
 * @brief Enumeration defining the supported video format types
 *
 */
typedef enum tvVideoFormatType_e {
    VIDEO_FORMAT_NONE  	   = 0,                 //!< No video format
    VIDEO_FORMAT_HDR10,                         //!< Video format is HDR10
    VIDEO_FORMAT_HDR10PLUS,                     //!< Video format is HDR10 plus
    VIDEO_FORMAT_DV,                            //!< Video format is Dolby Vision
    VIDEO_FORMAT_PRIMESL,                       //!< Video format is PRIMESL
    VIDEO_FORMAT_HLG,                           //!< Video format is HLG
    VIDEO_FORMAT_SDR,                           //!< Video format is SDR
    VIDEO_FORMAT_MVC,                           //!< Video format is MVC
    VIDEO_FORMAT_MAX                            //!< End of enum
} tvVideoFormatType_t;

/**
 * @brief Enumeration defining the supported source offset
 *
 */
typedef enum tvColorTempSourceOffset_e {
    ALL_SRC_OFFSET = -1,        //!< Video source offset is all
    HDMI_OFFSET    = 0,         //!< Video source offset HDMI and tuner
    TV_OFFSET      = 1,         //!< Video source offset IP
    AV_OFFSET      = 2,         //!< Video source offset Composite
    MAX_OFFSET     = 3          //!< End of enum.
} tvColorTempSourceOffset_t;

/**
 * @brief Enumeration defining the supported video source types
 *
 */
typedef enum tvVideoSrcType_e {
    VIDEO_SOURCE_ALL        = -1,               //!< Video source is All
    VIDEO_SOURCE_ANALOGUE = 0,                  //!< Video source is Analogue
    VIDEO_SOURCE_COMPOSITE1,                    //!< Video source is Composite1
    VIDEO_SOURCE_COMPOSITE2,                    //!< Video source is Composite2
    VIDEO_SOURCE_YPBPR1,                        //!< Video source is YPbPr1
    VIDEO_SOURCE_YPBPR2,                        //!< Video source is YPbPr2
    VIDEO_SOURCE_HDMI1,                         //!< Video source is HDMI1
    VIDEO_SOURCE_HDMI2,                         //!< Video source is HDMI2
    VIDEO_SOURCE_HDMI3,                         //!< Video source is HDMI3
    VIDEO_SOURCE_HDMI4,                         //!< Video source is HDMI4
    VIDEO_SOURCE_VGA,                           //!< Video source is VGA
    VIDEO_SOURCE_IP,                            //!< Video source is IP
    VIDEO_SOURCE_TUNER,                         //!< Video source is Tuner
    VIDEO_SOURCE_SVIDEO,                        //!< Video source is SVideo
    VIDEO_SOURCE_RESERVED,                      //!< Video source reserved
    VIDEO_SOURCE_RESERVED1,                     //!< Video source reserved
    VIDEO_SOURCE_RESERVED2,                     //!< Video source reserved
    VIDEO_SOURCE_RESERVED3,                     //!< Video source reserved
    VIDEO_SOURCE_MAX                            //!< End of enum.
} tvVideoSrcType_t;

/**
 *  @brief Enumeration defining supported video resolution values
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
    tvVideoResolution_800x480,                 //!< Resolution is 800x480
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
    tvVideoResolution_1366x768,                //!< Resolution is 1366x768
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
    tvVideoResolution_4096x2160,               //!< Resolution is 4096x2160
    tvVideoResolution_MAX                      //!< End of enum
}tvVideoResolution_t;

/**
 *  @brief Enumeration defining supported types of frame rates
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
    tvVideoFrameRate_59dot94,                   //!< Frame rate is 59.94
    tvVideoFrameRate_MAX                        //!< End of enum
}tvVideoFrameRate_t;

/**
 *  @brief Enumeration defining supported display modes
 */
typedef enum
{
    tvDisplayMode_4x3 = 0,                      //!< Display mode is 4x3
    tvDisplayMode_16x9,                         //!< Display mode is 16x9
    tvDisplayMode_FULL,                         //!< Display mode is Full
    tvDisplayMode_NORMAL,                       //!< Display mode is Normal
    tvDisplayMode_AUTO,                         //!< Display mode is Auto
    tvDisplayMode_DIRECT,                       //!< Display mode is Direct
    tvDisplayMode_ZOOM,                         //!< Display mode is Zoom
    tvDisplayMode_MAX                           //!< End of enum
}tvDisplayMode_t;

/**
 * @brief Enumeration defining supported color temperature
 *
 * #TODO: This enum list will be deprecated, no further extensions can take place, 
 *         It will be replaced by a picture mode string list, that can be defined by a "well-known name" to allow future scaling. 
 */
 typedef enum {
    tvColorTemp_STANDARD = 0,                   //!< Color Temperature is Standard
    tvColorTemp_WARM,                           //!< Color Temperature is Warm
    tvColorTemp_COLD,                           //!< Color Temperature is Cold
    tvColorTemp_USER,                           //!< User defined color temperature
    tvColorTemp_BOOST_STANDARD,                 //!< Color Temperature is Standard for boost mode
    tvColorTemp_BOOST_WARM,                     //!< Color Temperature is Warm for boost mode
    tvColorTemp_BOOST_COLD,                     //!< Color Temperature is Cold for boost mode
    tvColorTemp_BOOST_USER,                     //!< User defined color temperature for boost mode
    tvColorTemp_SUPERCOLD,                      //!< Color Temperature is Supercold
    tvColorTemp_BOOST_SUPERCOLD,                //!< Color Temperature is Supercold for boost mode
    tvColorTemp_MAX                             //!< End of enum    
}tvColorTemp_t;

/**
 * @brief Enumeration defining supported wakeup source types
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
 * @brief Enumeration defining supported RGB values
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
    RGB_TYPE_MAX                                //!< End of enum
} tvRGBType_t;

/**
 * @brief Enumeration defining supported TV component colors
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
 * @brief Enumeration defining the supported component types
 *
 */
typedef enum tvComponentType_e 
{
    COMP_NONE=0,                                //!< No Component
    COMP_HUE,                                   //!< Component is Hue
    COMP_SATURATION,                            //!< Component is Saturation
    COMP_LUMA,                                  //!< Component is Luma
    COMP_MAX                                    //!< End of enum
}tvComponentType_t;

/**
 * @brief Enumeration defining the supported PQ mode types
 *
 */
typedef enum tvPQModeIndex {
    PQ_MODE_INVALID  = -1,                      //!< Picture mode is Invalid
    PQ_MODE_STANDARD  = 0,                      //!< Picture mode is "Standard" or "Entertainment" */
    PQ_MODE_VIVID =1 ,                          //!< Picture mode is "Vivid" or "Dynamic" */
    PQ_MODE_ENERGY_SAVING =2,                   //!< Picture mode is "Energysaving" */
    PQ_MODE_CUSTOM =3,                          //!< Picture mode is "Custom" or "Expert" */
    PQ_MODE_THEATER =4 ,                        //!< Picture mode is "Theater" or "Movie" */
    PQ_MODE_RESERVED1 =5 ,                      //!< Picture mode is Reserved */
    PQ_MODE_RESERVED2 =6 ,                      //!< Picture mode is Reserved */
    PQ_MODE_GAME =7,                            //!< Picture mode is "Game" */
    PQ_MODE_SPORTS =8 ,                         //!< Picture mode is "Sports" */
    PQ_MODE_GRAPHICS =9 ,                       //!< Picture mode is "Graphics" */
    PQ_MODE_FMM =10,                            //!< Picture mode is "Filmmaker" */
    PQ_MODE_VIVID2 =11,                         //!< Picture mode is "Vivid2 or Dynamic2" */
    PQ_MODE_AIPQ =12,                           //!< Picture mode is "AIPQ" */
    PQ_MODE_DARK = 13,                          //!< Picture mode is "Dark" */
    PQ_MODE_BRIGHT = 14,                        //!< Picture mode is "Bright" */
    PQ_MODE_DVIQ = 15,                          //!< Picture mode is "DV IQ" */
    PQ_MODE_MAX=16                              //!< End of enum
}tvPQModeIndex_t;

/**
 * @brief Enumeration defining the supported PQ param types
 *
 */
typedef enum tvPQParameterIndex {
    PQ_PARAM_BRIGHTNESS  = 0,                   //!< Picture parameter is Brightness
    PQ_PARAM_CONTRAST,                          //!< Picture parameter is Contrast
    PQ_PARAM_SHARPNESS,                         //!< Picture parameter is Sharpness
    PQ_PARAM_SATURATION,                        //!< Picture parameter is Saturation
    PQ_PARAM_HUE,                               //!< Picture parameter is Hue
    PQ_PARAM_BACKLIGHT,                         //!< Picture parameter is Backlight
    PQ_PARAM_DOLBY_MODE,                        //!< Picture parameter is Dolby Mode
    PQ_PARAM_HDR10_MODE,                        //!< Picture parameter is HDR10 mode. To be deprecated
    PQ_PARAM_HLG_MODE,                          //!< Picture parameter is HLG mode. To be deprecated
    PQ_PARAM_ASPECT_RATIO,                      //!< Picture parameter is Aspect ratio
    PQ_PARAM_COLOR_TEMPERATURE,                 //!< Picture parameter is Colour temperature
    PQ_PARAM_DIMMINGMODE,                       //!< Picture parameter is Dimming mode
    PQ_PARAM_LDIM,                               //!< Picture parameter is LDIM. To be deprecated 
    PQ_PARAM_LOCALDIMMING_LEVEL,                //!< Picture parameter is Local dimming level
    PQ_PARAM_LOWLATENCY_STATE,                  //!< Picture parameter is Low latency state
    PQ_PARAM_CMS,                               //!< Picture parameter is CMS. To be deprecated
    PQ_PARAM_CMS_STATE,                         //!< Picture parameter is CMS. To be deprecated
    PQ_PARAM_CMS_SATURATION_RED,                //!< Picture parameter is Component saturation red
    PQ_PARAM_CMS_SATURATION_BLUE,               //!< Picture parameter is Component saturation blue
    PQ_PARAM_CMS_SATURATION_GREEN,              //!< Picture parameter is Component saturation green
    PQ_PARAM_CMS_SATURATION_YELLOW,              //!< Picture parameter is Component saturation yellow
    PQ_PARAM_CMS_SATURATION_CYAN,               //!< Picture parameter is Component saturation cyan
    PQ_PARAM_CMS_SATURATION_MAGENTA,            //!< Picture parameter is Component saturation magenta
    PQ_PARAM_CMS_HUE_RED,                       //!< Picture parameter is Component hue red
    PQ_PARAM_CMS_HUE_BLUE,                      //!< Picture parameter is Component hue blue
    PQ_PARAM_CMS_HUE_GREEN,                     //!< Picture parameter is Component hue green
    PQ_PARAM_CMS_HUE_YELLOW,                     //!< Picture parameter is Component hue yellow
    PQ_PARAM_CMS_HUE_CYAN,                      //!< Picture parameter is Component hue cyan
    PQ_PARAM_CMS_HUE_MAGENTA,                   //!< Picture parameter is Component hue magenta
    PQ_PARAM_CMS_LUMA_RED,                      //!< Picture parameter is Component luma red
    PQ_PARAM_CMS_LUMA_BLUE,                     //!< Picture parameter is Component luma blue
    PQ_PARAM_CMS_LUMA_GREEN,                    //!< Picture parameter is Component luma green
    PQ_PARAM_CMS_LUMA_YELLOW,                    //!< Picture parameter is Component luma yellow
    PQ_PARAM_CMS_LUMA_CYAN,                     //!< Picture parameter is Component luma cyan
    PQ_PARAM_CMS_LUMA_MAGENTA,                  //!< Picture parameter is Component luma magenta
	PQ_PARAM_WB_GAIN_RED,                       //!< Picture parameter is Component Red Gain
    PQ_PARAM_WB_GAIN_GREEN,                     //!< Picture parameter is Component Green Gain
    PQ_PARAM_WB_GAIN_BLUE,                      //!< Picture parameter is Component Blue Gain
    PQ_PARAM_WB_OFFSET_RED,                     //!< Picture parameter is Component Red Offset
    PQ_PARAM_WB_OFFSET_GREEN,                   //!< Picture parameter is Component Green Offset
    PQ_PARAM_WB_OFFSET_BLUE,                    //!< Picture parameter is Component Blue Offset
    PQ_PARAM_PRECISION_DETAIL,                 //!< Picture parameter is Precision Detail
    PQ_PARAM_SDR_GAMMA,                        //!< Picture parameter is SDR Gamma
    PQ_PARAM_LOCAL_CONTRAST_ENHANCEMENT,       //!< Picture parameter is Local Contrast Enhancement
    PQ_PARAM_MPEG_NOISE_REDUCTION,             //!< Picture parameter is MPEG Noise Reduction
    PQ_PARAM_DIGITAL_NOISE_REDUCTION,          //!< Picture parameter is Digital Noise Reduction
    PQ_PARAM_AI_SUPER_RESOLUTION,              //!< Picture parameter is AI Super Resolution
    PQ_PARAM_MEMC,                             //!< Picture parameter is MEMC
    PQ_PARAM_MULTI_POINT_WB,                   //!< Picture parameter is Multi-Point WB
    PQ_PARAM_DOLBY_VISION_CALIBRATION,         //!< Picture parameter is Dolby Vision Calibration
    PQ_PARAM_MAX                               //!< End of enum
}tvPQParameterIndex_t;

/**
 *  @brief Enumeration defining the various supported dolby modes
 *  This enum will be deprecated and switched to tvPQModeIndex_t
 */
 typedef enum {
    tvDolbyMode_Invalid = -1,           //!< Dolby mode is invalid
    tvDolbyMode_Dark = 0,               //!< Dolby mode is Dolby Dark
    tvDolbyMode_Bright,                 //!< Dolby mode is Dolby Bright
    tvDolbyMode_Game,                   //!< Dolby mode is Dolby Game
    tvHDR10Mode_Dark,                   //!< Dolby mode is HDR10 Dark
    tvHDR10Mode_Bright,                 //!< Dolby mode is HDR10 Bright
    tvHDR10Mode_Game,                   //!< Dolby mode is HDR10 Game
    tvHLGMode_Dark,                     //!< Dolby mode is HLG Dark
    tvHLGMode_Bright,                   //!< Dolby mode is HLG Bright
    tvHLGMode_Game,                     //!< Dolby mode is HLG Game
    tvMode_Max = 28                     //!< End of enum
}tvDolbyMode_t;

/**
 * @brief Enumeration defining the supported dimming modes
 */
typedef enum
{
  tvDimmingMode_Fixed=0,                 //!< Dimming Mode is Fixed
  tvDimmingMode_Local,                   //!< Dimming Mode is Local
  tvDimmingMode_Global,                  //!< Dimming Mode is Global
  tvDimmingMode_MAX                      //!< End of enum
}tvDimmingMode_t;


/**
 * @brief Enumeration defining the supported LDIM states
 *
 */
typedef enum _ldimStateLevel
{
    LDIM_STATE_NONBOOST = 0,            //!< LDIM state level is non boost (AKA Normal)
    LDIM_STATE_BOOST,                   //!< LDIM state level is boost
    LDIM_STATE_BURST,                   //!< LDIM state level is burst
    LDIM_STATE_MAX,                     //!< End of enum
} ldimStateLevel_t;

/**
 * @brief Enumeration defining the supported backlight test modes
 *
 */
typedef enum tvBacklightTestMode_s{
    tvBacklightTestMode_Normal = 0,     //!< Backlight test mode is normal
    tvBacklightTestMode_Boost,          //!< Backlight test mode is boost
    tvBacklightTestMode_Burst,          //!< Backlight test mode is burst
    tvBacklightTestMode_Reset,          //!< Backlight test mode is reset
    tvBacklightTestMode_Max             //!< End of enum
}tvBacklightTestMode_t;

/**
 * @brief Callback for tvVideoFormatChangeCB
 *
 * This callback is triggered when a video format change is encountered.
 *
 * @param[in] format   			- Type of content format. Valid values will be member of ::tvVideoFormatType_t
 * @param[in] userData 			- Data of the content
 *
 */
typedef void (*tvVideoFormatChangeCB)(tvVideoFormatType_t format,void *userData);


/**
 * @brief Callback for tvVideoContentChangeCB
 *
 * This callback is triggered when a video content change is encountered.
 *
 * @param[in] mode                      - Types of FMM mode. Valid values will be member of ::tvContentType_t
 * @param[in] userData                  - Data of the content
 *
 */
typedef void (*tvVideoContentChangeCB)(tvContentType_t mode,void *userData);


/**
 * @brief Structure for TV resolution parameters
 */
typedef struct
{
    int frameHeight;                            //!< Frame height of the TV resolution
    int frameWidth;                             //!< Frame width of the TV resolution 
    bool isInterlaced;                          //!< Checks whether the TV resolution is interlaced
    tvVideoResolution_t resolutionValue;        //!< Represents the struct TV resolution value
}tvResolutionParam_t;

/**
 * @brief Callback for tvVideoResolutionChangeCB.
 *
 * This callback is triggered when a video resolution change is encountered.
 *
 * @param[in] resolutionStruct    - Resolution parameter. Valid values will be member of ::tvResolutionParam_t
 * @param[in] userData            - Data of the content
 *
 */
typedef void (*tvVideoResolutionChangeCB)(tvResolutionParam_t resolutionStruct,void *userData);

/**
 * @brief Callback for tvVideoFrameRateChangeCB.
 *
 * This callback is triggered when a video framerate change is encountered.
 *
 * @param[in] frameRate            - framerate parameter. Valid values will be member of ::tvVideoFrameRate_t
 * @param[in] userData             - Data of the content
 *
 */
typedef void (*tvVideoFrameRateChangeCB)(tvVideoFrameRate_t frameRate,void *userData);

/** 
 * @brief Structure for the pic modes and value.@n
   The value contains the index and parameter is applicable only for get/set of picmodes.
 */
typedef struct pic_modes{
    char name[PIC_MODE_NAME_MAX];       //!< name of the picture mode
    short int value;                    //!< Index of the picture mode
}pic_modes_t;

/**
 * @brief Structure defining supported parameters in tv color
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
 * @brief Structure for video format call back data. 
 */
typedef struct
{
    void *userdata;                             //!< User data passed back to caller during call back
    tvVideoFormatChangeCB cb;                   //!< Video format change call back function pointed
}tvVideoFormatCallbackData;

/**
 * @brief Structure for FMM content call back data.
 */
typedef struct
{
    void *userdata;                             //!< User data passed back to caller during call back
    tvVideoContentChangeCB cb;                  //!< Video content change call back function pointed
}tvVideoContentCallbackData;

/** 
 * @brief Structure for video resolution callback data. 
 */
typedef struct
{
    void *userdata;                             //!< User data passed back to caller during call back
    tvVideoResolutionChangeCB cb;               //!< Video resolution change call back function pointed
}tvVideoResolutionCallbackData;

/** 
 * @brief Structure for video framerate callback data. 
 */
typedef struct
{
    void *userdata;                             //!< User data passed back to caller during call back
    tvVideoFrameRateChangeCB cb;                //!< Video frame change call back function pointed
}tvVideoFrameRateCallbackData;

/**
 * @brief Enumeration defining the supported WhiteBalance Color
 *
 */
typedef enum
{
    tvWB_COLOR_RED = 0,                         //!< Color is Red
    tvWB_COLOR_GREEN,                           //!< Color is Green
    tvWB_COLOR_BLUE,                            //!< Color is Blue
    tvWB_COLOR_MAX                              //!< End of enum
}tvWBColor_t;

/**
 * @brief Enumeration defining the supported WhiteBalance Control
 *
 */
typedef enum
{
    tvWB_CONTROL_GAIN = 0,                      //!< Modifies the intensity of Red, Green, and Blue at the brighter level
    tvWB_CONTROL_OFFSET,                        //!< Modifies the intensity of Red, Green, and Blue at the darker level
    tvWB_CONTROL_MAX                            //!< End of enum
}tvWBControl_t;

/**
 * @brief Structure for DV Calibration Settings.
 *
 * This struct holds calibration settings including
 * maximum and minimum temperature settings (Tmax, Tmin), gamma correction (Tgamma),
 * and RGBW color coordinate values (Rx, Ry, Gx, Gy, Bx, By, Wx, Wy).
 */
typedef struct {
    double Tmax, Tmin,
        Tgamma,
        Rx, Ry,
        Gx, Gy,
        Bx, By,
        Wx, Wy;
} tvDVCalibrationSettings_t;

/**
 * @brief Structure that holds a single context, used to describe a supported feature configuration.
 *
 * A context is formed from a PQ picture mode, video format and video source combination.
 * When listed in capabilities it indicates a valid combination a feature can be configured against.
 */
typedef struct
{
    tvPQModeIndex_t pq_mode; /**< PQ picture mode. When set to PQ_MODE_INVALID, it is global across
    all PQ picture modes. */
    tvVideoFormatType_t videoFormatType; /**< Video format When set to VIDEO_FORMAT_NONE, it is global across
    all video formats. */
    tvVideoSrcType_t videoSrcType; /**< Video source. When set to VIDEO_SOURCE_ALL, it is global across
    all video sources. */
} tvConfigContext_t;

/**
 * @brief Structure that holds an array of `tvConfigContext_t`, used to describe all of the supported feature
capabilities.
 *
 * When `num_contexts` is 0 it indicates a global feature setting that can't be configured for
 * specific PQ picture modes, video formats or video sources.
 */
typedef struct
{
    size_t num_contexts;
    tvConfigContext_t * contexts;
} tvContextCaps_t;

/**
 * @brief Enum for SDR Gamma values.
 *
 * This enum defines the possible values for SDR gamma correction,
 * including invalid, specific gamma values (1.8 to 2.4), ITU-R BT.1886 standard,
 * and the maximum boundary of the enum.
 */
typedef enum
{
    tvSdrGamma_INVALID = -1, //!< SDR gamma is invalid.
    tvSdrGamma_1_8, //!< SDR gamma is 1.8
    tvSdrGamma_1_9, //!< SDR gamma is 1.9
    tvSdrGamma_2_0, //!< SDR gamma is 2.0
    tvSdrGamma_2_1, //!< SDR gamma is 2.1
    tvSdrGamma_2_2, //!< SDR gamma is 2.2
    tvSdrGamma_2_3, //!< SDR gamma is 2.3
    tvSdrGamma_2_4, //!< SDR gamma is 2.4
    tvSdrGamma_BT_1886, //!< SDR gamma is ITU-R BT.1886
    tvSdrGamma_MAX //!< End of enum
} tvSdrGamma_t;

#ifdef __cplusplus
}
#endif

#endif //_TV_TYPES_H

/** @} */ // End of TV_Types_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
