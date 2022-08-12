/*! \file ac_settings.h */

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
