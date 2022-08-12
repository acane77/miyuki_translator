/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * */

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
