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

#ifndef _TV_ERROR_H
#define _TV_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum {
    tvERROR_NONE = 0,
    tvERROR_GENERAL,
    tvERROR_OPERATION_NOT_SUPPORTED,
    tvERROR_INVALID_PARAM,
    tvERROR_INVALID_STATE
}tvError_t;

#ifdef __cplusplus
}
#endif

#endif //_TV_ERROR_H
