//
//  SettingUtils.h
//  Translator
//
//  Created by Acane on 2022/5/19.
//

#ifndef SettingUtils_h
#define SettingUtils_h

#include "ac_common.h"
#include "ac_settings.h"

#include <string>
#include <sstream>
#include <type_traits>

ac_result_t getSettingS(const char* id, const char* name, std::string& value) {
    const char* v;
    ac_result_t ret = ac_settings_get(ac_settings_settings_name(id, name), &v);
    if (ret == AC_FAIL || v == nullptr) return ret;
    value = v;
    return ret;
}

template <class T>
T getSettings(const char* id, const char* name, T default_value) {
    std::string value;
    getSettingS(id, name, value);
    if (value == "") {
        return default_value;
    }
    try {
        if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>) {
            T val;
            std::stringstream ss;
            ss << value;
            ss >> val;
            if (!ss.eof()) {
                throw std::runtime_error("not convertible: " + value);
            }
            return val;
        }
        else if constexpr (std::is_convertible<T, int>::value) {
            T val = std::stoi(value);
            return val;
        }
        else {
            return value;
        }
    }
    catch (std::exception& e) {
        printf("error while cast type: %s\n", e.what());
    }
    return default_value;
}

#endif /* SettingUtils_h */
