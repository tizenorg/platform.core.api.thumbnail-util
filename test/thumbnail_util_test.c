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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <glib.h>
#include <thumbnail_util.h>
#include <thumbnail_util_private.h>

#define MAX_SIZE 16
GMainLoop *g_loop = NULL;
char *g_id = NULL;

void thumbnail_completed_cb(thumbnail_util_error_e error, const char *request_id, int raw_width, int raw_height, unsigned char *raw_data, int raw_size, void *user_data)
{
#if 0
	FILE *fp;
	char file_name[MAX_SIZE + 1] = {0, };

	memset(file_name, 0, MAX_SIZE);
	snprintf(file_name, MAX_SIZE, "test_%s.raw", request_id);
	fp = fopen(file_name, "w");
	fwrite(raw_data, 1, raw_size, fp);
	fclose(fp);
#endif
	thumbnail_util_debug("=================[RESULT]");
	thumbnail_util_debug("error_code [%d]", error);
	thumbnail_util_debug("request id [%s]", request_id);
	thumbnail_util_debug("width [%d], height [%d]", raw_width, raw_height);
	thumbnail_util_debug("raw_data [0x%x], size [%d]", *raw_data, raw_size);
#if 0
	if (strncmp(request_id, "50", 2) == 0)
		g_main_loop_quit(g_loop);
#else
	g_main_loop_quit(g_loop);
#endif
}

void __convert_i_to_a(unsigned int request_id, char **req_str)
{
	char *buf = NULL;
	buf = malloc(MAX_SIZE * sizeof(char));

	if (buf != NULL) {
		snprintf(buf, MAX_SIZE, "%d", request_id);
		*req_str = strndup(buf, strlen(buf));
		SAFE_FREE(buf);
	}
}

gboolean extract_thumbnail_start(gpointer data)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
#if 0
	int i;
	thumbnail_h test_info;
	thumbnail_util_create(&test_info);
	thumbnail_util_set_size(test_info, 512, 288);

	for (i = 0; i < 50; i++) {
		char filepath[255] = {0,};
		snprintf(filepath, sizeof(filepath), "%s%d.jpg", "/home/owner/content/Images/test_image", i + 1);
		thumbnail_util_debug("File : %s\n", filepath);
		thumbnail_util_set_path(test_info, filepath);
		ret = thumbnail_util_extract(test_info, thumbnail_completed_cb, test_info, &g_id);
		thumbnail_util_debug("GENERATED ID [%s]", g_id);
	}
#else
	thumbnail_h test_info;
	thumbnail_util_create(&test_info);
	thumbnail_util_set_path(test_info, "/home/owner/content/Images/test_image1.jpg");
	/*thumbnail_util_set_size(test_info, 511, 288); */
	ret = thumbnail_util_extract(test_info, thumbnail_completed_cb, test_info, &g_id);
#endif
	thumbnail_util_destroy(test_info);

	if (ret == THUMBNAIL_UTIL_ERROR_NONE)
		thumbnail_util_debug("extract raw data is success");
	else
		thumbnail_util_error("extract raw data is failed");

	return false;
}


gboolean cancel_all(gpointer data)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_h _media_thumb;
	thumbnail_util_create(&_media_thumb);
#if 0
	ret = thumbnail_util_cancel_all(_media_thumb);

	if (ret == THUMBNAIL_UTIL_ERROR_NONE)
		thumbnail_util_debug("thumbnail_util_cancel_all is success");
	else
		thumbnail_util_error("thumbnail_util_cancel_all is failed");
#else
	int i, num;
	num = atoi(g_id);
	char *req_str = NULL;
	for (i = num - 20; i < num; i++) {
		__convert_i_to_a(i, &req_str);
		ret = thumbnail_util_cancel(_media_thumb, req_str);
		if (ret == THUMBNAIL_UTIL_ERROR_NONE)
			thumbnail_util_debug("thumbnail_util_cancel[%d] is success", i);
		else
			thumbnail_util_error("thumbnail_util_cancel[%d] is failed", i);
	}
#endif
	thumbnail_util_destroy(_media_thumb);

	return false;
}

int test_extract_thumbnail(bool cancel)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	GSource *source = NULL;
	GMainContext *context = NULL;

	g_loop = g_main_loop_new(NULL, false);
	context = g_main_loop_get_context(g_loop);
	source = g_idle_source_new();
	g_source_set_callback(source, extract_thumbnail_start, NULL, NULL);
	g_source_attach(source, context);

	/* Logic to cancel */
	if (cancel) {
		GSource *cancel_src = NULL;
		cancel_src = g_idle_source_new();
		g_source_set_callback(cancel_src, cancel_all, NULL, NULL);
		g_source_attach(cancel_src, context);
	}

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	return ret;
}

int main(int argc, char *argv[])
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	thumbnail_util_debug("--- Thumbnail util test start ---\n\n");

	ret = test_extract_thumbnail(false);
	if (ret != THUMBNAIL_UTIL_ERROR_NONE)
		return ret;

	thumbnail_util_debug("--- Thumbnail util test end ---\n");

	return ret;
}
