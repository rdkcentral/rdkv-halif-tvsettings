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

#define ALS_LUT_MAX_INDEX     (513)
#define ALS_LUT_FILE_NAME  "ALSToBackLightLUT.ini"

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
    int sdrALSCurve[ALS_LUT_MAX_INDEX];
    int hdrALSCurve[ALS_LUT_MAX_INDEX];
}tvBacklightInfo_t;

typedef enum tvdeviceBoostMode_s{
    tvdeviceBoostMode_Normal = 0,
    tvdeviceBoostMode_Boost,
    tvdeviceBoostMode_Burst,
    tvdeviceBoostMode_Reset,
    tvdeviceBoostMode_Max
}tvdeviceBoostMode_t;

tvError_t tvInit();
tvError_t tvSD3toCriSyncInit();
tvError_t tvTerm();
tvError_t GetTVPictureMode(char *pictureMode);
tvError_t SetTVPictureMode(const char * pictureMode);
tvError_t GetBacklight(int *backlight);
tvError_t SetBacklight(int backlight);
tvError_t SetBrightness(int brightness);
tvError_t GetBrightness(int *brightness);
tvError_t SetContrast(int contrast);
tvError_t GetContrast(int *contrast);
tvError_t SetSharpness(int sharpness);
tvError_t GetSharpness(int *sharpness);
tvError_t SetSaturation(int saturation);
tvError_t GetSaturation(int *saturation);
tvError_t SetHue(int hue);
tvError_t GetHue(int *hue);
tvError_t SetColorTemperature(tvColorTemp_t colorTemp);
tvError_t GetColorTemperature(tvColorTemp_t *colorTemp);
tvError_t SetAspectRatio(tvDisplayMode_t dispMode);
tvError_t GetAspectRatio(tvDisplayMode_t *dispMode);

tvError_t GetTint(int *tint);
tvError_t SetTint(int tint);
tvError_t GetSupportedBacklightModes(int *blModes);
tvError_t GetCurrentBacklightMode(tvBacklightMode_t *blMode);
tvError_t SetCurrentBacklightMode(tvBacklightMode_t blMode);
tvError_t GetCurrentVideoFormat(tvVideoHDRFormat_t *format);
tvError_t GetVideoResolution(tvResolutionParam_t *res);
tvError_t GetVideoFrameRate(tvVideoFrameRate_t *format);
tvError_t setWakeupConfig(const tvWakeupSrcType_t src_type, const bool value);

tvError_t SetRGBPattern(int r,int g, int b) ;
tvError_t GetRGBPattern(int *r,int *g,int *b);
tvError_t SetGrayPattern(int YUVValue);
tvError_t GetGrayPattern(int* YUVValue);
tvError_t SetColorTemp_Rgain(tvColorTemp_t colorTemp, int rgain);
tvError_t GetColorTemp_Rgain(tvColorTemp_t colorTemp, int* rgain);

tvError_t SetColorTemp_Ggain(tvColorTemp_t colorTemp, int ggain);
tvError_t GetColorTemp_Ggain(tvColorTemp_t colorTemp, int* ggain);
tvError_t SetColorTemp_Bgain(tvColorTemp_t colorTemp, int bgain);
tvError_t GetColorTemp_Bgain(tvColorTemp_t colorTemp, int* bgain);

tvError_t SetColorTemp_R_post_offset(tvColorTemp_t colorTemp, int rpostoffset);
tvError_t GetColorTemp_R_post_offset(tvColorTemp_t colorTemp, int* rpostoffset);
tvError_t SetColorTemp_G_post_offset(tvColorTemp_t colorTemp, int gpostoffset);
tvError_t GetColorTemp_G_post_offset(tvColorTemp_t colorTemp, int* gpostoffset);
tvError_t SetColorTemp_B_post_offset(tvColorTemp_t colorTemp, int bpostoffset);
tvError_t GetColorTemp_B_post_offset(tvColorTemp_t colorTemp, int* bpostoffset);

tvError_t GetTVSupportedPictureModes(pic_modes_t *pictureModes[],unsigned short *count);

void RegisterVideoFormatChangeCB(tvVideoFormatCallbackData& cbData);
void RegisterVideoContentChangeCB(tvVideoContentCallbackData &cbData);

typedef void (*tvVideoResolutionChangeCB)(tvResolutionParam_t resolutionStruct,void *userData);
typedef struct
{
    void *userdata;
    tvVideoResolutionChangeCB cb;
}tvVideoResolutionCallbackData;

void RegisterVideoResolutionChangeCB(tvVideoResolutionCallbackData& cbData);

typedef void (*tvVideoFrameRateChangeCB)(tvVideoFrameRate_t frameRate,void *userData);
typedef struct
{
    void *userdata;
    tvVideoFrameRateChangeCB cb;
}tvVideoFrameRateCallbackData;

