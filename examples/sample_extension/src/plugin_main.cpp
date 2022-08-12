#include "ac_common.h"
#include "ac_feature_core.h"
#include "ac_database.h"
#include "ac_settings.h"

#include <iostream>

char database_path[256];
bool database_opened = false;

ACANE_EXTERN_C_START

ac_result_t ac_init() {
    // Write code here to do actions to initialize resources...
    // open dataase connection
    ac_result_t ret = ac_sqlite_init(database_path);
    if (ret != AC_OK) {
        LOGE("failed to open database");
        return ret;
    }
    database_opened = true;
    return AC_OK;
}

ac_result_t ac_deinit() {
    // Write code here to free or release resources
    if (database_opened) {
        database_opened = false;
        ac_sqlite_deinit();
    }
    return AC_OK;
}

ac_result_t ac_do_translate(ac_json_string_t input_json, ac_json_string_t* output_json) {
    // Write code here to translate from input and save result to output
    *output_json = R"sample(
        {
           "code": 0,
           "message": "ok",
           "result": "hello world"
         }
    )sample";
    return AC_OK;
}

ac_result_t ac_get_meta_info(ac_json_string_t* meta_json) {
    // Write codes here to specify meta info, as following
    // See documentation for more details
    *meta_json = R"sample(
    {
    "name": "My Extension",
    "language_codes": ["zh", "en"],
    "en_code": "en",
    "zh_code": "zh",
    "i18n": {
        "zh": { "zh": "中文", "en": "Chinese" },
        "en": { "zh": "英语", "en": "English" }
    },
    "support_auto": true,
    "config": {
        
    }
})sample";
    return AC_OK;
}

void ac_report_db_location(const char* path) {
    strcpy(database_path, path);
}

ACANE_EXTERN_C_END
