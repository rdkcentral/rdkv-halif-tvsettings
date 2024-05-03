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
 * @addtogroup BL_Table BL Table Module
 * @{
 */


/**
* @addtogroup BL_Table_HAL BL Table HAL
* @{
*/

/**
* @defgroup BL_Table_H BL Table Header
* @{
*/

#ifndef __BL_TABLE_INFO_H
#define __BL_TABLE_INFO_H
#define BACKLIGHT_FILE_NAME  "backlight_values.ini"
const int defaultSDR = 50;
const int defaultHDR = 100;
#endif /*__BL_TABLE_INFO_H */

/** @} */ // End of BL_Table_H
/** @} */ // End of BL_Table_HAL
/** @} */ // End of BL_Table
/** @} */ // End of HPK