void RegisterVideoFrameRateChangeCB(tvVideoFrameRateCallbackData& cbData);

tvError_t GetTVSupportedDVModes(pic_modes_t *dvModes[],unsigned short *count);
tvError_t SetTVDolbyVisionMode(const char * dolbyMode);
tvError_t GetTVDolbyVisionMode(char *dolbyMode);
tvError_t SetTVHLGMode(const char * hlgMode);
tvError_t SetTVHDR10Mode(const char * hdr10Mode);
tvError_t GetTVHLGMode(char *hlgMode);
tvError_t GetTVHDR10Mode(char *hdr10Mode);
tvError_t GetTVSupportedHLGModes(pic_modes_t *dvModes[],unsigned short *count);
tvError_t GetTVSupportedHDR10Modes(pic_modes_t *dvModes[],unsigned short *count);

tvError_t SetDynamicContrast(const char *dynamicContrastEnable);
tvError_t GetDynamicContrast(char *isDynamicContrastEnabled);


tvError_t SetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int rgain,int sourceId, int saveOnly);
tvError_t GetColorTemp_Rgain_onSource(tvColorTemp_t colorTemp, int* rgain,int sourceId);
tvError_t SetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int ggain,int sourceId, int saveOnly);
tvError_t GetColorTemp_Ggain_onSource(tvColorTemp_t colorTemp, int* ggain,int sourceId);
tvError_t SetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int bgain,int sourceId, int saveOnly);
tvError_t GetColorTemp_Bgain_onSource(tvColorTemp_t colorTemp, int* bgain,int sourceId);

tvError_t SetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int rpostoffset,int sourceId, int saveOnly);
tvError_t GetColorTemp_R_post_offset_onSource(tvColorTemp_t colorTemp, int* rpostoffset,int sourceId);
tvError_t SetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int gpostoffset,int sourceId, int saveOnly);
tvError_t GetColorTemp_G_post_offset_onSource(tvColorTemp_t colorTemp, int* gpostoffset,int sourceId);
tvError_t SetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int bpostoffset,int sourceId, int saveOnly);
tvError_t GetColorTemp_B_post_offset_onSource(tvColorTemp_t colorTemp, int* bpostoffset,int sourceId);

tvError_t setWBctrl(char *inputSrc, char *colorTemp,char *color, char *ctrl, int value);
tvError_t getWBctrl(char *inputSrc, char *colortemp, char *color, char *ctrl, int *value);
tvError_t getWbInfo(getWBInfo_t* params, std::vector<std::string> &selector, std::vector<std::string> &colorTmp, std::vector<std::string> &input);
tvError_t enableWBmode(bool value);

tvError_t GetSupportedComponentColor(int *blComponentColor);
tvError_t SetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int saturation);
tvError_t GetCurrentComponentSaturation(tvDataComponentColor_t blSaturationColor, int *saturation);
tvError_t SetCurrentComponentHue(tvDataComponentColor_t blHueColor, int hue);
tvError_t GetCurrentComponentHue(tvDataComponentColor_t blHueColor, int *hue);
tvError_t SetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int Luma);
tvError_t GetCurrentComponentLuma(tvDataComponentColor_t blLumaColor, int *Luma);
tvError_t GetTVSupportedDimmingModes(char **dimmingModes,unsigned short *count);
tvError_t SetTVDimmingMode(const char *dimmingMode);

tvError_t GetTVBacklightGlobalFactor(int * value);
tvError_t SetTVBacklightGlobalFactor(int value, int rangeMidPointValue);
tvPictureMode_t GetTVPictureModeIndex(const char * pictureMode);
tvVideoHDRFormat_t GetCurrentContentFormat(void);
tvError_t GetSupportedContentFormats(unsigned int * contentFormats,unsigned short *numberOfFormats);

tvError_t ResetBrightness(int defaultValue,bool resetForAllFormats);
tvError_t ResetContrast(int defaultValue,bool resetForAllFormats);
tvError_t ResetSharpness(int defaultValue,bool resetForAllFormats);
tvError_t ResetSaturation(int defaultValue,bool resetForAllFormats);
tvError_t ResetHue(int defaultValue,bool resetForAllFormats);
tvError_t ResetBacklight(int defaultValue,bool resetForAllFormats);
tvError_t ResetColorTemperature(int defaultValue,bool resetForAllFormats);
tvError_t ResetComponentSaturation(int color,int defaultValue);
tvError_t ResetComponentLuma(int color,int defaultValue);
tvError_t ResetComponentHue(int color,int defaultValue);

bool isCurrentTypeSDR(void);
bool isCurrentTypeHDR(void);
bool isCurrentHDRTypeIsSDR(void);
int GetPanelID(char* panelid);
void GetDefaultPanelID(char *panelID);

