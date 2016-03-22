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

#ifndef __TIZEN_THUMBNAIL_UTIL_H__
#define __TIZEN_THUMBNAIL_UTIL_H__

#include <thumbnail_util_type.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @file thumbnail_util.h
 * @brief This file contains the thumbnail util API and functions related with handling thumbnail. \n
 *        Functions include operations to get the various size thumbnail from media file.
 */

/**
 * @addtogroup CAPI_MEDIA_THUMBNAIL_UTIL_MODULE
 * @{
 */

/**
 * @brief Creates thumbnail info handle.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 * @remarks You must release @a thumb info using thumbnail_util_destroy().
 *
 * @param[in] thumb The handle to thumbnail info
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #THUMBNAIL_UTIL_ERROR_NONE Successful
 * @retval #THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #THUMBNAIL_UTIL_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @retval #THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED Permission denied
 *
 * @post Created handle should be released using thumbnail_util_destroy() API.
 */
int thumbnail_util_create(thumbnail_h *thumb);

/**
 * @brief Extracts the thumbnail for the given media, asynchronously.
 * @details This function extracts the thumbnail for given media item and calls registered
 *         callback function for completion of extracting the thumbnail.\n
 *
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 *
 * @remarks You must release @a request_id using free(). \n
 *                http://tizen.org/privilege/mediastorage is needed if input or output path are relevant to media storage. \n
 *                http://tizen.org/privilege/externalstorage is needed if input or output path are relevant to external storage. \n
 *                If you don't set the size, the thumbnail size will be set default size. Default size is 320x240. \n
 *                Color space of the generated thumbnail is BGRA. \n
 *                Since 3.0, http://tizen.org/privilege/content.write privilege is not required. \n
 *
 * @param[in] thumb     The thumbnail info handle
 * @param[in] callback  The callback function to be invoked
 * @param[in] user_data The user data to be passed to the callback function
 * @param[out] request_id The request id for the thumbnail extraction request
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #THUMBNAIL_UTIL_ERROR_NONE              Successful
 * @retval #THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre Create a thumbnail info handle by calling thumbnail_util_create(). \n
 *           The content path that you want to generate thumbnail must be set by calling thumbnail_util_set_path().
 *
 * @post Thumbnail extraction result except canceled is provided by thumbnail_extracted_cb.
 */
int thumbnail_util_extract(thumbnail_h thumb, thumbnail_extracted_cb callback, void *user_data, char **request_id);

/**
 * @brief Sets the path of original media file.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 *
 * @param[in] thumb     The thumbnail info handle
 * @param[in] path        The path of the original media file
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #THUMBNAIL_UTIL_ERROR_NONE              Successful
 * @retval #THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre Create a thumbnail info handle by calling thumbnail_util_create().
 * @see Set the thumbnail size you want by calling thumbnail_util_size().
 * @post Extract the thumbnail by calling thumbnail_util_extract().
 */
int thumbnail_util_set_path(thumbnail_h thumb, const char *path);

/**
 * @brief Sets the size of thumbnail to be extracted.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 * @remarks If you don't set the size, the thumbnail size will be set default size. Default size is 320x240. \n
 *                  If the set width is not a multiple of 8, it can be changed by inner process. the width will be a multiple of 8 greater than the set value.
 *
 * @param[in] thumb    The thumbnail info handle
 * @param[in] width      The width of the thumbnail
 * @param[in] height     The height of the thumbnail
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #THUMBNAIL_UTIL_ERROR_NONE              Successful
 * @retval #THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre Create a thumbnail info handle by calling thumbnail_util_create().
 *
 * @post Extract the thumbnail by calling thumbnail_util_extract().
 */
int thumbnail_util_set_size(thumbnail_h thumb, int width, int height);

/**
 * @brief Cancels the thumbnail extraction request for the given media.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 * @remarks If there is no item you want to cancel, this API return MEDIA_CONTENT_ERROR_INVALID_OPERATION
 *
 * @param[in] thumb         The media thumbnail info handle
 * @param[in] request_id   The generated request id by thumbnail extraction request
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #THUMBNAIL_UTIL_ERROR_NONE              Successful
 * @retval #THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre Create a thumbnail info handle by calling thumbnail_util_create().
 */
int thumbnail_util_cancel(thumbnail_h thumb, const char *request_id);

/**
 * @brief Cancels all thumbnail extraction requests associated with the given thumbnail info handle.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 * @remarks If there is no item you want to cancel, this API return MEDIA_CONTENT_ERROR_INVALID_OPERATION
 *
 * @param[in] thumb The media thumbnail info handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #THUMBNAIL_UTIL_ERROR_NONE              Successful
 * @retval #THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre Create a thumbnail info handle by calling thumbnail_util_create().
 */
int thumbnail_util_cancel_all(thumbnail_h thumb);

/**
 * @brief Destroys thumbnail info handle.
 * @details The function frees all resources related to the thumbnail info handle. This handle
 *          can no longer be used to perform any operation. New thumbnail info handle has to
 *          be created before the next usage.
 *
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 *
 * @param[in]  thumb  The thumbnail info handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #THUMBNAIL_UTIL_ERROR_NONE              Successful
 * @retval #THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre Create a thumbnail info handle by calling thumbnail_util_create().
 */
int thumbnail_util_destroy(thumbnail_h thumb);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_THUMBNAIL_UTIL_H__ */
