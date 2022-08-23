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

#ifndef _TV_LOG_H
#define _TV_LOG_H


#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** Error Log definition */
#define ERROR(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "ERROR", ##__VA_ARGS__);}while(0);
/** INFO log definition */
#define INFO(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "INFO", ##__VA_ARGS__);}while(0);

//#define DEBUG_ENABLED
#ifdef DEBUG_ENABLED
/** Debug log definition */
#define DEBUG(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "DEBUG", ##__VA_ARGS__);}while(0);
#else
#define DEBUG(text, ...) /** Debug log definition if DEBUG_ENABLED is false
#endif


#ifdef __cplusplus
}
#endif

#endif //_TV_LOG_H