tvError_t SaveColorTemperature(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveBacklight(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveContrast(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveSaturation(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveSharpness(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveBrightness(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveHue(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveDynamicBacklight(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveDisplayMode(int sourceInput, int pq_mode,int hdr_type,int value);
tvError_t SaveCMS(int sourceInput, int pq_mode,int hdr_type,int tunnel_type,int color_type,int value);
tvError_t SaveDolbyMode(int sourceInput, int pq_mode,int hdr_type,int value);
int GetNumberOfModesupported(void);
int GetCurrentPQIndex(void);
void GetAllSupportedPicModeIndex(int pic_mode_index[]);
int GetCMSDefault(tvCMS_tunel_t color_tunel_type);
int GetDolbyModeIndex(const char * dolbyMode);
int ConvertVideoFormatToHDRFormat(tvVideoHDRFormat_t videoFormat);
int ConvertTVColorToVendorColor(tvDataComponentColor_t blComponentColor);
int ConvertHDRFormatToContentFormat(tvhdr_type_t hdrFormat);
int GetCustomPQModeIndex(void);
tvError_t SetCMSState(tvCMS_tunel_t tunelType,tvcomponent_color_type_t colorType,tvcomponent_state_t componentState);
int GetWBRgbType(const char *color, const char * ctrl);
tvError_t SetColorTemperatureUser(int rgbType, int value);
tvError_t SaveColorTemperatureUser(int rgbType, int value,int boost);
tvError_t SetBacklightInfo(tvBacklightInfo_t *backlightDefaults);
int GetDriverEquivalentBLForCurrentFmt(int backlight);
int GetHLGModeIndex(const char * hlgMode);
int GetHDR10ModeIndex(const char * hdr10Mode);
tvError_t SetBacklightFade(int from,int to,int duration);
tvError_t ReadAllModeConfigfile(const char *file, char *cpybuffer, const char *searchstring);
void splitstringsfrombuffer(char *buffer, char *availableModes, unsigned short *totalcount);
void splitstringsandvaluefrombuffer(char *buffer, pic_modes_t *availableModes[], unsigned short *totalcount);
tvError_t SetGammaMode(int mode);
tvError_t SetLocalDimmingLevel(int localDimmingLevel);
tvError_t GetLocalDimmingLevel(int *localDimmingLevel);
tvError_t SaveLocalDimmingLevel(int sourceInput, int pq_mode,int hdr_type,int value);
void SwitchEDID(int pqmode);
tvError_t UpdateEDIDAndSetDimmingLevel(int dimmingLevel,int pqmode);
void GetLDIMAndEDIDLevel(int dimmingMode,int format,int *dimmingLevel, int *edidLevel,int pqmode);
tvError_t SaveLowLatencyState( int sourceInput, int pq_mode,int hdr_type,int value );
tvError_t SetLowLatencyState( int lowLatencyIndex );
tvError_t GetLowLatencyState(int *lowlatencystate);
tvError_t SetGammaTable(unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);
tvError_t GetGammaTable(int colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);
tvError_t SaveGammaTable(int colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);
tvError_t SetGammaPattern(int is_10_bit, int R_Value, int G_Value, int B_Value);

//Gamma
tvError_t SetGammaTable(unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);
tvError_t GetGammaTable(int colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);
tvError_t SaveGammaTable(int colortemp, unsigned short *pData_R, unsigned short *pData_G, unsigned short *pData_B, unsigned short size);
tvError_t SetGammaPattern(int is_10_bit, int R_Value, int G_Value, int B_Value);

void SetGammaTestPoint( int length, unsigned short gamma[ ]);
void getGammaTestPoint( int *length, unsigned short gamma[]);
void GetTVGammaTarget(int colorTemp,double *x, double *y);
int GetMaxGainValue();

//Tmax
tvError_t SetAmlDvTmaxValue(int value);	
tvError_t GetAmlDvTmaxValue(int *value);
tvError_t SaveAmlDvTmaxValue(LDIM_STATE_INDEX state, int value);

tvError_t GetOpenCircuitStatus(int *status);
tvError_t SetDynamicGamma(double tvGammaValue);

int TVWriteSysfs(const char *path, const char * cmd);
tvError_t SetGammaPatternMode(bool mode);
tvError_t SetLDIMRemap(bool mode);
tvError_t SetWBMode(bool mode);
tvError_t SetLDIM(bool mode);
tvError_t SetLDIMSequenceTest(int mode, int delay);
tvError_t SetDNLPMode(bool mode);
tvError_t SetLCMode(bool mode);
tvError_t setDeviceBoostMode(tvdeviceBoostMode_t mode);

#ifdef __cplusplus
}
#endif

#endif //_TV_SETTINGS_H
