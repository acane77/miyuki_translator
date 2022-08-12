/*! \file ac_settings.h */

//
//  ac_settings.h
//  Translator
//
//  Created by Acane on 2022/2/8.
//

/*
    Copyright (C) 2022  Acane

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

#ifndef ac_settings_h
#define ac_settings_h

#include "ac_common.h"
#include "ac_database.h"

ACANE_EXTERN_C_START

/// Settings for native plugin
typedef struct ACANE_SETTINGS {
    int id;
    const char* name;
    const char* value;
} ac_settings_t;

/// Add settings, called by ac_settings_set()
/// \param name    name of setting
/// \param value   value of setting
/// \return AC_OK or AC_FAIL
ACANE_API
ac_result_t ac_settings_add(const char* name, const char* value);

/// Remove specified setting
/// @param name    name of setting
/// @return AC_OK or AC_FAIL
ACANE_API
ac_result_t ac_settings_remove(const char* name);

/// Set value for setting
/// \param name    name of setting
/// \param value   value of setting
/// \return AC_OK or AC_FAIL
ACANE_API
ac_result_t ac_settings_set(const char* name, const char* value);

/// Get value of setting
/// @param name    name of setting
/// @param value  [OUT] value of setting (must free manually using ac_settings_free() )
/// @return AC_OK or AC_FAIL
ACANE_API
ac_result_t ac_settings_get(const char* name, const char** value);

/// Delete all settings
/// @return AC_OK or AC_FAIL
ACANE_API
ac_result_t ac_settings_delete_all();

/// Get real hased name by plugin ID and settings name
/// @param id    plugin identifier
/// @param name  setting name
/// @return The hashed setting name (don't free it or use it at parallel or keep using
/// the returned string since the string is store shared for all calls from this function)
ACANE_API
const char* ac_settings_settings_name(const char* id, const char* name);

/// Free string returned from ac_settings_get()
/// @param _ptr   Pointer to resource to free
ACANE_API
void ac_settings_free(const char* _ptr);

/// execute CREATE TABLE
ACANE_API
ac_result_t ac_settings_create_table();

ACANE_EXTERN_C_END

#endif /* ac_settings_h */
