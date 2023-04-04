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
* @addtogroup HPK
* @{
**/
/**
* @addtogroup tvsettings
* @{
**/

#ifndef _TV_TYPES_H
#define _TV_TYPES_H

#include <inttypes.h>
/* TODO: BUG: incorrect usage of enum, it has to be #define in V2*/

#ifdef __cplusplus
extern "C"
{
#endif

typedef short int tvPictureMode_t;             //!< Picture mode struct variable 
const tvPictureMode_t tvPictureMode_MAX=0xFF;  //!< Setting the default value of max picture mode to OXFF 

/* An enumeration defining the backlight modes */

typedef enum {
    tvBacklightMode_NONE = 0x00,               //!< backlight mode - None
    tvBacklightMode_MANUAL = 0x01,             //!< backlight mode - manual
    tvBacklightMode_AMBIENT = 0x02,            //!< backlight mode - ambient
    tvBacklightMode_ECO = 0x04,                //!< backlight mode - eco
    tvBacklightMode_INVALID = 0x08,            //!< backlight mode - invalid
    tvBacklightMode_MAX                        //!< End of enum
}tvBacklightMode_t;

/* An enumeration defining different HDR video formats */
typedef enum {
    tvVideoFormat_NONE= 0x00,                  //!< video format - None 
    tvVideoFormat_SDR = 0x01,                  //!< video format - SDR 
    tvVideoFormat_HLG = 0x02,                  //!< video format - HLG 
    tvVideoFormat_HDR10 = 0x04,                //!< video format - HDR10 
    tvVideoFormat_HDR10PLUS = 0x08,            //!< video format - HDR10plus 
    tvVideoFormat_DV = 0x010,                  //!< video format - DV 
    tvVideoFormat_MAX                          //!< End of enum
}tvVideoFormat_t;

/* An enumeration defining different video resolution values */
typedef enum {
    tvVideoResolution_NONE,                    //!< Resolution None
    tvVideoResolution_720x240,                 //!< Resolution 720x240
    tvVideoResolution_2880x240,                //!< Resolution 2880x240
    tvVideoResolution_720x288,                 //!< Resolution 720x288
    tvVideoResolution_2880x288,                //!< Resolution 2880x288
    tvVideoResolution_640x480,                 //!< Resolution 640x480
    tvVideoResolution_720x480,                 //!< Resolution 720x480
    tvVideoResolution_800x480,                 //!< Resolution 800x48
    tvVideoResolution_852x480,                 //!< Resolution 852x480
    tvVideoResolution_854x480,                 //!< Resolution 854x480
    tvVideoResolution_1440x480,                //!< Resolution 1440x480
    tvVideoResolution_2880x480,                //!< Resolution 2880x480
    tvVideoResolution_960x540,                 //!< Resolution 960x540
    tvVideoResolution_3840x540,                //!< Resolution 3840x540
    tvVideoResolution_720x576,                 //!< Resolution 720x576
    tvVideoResolution_1440x576,                //!< Resolution 1440x576
    tvVideoResolution_2880x576,                //!< Resolution 2880x576
    tvVideoResolution_800x600,                 //!< Resolution 800x600
    tvVideoResolution_1024x600,                //!< Resolution 1024x600
    tvVideoResolution_1280x600,                //!< Resolution 1280x600
    tvVideoResolution_1280x720,                //!< Resolution 1280x720
    tvVideoResolution_1280x1024,               //!< Resolution 1280x1024
    tvVideoResolution_1680x720,                //!< Resolution 1680x720
    tvVideoResolution_1024x768,                //!< Resolution 1024x768
    tvVideoResolution_1280x768,                //!< Resolution 1280x768
    tvVideoResolution_1360x768,                //!< Resolution 1360x768
    tvVideoResolution_1366x768,                //!< Resolution 1366x76
    tvVideoResolution_1440x900,                //!< Resolution 1440x900
    tvVideoResolution_1600x900,                //!< Resolution 1600x900
    tvVideoResolution_1280x960,                //!< Resolution 1280x960
    tvVideoResolution_1920x1080,               //!< Resolution 1920x1080
    tvVideoResolution_2560x1080,               //!< Resolution 2560x1080
    tvVideoResolution_3840x1080,               //!< Resolution 3840x1080
    tvVideoResolution_1600x1200,               //!< Resolution 1600x1200
    tvVideoResolution_1920x1200,               //!< Resolution 1920x1200
    tvVideoResolution_2160x1200,               //!< Resolution 2160x1200
    tvVideoResolution_2400x1200,               //!< Resolution 2400x1200
    tvVideoResolution_2560x1440,               //!< Resolution 2560x1440
    tvVideoResolution_3440x1440,               //!< Resolution 3440x1440
    tvVideoResolution_3840x2160,               //!< Resolution 3840x2160
    tvVideoResolution_4096x2160,               //!< Resolution 4096x2160
    tvVideoResolution_MAX,                     //!< End of enum
}tvVideoResolution_t;

/* A structure defined for tv resolution parameters */
typedef struct {
    int frameHeight;                            //!< frame height of the tv resolution
    int frameWidth;                             //!< frame width of the tv resolution 
    bool isInterlaced;                          //!< checks whether the tv resolution is interlaced
    tvVideoResolution_t resolutionValue;        //!< represents the struct tv resolution value
}TvResolutionParam_t;

/* An enumeration defining different types of framerates */
typedef enum {
    tvVideoFrameRate_NONE,                      //!< Framerate None
    tvVideoFrameRate_24,                        //!< Framerate 24
    tvVideoFrameRate_25,                        //!< Framerate 25
    tvVideoFrameRate_30,                        //!< Framerate 30
    tvVideoFrameRate_50,                        //!< Framerate 50
    tvVideoFrameRate_60,                        //!< Framerate 60
    tvVideoFrameRate_23dot98,                   //!< Framerate 23dot98
    tvVideoFrameRate_29dot97,                   //!< Framerate 29dot97
    tvVideoFrameRate_59dot94,                   //!< Framerate 59dot94
    tvVideoFrameRate_MAX,                       //!< End of enum
}tvVideoFrameRate_t;

/* An enumeration defining different display modes */
typedef enum {
    tvDisplayMode_4x3 = 0,                      //!< Displaymode 4x3
    tvDisplayMode_16x9,                         //!< Displaymode 16x9
    tvDisplayMode_FULL,                         //!< Displaymode Full
    tvDisplayMode_NORMAL,                       //!< Displaymode Normal
    tvDisplayMode_AUTO,                         //!< Displaymode Auto
    tvDisplayMode_DIRECT,                       //!< Displaymode Direct
    tvDisplayMode_ZOOM,                         //!< Displaymode Zoom
    tvDisplayMode_MAX                           //!< End of enum
}tvDisplayMode_t;

/* An enumeration defining different color temperature */
typedef enum {
    tvColorTemp_STANDARD = 0,                   //!< Color Temperature Standard
    tvColorTemp_WARM,                           //!< Color Temperature Warm
    tvColorTemp_COLD,                           //!< Color Temperature Cold
    tvColorTemp_USER,                           //!< Color Temperature User
    tvColorTemp_MAX                             //!< End of enum
}tvColorTemp_t;

/* An enum defining different wakeup source types */
typedef enum {
    tvWakeupSrc_VOICE = 0,                     //!< Wakeup source Voice
    tvWakeupSrc_PRESENCE_DETECTION,            //!< Wakeup source Presence detection
    tvWakeupSrc_BLUETOOTH,                     //!< Wakeup source bluetooth
    tvWakeupSrc_WIFI,                          //!< Wakeup source Wifi
    tvWakeupSrc_IR,                            //!< Wakeup source IR
    tvWakeupSrc_POWER_KEY,                     //!< Wakeup source Powerkey
    tvWakeupSrc_TIMER,                         //!< Wakeup source Timer
    tvWakeupSrc_CEC,                           //!< Wakeup source CEC
    tvWakeupSrc_LAN,                           //!< Wakeup source LAN
    tvWakeupSrc_MAX                            //!< End of enum
}tvWakeupSrcType_t;

/* An enumeration defining different parameters in tv color */
typedef struct _tvDataColor {
     unsigned int r_gain;                       //!< Color Data r_gain
     unsigned int g_gain;                       //!< Color Data g_gain
     unsigned int b_gain;                       //!< Color Data b_gain
     int r_offset;                              //!< Color Data r_offset
     int g_offset;                              //!< Color Data g_offset
     int b_offset;                              //!< Color Data b_offset
}TvDataColor_t;

/* An enumeration defining different tv component colors */
typedef enum {
    tvDataColor_NONE= 0,                        //!< Color None
    tvDataColor_RED = 1,                        //!< Color Red
    tvDataColor_GREEN = 2,                      //!< Color Green
    tvDataColor_BLUE = 4,                       //!< Color Blue
    tvDataColor_YELLOW = 8,                     //!< Color Yellow
    tvDataColor_CYAN = 16,                      //!< Color Cyan
    tvDataColor_MAGENTA = 32,                   //!< Color Megenta
    tvDataColor_MAX = 64                        //!< End of enum
}tvDataComponentColor_t;

/* An enumeration defining different conent format type */
typedef enum {
    tvContentFormatType_NONE= 0x00,             //!< Content Format type NONE
    tvContentFormatType_SDR = 0x01,             //!< Content Format type SDR
    tvContentFormatType_HLG = 0x02,             //!< Content Format type HLG
    tvContentFormatType_HDR10 = 0x03,           //!< Content Format type HDR10
    tvContentFormatType_HDR10PLUS = 0x04,       //!< Content Format type HDR10PLUS
    tvContentFormatType_DOVI = 0x05,            //!< Content Format type DOVI
    tvContentFormatType_MAX                     //!< End of enum
}tvContentFormatType_t;

#ifndef __VE_HDR_TYPE__
#define __VE_HDR_TYPE__

/* An enumeration defining different hdr types */
typedef enum tvhdr_type_e {
    HDR_TYPE_NONE      = 0,                     //!< HDR Type None
    HDR_TYPE_HDR10     = 1,                     //!< HDR Type HDR10
    HDR_TYPE_HDR10PLUS = 2,                     //!< HDR Type HDR10PLUS
    HDR_TYPE_DOVI      = 3,                     //!< HDR Type DOVI
    HDR_TYPE_PRIMESL   = 4,                     //!< HDR Type PRIMESL
    HDR_TYPE_HLG       = 5,                     //!< HDR Type HLG
    HDR_TYPE_SDR       = 6,                     //!< HDR Type SDR
    HDR_TYPE_MVC       = 7,                     //!< HDR Type MVC
    HDR_TYPE_MAX,                               //!< End of enum
} tvHdr_Type_t;
#endif // __VE_HDR_TYPE__

/* An enumeration defining different component color types */
typedef enum
{
    COLOR_ENABLE  = 0,                          //!< Color Enable
    COLOR_RED,                                  //!< Color Red
    COLOR_GREEN,                                //!< Color Green
    COLOR_BLUE,                                 //!< Color Blue
    COLOR_CYAN,                                 //!< Color Cyan
    COLOR_MAGENTA,                              //!< Color Megenta
    COLOR_YELLOW,                               //!< Color Yellow
    COLOR_MAX,                                  //!< End of enum
}tvComponent_Color_Type_t;

/* An enumeration defining different component states */
typedef enum
{
    COMPONENT_DISABLE = 0,                      //!< State Disable
    COMPONENT_ENABLE,                           //!< State Enable
    COMPONENT_RESET,                            //!< State Reset
    COMPONENT_MAX,                              //!< End of enum
}tvComponent_State_t;

/* An enumeration defining different CMS tunel */
typedef enum
{
    COLOR_STATE=0,                              //!< CMS tunel State
    COLOR_HUE,                                  //!< CMS tunel Hue
    COLOR_SATURATION,                           //!< CMS tunel Saturation
    COLOR_LUMA,                                 //!< CMS tunel Luma
    COLOR_MAX                                   //!< End of enum
}tvCMS_tunel_t;

/**
 * TODO: need to prefix with tvSettings_ in V2
 * TODO: change the int to inttypes variables  in V2
 */
/* An enumeration defining the various dolby modes */
typedef enum {
    tvDolbyMode_Dark=0,                         //!< Dolby mode Dark
    tvDolbyMode_Bright,                         //!< Dolby mode Bright
    tvHDR10Mode_Dark=3,                         //!< HDR1HLG mode Gamede Dark
    tvHDR10Mode_Bright,                         //!< HDR10 mode bright
    tvHLGMode_Dark=6,                           //!< HLG mode Dark
    tvHLGMode_Bright,                           //!< HLG mode Bright
    tvDolbyMode_Game=9,                         //!< Dolby mode Game
    tvHDR10Mode_Game,                           //!< HDR10 mode Game
    tvHLGMode_Game,                             //!< End of enum
    tvMode_Max = 28
}tvHDRMode_t;


/* An enumeration defining the different dimming modes */
typedef enum {
  tvDimmingMode_Fixed=0,                        //!< Mode Fixed
  tvDimmingMode_Local,                          //!< Mode Local
  tvDimmingMode_Global,                         //!< Mode Global
  tvDimmingMode_Max                             //!< End of enum
}tvDimmingMode_t;

#ifdef __cplusplus
}
#endif

#endif //_TV_TYPES_H

/** @} */ // End of tvsettings
/** @} */ // End of HPK
