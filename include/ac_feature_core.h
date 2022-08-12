/*! \file ac_feature_core.h */

/*
 * This header file is used to provide additional custom services for
 * this software.
 * This header file defines interface of functions you need to implement
 *
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
 *
 *
 * Note:
 *  1. the identifier of feature is in the name of dylib
 *         e.g.   if a feature's identifier is `my_feature`, it means the file
 *               name of this plugin is `libmy_feature.dylib`.
 *  2. the exported dylib should contains both x86_64 and arm64 version
 *  3. Do not read/write files from outside of sandbox directory
 *  4. Export to C-linkage of your function is required, i.e., using extern "C"
 *     is required.
 * */

#ifndef TRANSLATOR_AC_FEATURE_CORE_H
#define TRANSLATOR_AC_FEATURE_CORE_H

#include "ac_common.h"

ACANE_EXTERN_C_START

typedef const char* ac_json_string_t;

/// ====== Definition for Handler ======

/// Call to initialize this plugin
typedef ac_result_t (*ac_translate_init_handler_t)();

/// Call to de-initialize the plugin
typedef ac_result_t (*ac_translate_deinit_handler_t)();

/// Do translate handler
/// \param input     [IN]  Input content in JSON format
/// \return Translated content in JSON format
typedef ac_result_t (*ac_translate_do_handler_t)(ac_json_string_t input_json, ac_json_string_t* output_json);

/// Get meta information handler
/// \param meta_json   [OUT]  Json string of meta info
/// \return A JSON represents meta information of a translate service
typedef ac_result_t (*ac_translate_get_meta_info_handler_t)(ac_json_string_t* meta_json);

/// Give the information about database path
typedef void (*ac_report_db_location_handler_t)(const char* path);

ACANE_EXTERN_C_END

#endif //TRANSLATOR_AC_FEATURE_CORE_H
