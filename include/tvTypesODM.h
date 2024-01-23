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
* @defgroup TV_TYPES_ODM_H TV Types Header
* @{
*/

#ifndef _TV_TYPES_ODM_H
#define _TV_TYPES_ODM_H
/* SOC vendors can stub these ODM functions and mark it as weak */
#ifdef __cplusplus
extern "C"
{
#endif

//ODM Specific Macros
#define MAX_STRING_SIZE (15)                //!< Defines the maximum size of string
#define CONTROL_COUNT (2)                   //!< Defines the maximum WB control count
#define BACKLIGHT_CURVE_MAX_INDEX     (101)  
#define GENERIC_MODE_CONFIG_FILE  "/etc/tv/allmodes.conf"
#define ALS_LUT_MAX_INDEX     (513)          
#define ALS_LUT_FILE_NAME  "ALSToBackLightLUT.ini"

typedef short int tvPictureMode_t;          //!< Picture mode struct variable 


/**
 * @brief Enumeration defining supported HDR video formats
 */
typedef enum
{
    tvVideoHDRFormat_NONE= 0x00,                  //!< No video format 
    tvVideoHDRFormat_SDR = 0x01,                  //!< video format is SDR 
    tvVideoHDRFormat_HLG = 0x02,                  //!< video format is HLG 
    tvVideoHDRFormat_HDR10 = 0x04,                //!< video format is HDR10 
    tvVideoHDRFormat_HDR10PLUS = 0x08,            //!< video format is HDR10plus 
    tvVideoHDRFormat_DV = 0x010,                  //!< video format is DV
    tvVideoHDRFormat_MAX = 0x11                   //!< End of enum
}tvVideoHDRFormat_t;
    
#ifndef __VE_HDR_TYPE__
#define __VE_HDR_TYPE__
/** 
 * @brief Enumeration defining supported hdr types
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
    HDR_TYPE_MAX                                //!< End of enum
} tvhdr_type_t;
#endif

// ODM Specific. To be Depricated
typedef enum {
    tvContentFormatType_NONE= 0x00,
    tvContentFormatType_SDR = 0x01,
    tvContentFormatType_HLG = 0x02,
    tvContentFormatType_HDR10 = 0x03,
    tvContentFormatType_HDR10PLUS = 0x04,
    tvContentFormatType_DOVI = 0x05,
    tvContentFormatType_MAX
}tvContentFormatType_t;

//ODM specific. To be Depricated
/** 
 * @brief Enumeration defining supported component color types
 */
typedef enum
{
    COLOR_NONE  = 0,                            //!< Color is None
    COLOR_RED,                                  //!< Color is Red
    COLOR_GREEN,                                //!< Color is Green
    COLOR_BLUE,                                 //!< Color is Blue
    COLOR_CYAN,                                 //!< Color is Cyan
    COLOR_MAGENTA,                              //!< Color is Megenta
    COLOR_YELLOW,                               //!< Color is Yellow
    COLOR_MAX                                   //!< End of enum
}tvcomponent_color_type_t;

//ODM specific. To be Depricated
/**
 * @brief Enumeration defining supported component states
 */
typedef enum
{
    COMPONENT_DISABLE = 0,                      //!< State is Disable
    COMPONENT_ENABLE,                           //!< State is Enable
    COMPONENT_RESET,                            //!< State is Reset
    COMPONENT_MAX                               //!< End of enum
}tvcomponent_state_t;

//ODM specific. To be Depricated
typedef enum {
    mfrColorTemp_STANDARD = 0,
    mfrColorTemp_COLD,
    mfrColorTemp_WARM,
    mfrColorTemp_USER,
    mfrColorTemp_MAX
}fp_mfrColorTemp_t;

//ODM specific. To be Depricated
/**
 * @brief Enumeration defining the colour temperature offset from different sources
 */
 typedef enum input_source_offset_e {
    HDMI_OFFSET_NEW = 0,            //!< Color temperature offset for the source HDMI
    TV_OFFSET_NEW   = 4,            //!< Color temperature offset for the source TV
    AV_OFFSET_NEW   = 8,            //!< Color temperature offset for the source AV
    MAX_OFFSET_NEW                  //!< End of enum
} input_source_offset_t;

typedef struct getWBInfo {
    char wbControls[CONTROL_COUNT][MAX_STRING_SIZE];
    char wbGain[CONTROL_COUNT][MAX_STRING_SIZE];
    char wbOffset[CONTROL_COUNT][MAX_STRING_SIZE];
}getWBInfo_t;

typedef struct _gammaCalibrated {
     unsigned short r_gamma_offset[256];
     unsigned short g_gamma_offset[256];
     unsigned short b_gamma_offset[256];
}gammaCalibrated_t;

#ifdef __cplusplus
}
#endif

#endif // End of _TV_TYPES_ODM_H

/** @} */ // End of TV_TYPES_ODM_H
/** @} */ // End of TV_Settings_HAL
/** @} */ // End of TV_Settings
/** @} */ // End of HPK
