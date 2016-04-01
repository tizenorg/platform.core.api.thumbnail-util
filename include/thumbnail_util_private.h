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



#ifndef __TIZEN_THUMBNAIL_UTIL_PRIVATE_H__
#define __TIZEN_THUMBNAIL_UTIL_PRIVATE_H__


#include <unistd.h>
#include <asm/unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <thumbnail_util_type.h>
#include <dlog.h>
#include <tzplatform_config.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "CAPI_MEDIA_THUMBNAIL_UTIL"

#define SAFE_STRLCPY(dst, src, n)	((g_strlcpy(dst, src, n) < n) ? TRUE : FALSE)
#define SAFE_STRLCAT(dst, src, n)	g_strlcat(dst, src, n);
#define SAFE_FREE(src)		{if (src) {free(src); src = NULL; } }
#define STRING_VALID(str)		((str != NULL && strlen(str) > 0) ? TRUE : FALSE)

typedef struct {
	int request_id;
	char *file_path;
	int dst_width;
	int dst_height;
	int thumb_size;
	unsigned char *thumb_data;
} thumbnail_s;

typedef struct {
	thumbnail_s *handle;
	thumbnail_extracted_cb thumb_extract_cb;
	void *user_data;
} thumbnail_extract_cb_s;

#define FONT_COLOR_RESET    "\033[0m"
#define FONT_COLOR_RED      "\033[31m"
#define FONT_COLOR_GREEN    "\033[32m"
#define FONT_COLOR_YELLOW   "\033[33m"
#define FONT_COLOR_BLUE     "\033[34m"
#define FONT_COLOR_PURPLE   "\033[35m"
#define FONT_COLOR_CYAN     "\033[36m"
#define FONT_COLOR_GRAY     "\033[37m"

#define thumbnail_util_gettid() syscall(__NR_gettid)

#define thumbnail_util_retv_if(expr, val) do { \
		if (expr) { \
			LOGE(FONT_COLOR_RED"[%d]", media_content_gettid());    \
			return (val); \
		} \
	} while (0)

#define thumbnail_util_debug(fmt, arg...) do { \
		LOGD(FONT_COLOR_RESET"[%d]"fmt"", thumbnail_util_gettid(), ##arg);     \
	} while (0)

#define thumbnail_util_info(fmt, arg...) do { \
		LOGI(FONT_COLOR_GREEN"[%d]"fmt"", thumbnail_util_gettid(), ##arg);     \
	} while (0)

#define thumbnail_util_error(fmt, arg...) do { \
		LOGE(FONT_COLOR_RED"[%d]"fmt"", thumbnail_util_gettid(), ##arg);     \
	} while (0)

#define thumbnail_util_debug_func() do { \
		LOGD(FONT_COLOR_RESET"[%d]", thumbnail_util_gettid());     \
	} while (0)

#define thumbnail_util_sec_debug(fmt, arg...) do { \
		SECURE_LOGD(FONT_COLOR_RESET"[%d]"fmt"", thumbnail_util_gettid(), ##arg);     \
	} while (0)

#define thumbnail_util_sec_warn(fmt, arg...) do { \
		SECURE_LOGW(FONT_COLOR_GREEN"[%d]"fmt"", thumbnail_util_gettid(), ##arg);     \
	} while (0)

#define thumbnail_util_sec_error(fmt, arg...) do { \
		SECURE_LOGE(FONT_COLOR_RED"[%d]"fmt"", thumbnail_util_gettid(), ##arg);     \
	} while (0)

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*__TIZEN_THUMBNAIL_UTIL_PRIVATE_H__*/
