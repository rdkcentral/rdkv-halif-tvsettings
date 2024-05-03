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
#ifdef __cplusplus
extern "C"
{
#endif

typedef short int tvPictureMode_t;

const tvPictureMode_t tvPictureMode_MAX=0xFF;

/**
 * @brief Enumeration defining the supported FMM modes
 *
 */
typedef enum {
    tvContentType_NONE= 0x00, //!< Content type is NONE
    tvContentType_FMM = 0x01, //!< Content type is FMM
}tvContentType_t;

/**
 * @brief Enumeration defining the supported backlight modes
 * 
 */
typedef enum {
    tvBacklightMode_NONE = 0x00,               //!< No backlight
    tvBacklightMode_MANUAL = 0x01,             //!< backlight mode is manual
    tvBacklightMode_AMBIENT = 0x02,            //!< backlight mode is ambient
    tvBacklightMode_ECO = 0x04,                //!< backlight mode is eco
    tvBacklightMode_INVALID = 0x08,            //!< backlight mode is invalid
}tvBacklightMode_t;

/**
 * @brief Enumeration defining the TV video HDR format
 */
typedef enum {
    tvVideoHDRFormat_NONE= 0x00,               //!<  Video HDR format None
    tvVideoHDRFormat_SDR = 0x01,               //!<  Video HDR format SDR
    tvVideoHDRFormat_HLG = 0x02,               //!<  Video HDR format HLG
    tvVideoHDRFormat_HDR10 = 0x04,             //!<  Video HDR format HDR10
    tvVideoHDRFormat_HDR10PLUS = 0x08,         //!<  Video HDR format HDR10PLUS
    tvVideoHDRFormat_DV = 0x010,               //!<  Video HDR format DV
}tvVideoHDRFormat_t;

/**
 *  @brief Enumeration defining supported video resolution values
 */
typedef enum {
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
}tvVideoResolution_t;

/**
 * @brief Enumeration defining the TV resolution paramater
 */
typedef struct {
    int frameHeight;                           //!<  Frame height
    int frameWidth;                            //!<  Frame width
    bool isInterlaced;                         //!<  Is Interlaced
    tvVideoResolution_t resolutionValue;       //!<  Resolution value
}tvResolutionParam_t;

/**
 *  @brief Enumeration defining supported types of frame rates
 */
typedef enum {
    tvVideoFrameRate_NONE,                      //!< No frame rate
    tvVideoFrameRate_24,                        //!< Frame rate is 24
    tvVideoFrameRate_25,                        //!< Frame rate is 25
    tvVideoFrameRate_30,                        //!< Frame rate is 30
    tvVideoFrameRate_50,                        //!< Frame rate is 50
    tvVideoFrameRate_60,                        //!< Frame rate is 60
    tvVideoFrameRate_23dot98,                   //!< Frame rate is 23.98
    tvVideoFrameRate_29dot97,                   //!< Frame rate is 29.97
    tvVideoFrameRate_59dot94,                   //!< Frame rate is 59.94
}tvVideoFrameRate_t;

/**
 *  @brief Enumeration defining supported display modes
 */
typedef enum {
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
 */
typedef enum {
    tvColorTemp_STANDARD = 0,                   //!<  Temperature standard
    tvColorTemp_WARM,                           //!<  Temperature Warm
    tvColorTemp_COLD,                           //!<  Temperature cold
    tvColorTemp_USER,                           //!<  Temperature standard
    tvColorTemp_MAX                             //!<  Temperature MAX
}tvColorTemp_t;

/**
 * @brief Enumeration defining supported wakeup source types
 */
typedef enum {
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
 * @brief Structure defining supported parameters in tv color
 */
typedef struct _tvDataColor {
     unsigned int r_gain;                       //!< Color Data is r_gain
     unsigned int g_gain;                       //!< Color Data is g_gain
     unsigned int b_gain;                       //!< Color Data is b_gain
     int r_offset;                              //!< Color Data is r_offset
     int g_offset;                              //!< Color Data is g_offset
     int b_offset;                              //!< Color Data is b_offset
}tvDataColor_t;

/**
 * @brief Enumeration defining the TV Data color SSM
 */
typedef struct _tvDataColorSSM {
    unsigned int en;
    int r_pre_offset;                           //!< s11.0, range -1024~+1023, default is 0
    int g_pre_offset;                           //!< s11.0, range -1024~+1023, default is 0
    int b_pre_offset;                           //!< s11.0, range -1024~+1023, default is 0
    unsigned int r_gain;                        //!< u1.10, range 0~2047, default is 1024 (1.0x)
    unsigned int g_gain;                        //!< u1.10, range 0~2047, default is 1024 (1.0x)
    unsigned int b_gain;                        //!< u1.10, range 0~2047, default is 1024 (1.0x)
    int r_post_offset;                          //!< s11.0, range -1024~+1023, default is 0
    int g_post_offset;                          //!< s11.0, range -1024~+1023, default is 0
    int b_post_offset;                          //!< s11.0, range -1024~+1023, default is 0
} tvDataColorSSM_t;

/**
 * @brief Enumeration defining supported RGB values
 */
typedef enum _tvRGBType {
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
typedef enum {
    tvDataColor_NONE= 0,                        //!< No color
    tvDataColor_RED = 1,                        //!< Color is Red
    tvDataColor_GREEN = 2,                      //!< Color is Green
    tvDataColor_BLUE = 4,                       //!< Color is Blue
    tvDataColor_YELLOW = 8,                     //!< Color is Yellow
    tvDataColor_CYAN = 16,                      //!< Color is Cyan
    tvDataColor_MAGENTA = 32,                   //!< Color is Megenta
    tvDataColor_MAX = 64,                       //!< End of enum
}tvDataComponentColor_t;

/**
 * @brief Enumeration defining the TV content format type
 */
typedef enum {
    tvContentFormatType_NONE= 0x00,              //!< Tv Content Format Type None
    tvContentFormatType_SDR = 0x01,              //!< Tv Content Format Type SDR
    tvContentFormatType_HLG = 0x02,              //!< Tv Content Format Type HLG
    tvContentFormatType_HDR10 = 0x03,            //!< Tv Content Format Type HDR10
    tvContentFormatType_HDR10PLUS = 0x04,        //!< Tv Content Format Type HDR10PLUS
    tvContentFormatType_DOVI = 0x05,             //!< Tv Content Format Type DOVI
    tvContentFormatType_MAX                      //!< Tv Content Format Type MAX
}tvContentFormatType_t;

#ifndef __VE_HDR_TYPE__
#define __VE_HDR_TYPE__

/**
 * @brief Enumeration defining the TV hdr type
 */
typedef enum tvhdr_type_e {
    HDR_TYPE_NONE      = 0,                       //!< HDR TYPE NONE
    HDR_TYPE_HDR10     = 1,                       //!< HDR TYPE HDR10
    HDR_TYPE_HDR10PLUS = 2,                       //!< HDR TYPE HDR10PLUS
    HDR_TYPE_DOVI      = 3,                       //!< HDR TYPE DOVI
    HDR_TYPE_PRIMESL   = 4,                       //!< HDR TYPE PRIMESL
    HDR_TYPE_HLG       = 5,                       //!< HDR TYPE HLG
    HDR_TYPE_SDR       = 6,                       //!< HDR TYPE SDR
    HDR_TYPE_MVC       = 7,                       //!< HDR TYPE MVC
    HDR_TYPE_MAX,                                 //!< HDR TYPE MAX
} tvhdr_type_t;
#endif

/**
 * @brief Enumeration defining the TV component color type
 */
typedef enum tvcomponent_color_type_e
{
    COLOR_ENABLE  = 0,                            //!< COLOR TYPE ENABLE
    COLOR_RED,                                    //!< COLOR TYPE RED
    COLOR_GREEN,                                  //!< COLOR TYPE GREEN
    COLOR_BLUE,                                   //!< COLOR TYPE BLUE
    COLOR_CYAN,                                   //!< COLOR TYPE CYAN
    COLOR_MAGENTA,                                //!< COLOR TYPE MAGENTA
    COLOR_YELLOW,                                 //!< COLOR TYPE YELLOW
}tvcomponent_color_type_t;

/**
 * @brief Enumeration defining the TV component state
 */
typedef enum tvcomponent_state_e
{
    COMPONENT_DISABLE = 0,                        //!< COMPONENT DISABLE
    COMPONENT_ENABLE,                             //!< COMPONENT ENABLE
    COMPONENT_RESET,                              //!< COMPONENT RESET
}tvcomponent_state_t;

/**
 * @brief Enumeration defining the TV CMS tunel
 */
typedef enum tvCMS_tunel_e
{
    COLOR_STATE=0,                                 //!< COLOR STATE
    COLOR_HUE,                                     //!< COLOR HUE
    COLOR_SATURATION,                              //!< COLOR SATURATION
    COLOR_LUMA                                     //!< COLOR LUMA
}tvCMS_tunel_t;

/**
 * @brief Enumeration defining the TV source save configurations
 */
typedef enum tvSourceSaveConfig {
    SOURCE_SAVE_FOR_ALL = 0,                      //!< SOURCE SAVE FOR ALL
    SOURCE_SAVE_FOR_INDIVIDUAL,                   //!< SOURCE SAVE FOR INDIVIDUAL
    SOURCE_SAVE_FOR_GROUPED ,                     //!< SOURCE SAVE FOR GROUPED
    SOURCE_SAVE_FOR_MAX                           //!< SOURCE SAVE FOR MAX
}tvSourceSaveConfig_t;

/**
 * @brief Enumeration defining the TV Save format configurations
 */
typedef enum tvSaveFormatsConfig {
    CONTENT_FORMAT_SAVE_FOR_ALL=0,                //!< CONTENT FORMAT SAVE FOR ALL
    CONTENT_FORMAT_SAVE_FOR_CURRENT,              //!< CONTENT FORMAT SAVE FOR CURRENT
    CONTENT_FORMAT_SAVE_FOR_GROUPED,              //!< CONTENT FORMAT SAVE FOR GROUPED
    CONTENT_FORMAT_SAVE_FOR_DV_ONLY,              //!< CONTENT FORMAT SAVE FOR DV ONLY
    CONTENT_FORMAT_SAVE_FOR_NON_DV,               //!< CONTENT FORMAT SAVE FOR NON DV
    CONTENT_FORMAT_SAVE_FOR_HDR10_ONLY,           //!< CONTENT FORMAT SAVE FOR HDR10 ONLY
    CONTENT_FORMAT_SAVE_FOR_HLG_ONLY,             //!< CONTENT FORMAT SAVE FOR HLG ONLY
    CONTENT_FORMAT_SAVE_MAX                       //!< CONTENT FORMAT SAVE MAX
}tvSaveFormatsConfig_t;

/**
 * @brief Enumeration defining the TV Save Picture mode configurations
 */
typedef enum tvSavePicModesConfig {
    PIC_MODE_SAVE_FOR_ALL=0,                      //!< PIC MODE SAVE FOR ALL
    PIC_MODE_FORMAT_SAVE_FOR_CURRENT,             //!< PIC MODE SAVE FOR CURRENT
    PIC_MODE_FORMAT_SAVE_MAX                      //!< PIC MODE SAVE MAX
}tvSavePicModesConfig_t;

/**
 * @brief Enumeration defining the supported PQ param types
 *
 */
typedef enum tvPQParameterIndex {
    PQ_PARAM_BRIGHTNESS  = 0,                      //!< PQ PARAM BRIGHTNESS
    PQ_PARAM_CONTRAST  ,                           //!< PQ PARAM CONTRAST
    PQ_PARAM_SHARPNESS ,                           //!< PQ PARAM SHARPNESS
    PQ_PARAM_SATURATION ,                          //!< PQ PARAM SATURATION
    PQ_PARAM_BACKLIGHT  ,                          //!< PQ PARAM BACKLIGHT
    PQ_PARAM_HUE  ,                                //!< PQ PARAM HUE
    PQ_PARAM_ASPECT_RATIO  ,                       //!< PQ PARAM ASPECT RATIO
    PQ_PARAM_CMS  ,                                //!< PQ PARAM CMS
    PQ_PARAM_DOLBY_MODE,                           //!< PQ PARAM DOLBY MODE
    PQ_PARAM_COLOR_TEMPERATURE	,                  //!< PQ PARAM COLOR TEMPERATURE
    PQ_PARAM_LDIM,                                 //!< PQ PARAM LDIM
    PQ_PARAM_HDR10_MODE,                           //!< PQ PARAM HDR10 MODE
    PQ_PARAM_HLG_MODE,                             //!< PQ PARAM HLG MODE
    PQ_PARAM_LOCALDIMMING_LEVEL,                   //!< PQ PARAM LOCALDIMMING LEVEL
    PQ_PARAM_LOWLATENCY_STATE,                     //!< PQ PARAM LOWLATENCY STATE
    PQ_PARAM_DIMMINGMODE                           //!< PQ PARAM DIMMING MODE
}tvPQParameterIndex_t;

/**
 *  @brief Enumeration defining the various supported dolby modes
 */
typedef enum {
    tvDolbyMode_Invalid = -1,                       //!< TV DOLBY MODE INVALID
    tvDolbyMode_Dark = 0,                           //!< TV DOLBY MODE DARK
    tvDolbyMode_Bright,                             //!< TV DOLBY MODE BRIGHT
    tvDolbyMode_Custom,                             //!< TV DOLBY MODE CUSTOM
    tvHDR10Mode_Dark,                               //!< TV HDR10 MODE DARK
    tvHDR10Mode_Bright,                             //!< TV HDR10 MODE BRIGHT
    tvHDR10Mode_Custom,                             //!< TV HDR10 MODE CUSTOM
    tvHLGMode_Dark,                                 //!< TV HLG MODE DARK
    tvHLGMode_Bright,                               //!< TV HLG MODE BRIGHT
    tvHLGMode_Custom,                               //!< TV HLG MODE CUSTOM
    tvDolbyMode_Dark_Game,                          //!< TV DOLBY MODE DARK GAME
    tvDolbyMode_Bright_Game,                        //!< TV DOLBY MODE BRIGHT GAME
    tvHDR10Mode_Dark_Game,                          //!< TV HDR10 MODE DARK GAME
    tvHDR10Mode_Bright_Game,                        //!< TV HDR10 MODE BRIGHT GAME
    tvHLGMode_Dark_Game,                            //!< TV HLG MODE DARK GAME
    tvHLGMode_Bright_Game,                          //!< TV HLG MODE BRIGHT GAME
    tvMode_Max = 28                                 //!< TV MODE MAX
}tvDolbyMode_t;

/**
 * @brief Enumeration defining the supported dimming modes
 */
typedef enum {
  tvDimmingMode_Fixed=0,                 //!< Dimming Mode is Fixed
  tvDimmingMode_Local,                   //!< Dimming Mode is Local
  tvDimmingMode_Global                   //!< Dimming Mode is Global
}tvDimmingMode_t;

#ifdef __cplusplus
}
#endif
#endif //_TV_TYPES_H

/** @} */ // End of TV_Types_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
