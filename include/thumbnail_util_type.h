/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
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


#ifndef __TIZEN_THUMBNAIL_UTIL_TYPE_H__
#define __TIZEN_THUMBNAIL_UTIL_TYPE_H__

#include <time.h>
#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifndef DEPRECATED_API
#define DEPRECATED_API __attribute__ ((deprecated))
#endif

/**
 * @file thumbnail_util_type.h
 * @brief This file contains API related to thumbnail_util enumerations for classes of errors. \n
 *        Listed APIs are called when extracting thumbnail from media files,  \n
 */

/**
* @addtogroup CAPI_MEDIA_THUMBNAIL_UTIL_MODULE
 * @{
 */

/**
 * @ingroup CAPI_MEDIA_THUMBNAIL_UTIL_MODULE
 * @brief Enumeration for a thumbnail util error.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 */
typedef enum {
	THUMBNAIL_UTIL_ERROR_NONE                    = TIZEN_ERROR_NONE,                    /**< Successful */
	THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER       = TIZEN_ERROR_INVALID_PARAMETER,       /**< Invalid parameter */
	THUMBNAIL_UTIL_ERROR_OUT_OF_MEMORY           = TIZEN_ERROR_OUT_OF_MEMORY,           /**< Out of memory */
	THUMBNAIL_UTIL_ERROR_INVALID_OPERATION       = TIZEN_ERROR_INVALID_OPERATION,       /**< Invalid Operation */
	THUMBNAIL_UTIL_ERROR_FILE_NO_SPACE_ON_DEVICE       = TIZEN_ERROR_FILE_NO_SPACE_ON_DEVICE, /**< No space left on device */
	THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED		= TIZEN_ERROR_PERMISSION_DENIED,		  /**< Permission denied */
} thumbnail_util_error_e;


/**
 * @ingroup CAPI_MEDIA_THUMBNAIL_UTIL_MODULE
 * @brief The structure type for the thumbnail info handle.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 */
typedef struct thumbnail_s *thumbnail_h;


/**
 * @ingroup CAPI_MEDIA_THUMBNAIL_UTIL_MODULE
 * @brief Called when creating the thumbnail.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 * @remarks Color space of the generated thumbnail is BGRA.
 *
 * @details This callback is called for completion of generating the thumbnail.
 *
 * @param[in] error     The error code
 * @param[in] request_id       The generated request id by thumbnail extraction request
 * @param[in] thumb_width    The width of the thumbnail which is generated
 * @param[in] thumb_height   The height of the thumbnail which is generated
 * @param[in] thumb_data     The raw data of the thumbnail which is generated
 * @param[in] thumb_size      The size of the thumbnail which is generated
 * @param[in] user_data        The user data passed from the thumbnail_util_extract() fuction
 *
 * @pre thumbnail_util_extract()
 *
 * @see thumbnail_util_extract()
 */
typedef void (*thumbnail_extracted_cb)(thumbnail_util_error_e error, const char *request_id, int thumb_width, int thumb_height, unsigned char *thumb_data, int thumb_size, void *user_data);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /*__TIZEN_THUMBNAIL_UTIL_TYPE_H__*/
