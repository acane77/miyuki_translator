/*! \file ac_feature_core.h */

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
