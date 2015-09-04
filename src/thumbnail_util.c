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

#include <media-thumbnail.h>
#include <thumbnail_util.h>
#include <thumbnail_util_private.h>

#define MAX_SIZE 16

void __thumbnail_util_convert_itoa(int request_id, char **req_str)
{
	char *buf = NULL;

	buf = malloc(MAX_SIZE * sizeof(char));

	if (buf != NULL) {
		snprintf(buf, MAX_SIZE, "%d", request_id);
		*req_str = strndup(buf, strlen(buf));
		SAFE_FREE(buf);
	}
}
void __thumbnail_util_extract_completed_cb(int error, int request_id, const char *path, int thumb_width, int thumb_height, unsigned char *thumb_data, int thumb_size, void *user_data)
{
	thumbnail_extract_cb_s *_thumb_cb = (thumbnail_extract_cb_s *)user_data;
	char *request_id_str = NULL;

	if (_thumb_cb != NULL) {
		/*media_content_debug("error [%d], thumbnail_size [%d]", error, thumb_size); */
		__thumbnail_util_convert_itoa(request_id, &request_id_str);
		if (_thumb_cb->thumb_extract_cb) {
			_thumb_cb->thumb_extract_cb(error, request_id_str, thumb_width, thumb_height, thumb_data, thumb_size, _thumb_cb->user_data);
		}
	}
	SAFE_FREE(_thumb_cb);
}

int thumbnail_util_create(thumbnail_h *thumb)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	if (thumb == NULL) {
		thumbnail_util_error("INVALID_PARAMETER(0x%08x)", THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);
		return THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER;
	}

	thumbnail_s *_thumb = (thumbnail_s *)malloc(sizeof(thumbnail_s));
	if (_thumb == NULL) {
		thumbnail_util_error("OUT_OF_MEMORY(0x%08x)", THUMBNAIL_UTIL_ERROR_OUT_OF_MEMORY);
		return THUMBNAIL_UTIL_ERROR_OUT_OF_MEMORY;
	}

	_thumb->request_id = 0;
	_thumb->file_path = NULL;
	_thumb->dst_width = 0;
	_thumb->dst_height = 0;
	_thumb->thumb_size = 0;
	_thumb->thumb_data = NULL;

	*thumb = (thumbnail_h)_thumb;

	return ret;
}

int thumbnail_util_extract(thumbnail_h thumb, thumbnail_extracted_cb callback, void *user_data, char **request_id)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	static int g_thumbnail_req_id = 0;
	thumbnail_s *_thumb = (thumbnail_s *)thumb;

	if (_thumb != NULL && STRING_VALID(_thumb->file_path)) {
		g_thumbnail_req_id++;
		_thumb->request_id = g_thumbnail_req_id;
		__thumbnail_util_convert_itoa(_thumb->request_id, request_id);
		thumbnail_extract_cb_s *_thumb_cb = (thumbnail_extract_cb_s *)calloc(1, sizeof(thumbnail_extract_cb_s));

		if (_thumb_cb != NULL) {
			_thumb_cb->handle = _thumb;
			_thumb_cb->user_data = user_data;
			_thumb_cb->thumb_extract_cb = callback;
		}

		if (_thumb->dst_width == 0 || _thumb->dst_height == 0) {
			_thumb->dst_width = 320;
			_thumb->dst_height = 240;
		}

		ret = thumbnail_request_extract_raw_data_async(_thumb->request_id, _thumb->file_path, _thumb->dst_width, _thumb->dst_height, (ThumbRawFunc)__thumbnail_util_extract_completed_cb, (void *)_thumb_cb, tzplatform_getuid(TZ_USER_NAME));
	} else {
		thumbnail_util_error("INVALID_PARAMETER(0x%08x)", THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);
		ret = THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int thumbnail_util_set_path(thumbnail_h thumb, const char *path)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_s *_thumb = (thumbnail_s *)thumb;

	if (_thumb != NULL && path != NULL) {
		if (_thumb->file_path)
			SAFE_FREE(_thumb->file_path);
		_thumb->file_path = strndup(path, strlen(path));
	} else {
		thumbnail_util_error("INVALID_PARAMETER(0x%08x)", THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);
		ret = THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int thumbnail_util_set_size(thumbnail_h thumb, int width, int height)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_s *_thumb = (thumbnail_s *)thumb;

	if (_thumb != NULL && width > 0 && height > 0) {
		_thumb->dst_width = width;
		_thumb->dst_height = height;
	} else {
		thumbnail_util_error("INVALID_PARAMETER(0x%08x)", THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);
		ret = THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int thumbnail_util_cancel(thumbnail_h thumb, const char *request_id)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_s *_thumb = (thumbnail_s *)thumb;

	if (_thumb != NULL && STRING_VALID(request_id)) {
		unsigned int request_id_integer = atoi(request_id);
		ret = thumbnail_request_cancel_raw_data(request_id_integer, tzplatform_getuid(TZ_USER_NAME));
	} else {
		thumbnail_util_error("INVALID_PARAMETER(0x%08x)", THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);
		ret = THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int thumbnail_util_cancel_all(thumbnail_h thumb)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_s *_thumb = (thumbnail_s *)thumb;

	if (_thumb != NULL) {
		ret = thumbnail_request_cancel_all(true, tzplatform_getuid(TZ_USER_NAME));
	} else {
		thumbnail_util_error("INVALID_PARAMETER(0x%08x)", THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);
		ret = THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER;
	}

	return ret;
}


int thumbnail_util_destroy(thumbnail_h thumb)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_s *_thumb = (thumbnail_s *)thumb;

	if (_thumb) {
		SAFE_FREE(_thumb->file_path);
		SAFE_FREE(_thumb->thumb_data);
		SAFE_FREE(_thumb);
	} else {
		thumbnail_util_error("INVALID_PARAMETER(0x%08x)", THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);
		ret = THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER;
	}

	return ret;
}
