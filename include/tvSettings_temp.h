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


#ifndef _TV_SETTINGS_TEMP_H
#define _TV_SETTINGS_TEMP_H

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

/**
 * @brief Get the tint value.
 * 
 * This function gets the current tint value.
 *
 * @param[out] tint             - Tint value(0 - 100)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTint(int *tint);
/**
 * @brief Set the tint value.
 * 
 * This function sets the tint value.
 *
 * @param[in] tint             - Tint value(0 - 100)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetTint(int tint);

/**
 * @brief Set the RGB values.
 * 
 * This function sets the RGB pattern value(0 - 100).
 *
 * @param[in] r                    - Red value
 * @param[in] g                    - Green value
 * @param[in] b                    - Blue value
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting RGB values
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetRGBPattern(int r,int g, int b) ;

/**
 * @brief Get the RGB values.
 * 
 * This function gets the RGB pattern value(0 - 100).
 *
 * @param[out] r                    - Red value
 * @param[out] g                    - Green value
 * @param[out] b                    - Blue value
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetRGBPattern(int *r,int *g,int *b);

/**
 * @brief Set the gray pattern value.
 * 
 * This function sets the YUV color pattern value.
 *
 * @param[in] YUVValue              - Gray pattern value(0 -100)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting gray pattern values
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetGrayPattern(int YUVValue);

/**
 * @brief Get the gray pattern value.
 * 
 * This function gets the YUV color pattern value.
 *
 * @param[out] YUVValue              - Gray pattern value(0 - 100)
 * 
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting gray pattern values
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @param[in] colorTemp              - Color temperature
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
 * @brief Get HLG mode
 * 
 * This function gets the given HLG mode.
 *
 * @param[out] hlgMode               - HLG mode(dark, bright)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting HLG mode
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetTVHLGMode()
 */
tvError_t GetTVHLGMode(char *hlgMode);

/**
 * @brief Get HDR10 mode
 * 
 * This function gets the given HDR10 mode.
 *
 * @param[out] hdr10Mode               - HDR10 mode(dark, bright)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while getting HDR10 mode
 * 
 * @pre  tvInit() should be called before calling this API.
 * @see GetTVHLGMode()
 */
tvError_t GetTVHDR10Mode(char *hdr10Mode);

/**
 * @brief Set the rgain value for the source.
 * 
 * This function sets the rgain value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature
 * @param[in] rgain                - Value(0 - 2047)
 * @param[in] sourceId             - Source offset
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
tvError_t SetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int rgain,int sourceId, int saveOnly);

/**
 * @brief Get the rgain value for the source.
 * 
 * This function gets the rgain value for specfic color temperature and source.
 *
 * @param[in] colorTemp            - Color temperature
 * @param[out] rgain               - Value(0 - 2047)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[in] ggain                - Value(0 - 2047)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[out] ggain               - Value(0 - 2047)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[in] bgain                - Value(0 - 2047)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[out] bgain               - Value(0 - 2047)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[in] rpostoffset          - Value(-1024 - 1024)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[out] rpostoffset         - Value(-1024 - 1024)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[in] gpostoffset          - Value(-1024 - 1024)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[out] gpostoffset         - Value(-1024 - 1024)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[in] bpostoffset          - Value(-1024 - 1024)
 * @param[in] sourceId             - Source offset
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
 * @param[in] colorTemp            - Color temperature
 * @param[out] bpostoffset         - Value(-1024 - 1024)
 * @param[in] sourceId             - Source offset
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
 * @brief Get the backlight factor.
 * 
 * This function gets the TV backlight global factor.
 *
 * @param[out] value           - Global backlight factor
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetTVBacklightGlobalFactor(int * value);

/**
 * @brief Set the backlight factor.
 * 
 * This function sets the TV backlight global factor.
 *
 * @param[in] value                 - Global backlight factor
 * @param[in] rangeMidPointValue    - Mid value
 *
 * @return tvError_t
 * @retval tvERROR_GENERAL          - when midPointValue is 0 or error while setting global factor
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetTVBacklightGlobalFactor(int value, int rangeMidPointValue);

/**
 * @brief Enable or disable gamma mode.
 * 
 * This function enables or disables the gamma mode.
 *
 * @param[in] mode                - Gamma mode(0 or 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
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
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting dimming level
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
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
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetLocalDimmingLevel(int *localDimmingLevel);

/**
 * @brief Save low latency state to vendor specific storage file.
 * 
 * This function saves the low latency state for the specific picture mode, hdr_type and sourceInput. @n
 * Currently SOURCE_INVALID(-1) is specified it will be treated as save to all sources.
 * TODO: Add new enum value for sourceinput ALL in V2.
 * TODO: sourcetype should be tv_source_input_t in V2
 * TODO: hdr_type should be tvhdr_type_t in V2
 *
 * @param[in] sourceInput           - Source input value
 * @param[in] pq_mode               - PQ mode value(0 - 9)
 * @param[in] hdr_type              - HDR type value(tvhdr_type_t)
 * @param[in] value                 - Value of the low latency index(0 or 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting latency state
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SaveLowLatencyState( int sourceInput, int pq_mode,int hdr_type,int value );

/**
 * @brief Set low latency index
 * 
 * This function sets the low latency index
 *
 * @param[in] lowLatencyIndex       - Value of the low latency state(0 or 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting latency state
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t SetLowLatencyState( int lowLatencyIndex );

/**
 * @brief Get low latency index
 * 
 * This function gets the low latency index
 *
 * @param[in] lowlatencystate       - Value of the low latency state(0 or 1)
 *
 * @return tvError_t
 * @retval tvERROR_NONE             - Success
 * @retval tvERROR_GENERAL          - Error while setting latency state
 * @retval tvERROR_INVALID_STATE    - Interface is not initialized
 * 
 * @pre  tvInit() should be called before calling this API.
 */
tvError_t GetLowLatencyState(int *lowlatencystate);

#ifdef __cplusplus
}
#endif

#endif // End of _TV_SETTINGS_TEMP_H

/** @} */ // End of tvsettings
/** @} */ // End of HPK