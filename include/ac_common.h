/*! \file ac_common.h */

/*
 *    Copyright (C) 2020  Acane
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * */

#ifndef LOCALOCR_AC_COMMON_H
#define LOCALOCR_AC_COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>

enum ACANE_RESULT :uint32_t {
    AC_OK = 0,                          // Success
    AC_FAIL = 1                         // Failed
};

typedef enum ACANE_RESULT ac_result_t;

// ===== Log library =====

#define DEFAULT_TAG ACANE

#define LOG_(level, tag, fmt, ...)  do { \
    time_t t; time(&t);\
    struct tm * tm_ = localtime(&t);\
    fprintf(stderr, "[%d/%d %s%d:%s%d:%s%d][%s][%s][%s:%d][%s] " fmt "\n", \
        tm_->tm_mon+1, tm_->tm_mday, \
        tm_->tm_hour<10?"0":"",  tm_->tm_hour, \
        tm_->tm_min<10?"0":"", tm_->tm_min, \
        tm_->tm_sec<10?"0":"", tm_->tm_sec,\
        #level, #tag, __FILE_NAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
} while (0)

#define LOGLEVEL_INFO     1
#define LOGLEVEL_WARN     2
#define LOGLEVEL_DEBUG    4
#define LOGLEVEL_ERROR    8

#ifndef AC_LOGLEVEL
#define AC_LOGLEVEL       15
#endif // AC_LOGLEVEL

#define LOGLEVEL_ENABLED(level) ( AC_LOGLEVEL & (level) )

#if LOGLEVEL_ENABLED(LOGLEVEL_DEBUG)
#define LOGD_TAG(tag, fmt, ...) LOG_(DEBUG, tag, fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) LOGD_TAG(DEFAULT_TAG, fmt, ##__VA_ARGS__)
#else
#define LOGD_TAG(tag, fmt, ...)
#define LOGD(fmt, ...)
#endif // LOGLEVEL_ENABLED(LOGLEVEL_DEBUG)

#if LOGLEVEL_ENABLED(LOGLEVEL_WARN)
#define LOGW_TAG(tag, fmt, ...) LOG_(WARN, tag, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) LOGW_TAG(DEFAULT_TAG, fmt, ##__VA_ARGS__)
#else
#define LOGW_TAG(tag, fmt, ...)
#define LOGW(fmt, ...)
#endif // LOGLEVEL_ENABLED(LOGLEVEL_WARN)

#if LOGLEVEL_ENABLED(LOGLEVEL_ERROR)
#define LOGE_TAG(tag, fmt, ...) LOG_(ERROR, tag, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) LOGE_TAG(DEFAULT_TAG, fmt, ##__VA_ARGS__)
#else
#define LOGE_TAG(tag, fmt, ...)
#define LOGE(fmt, ...)
#endif // LOGLEVEL_ENABLED(LOGLEVEL_ERROR)

#if LOGLEVEL_ENABLED(LOGLEVEL_INFO)
#define LOGI_TAG(tag, fmt, ...) LOG_(INFO, tag, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) LOGI_TAG(DEFAULT_TAG, fmt, ##__VA_ARGS__)
#define LOG_TAG(tag, fmt, ...)  LOG_(INFO, tag, fmt, ##__VA_ARGS__)
#define LOG(fmt, ...) LOGI_TAG(DEFAULT_TAG, fmt, ##__VA_ARGS__)
#else
#define LOGI_TAG(tag, fmt, ...)
#define LOGI(fmt, ...)
#define LOG_TAG(tag, fmt, ...)
#define LOG(fmt, ...)
#endif // LOGLEVEL_ENABLED(LOGLEVEL_INFO)

#ifdef __cplusplus
#define ACANE_EXTERN_C          extern "C"
#define ACANE_EXTERN_C_START    extern "C" {
#define ACANE_EXTERN_C_END      };
#else
#define ACANE_EXTERN_C
#define ACANE_EXTERN_C_START
#define ACANE_EXTERN_C_END
#endif

#define ACANE_ATTRIBUTE_VISIBILITY(_visibility) __attribute__((visibility (#_visibility)))

#define ACANE_API_VISIBILITY_DEFAULT  ACANE_ATTRIBUTE_VISIBILITY(default)
#define ACANE_API_VISIBILITY_HIDDEN   ACANE_ATTRIBUTE_VISIBILITY(hidden)
#define ACANE_API ACANE_API_VISIBILITY_DEFAULT

#endif //LOCALOCR_AC_COMMON_H
