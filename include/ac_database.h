/*! \file ac_database.h */

#ifndef ACANE_DATABASE_H
#define ACANE_DATABASE_H

#include "ac_common.h"
#include "sqlite3.h"

ACANE_EXTERN_C_START

typedef void* ac_sqlite_connection_t;
typedef void* ac_result_table_t;

/// Initialize SQLite database
/// \param path   [IN] path to sqlite database
/// \return
ACANE_API
ac_result_t ac_sqlite_init(const char* path);

/// Deinit SQLite database
/// \return
ACANE_API
ac_result_t ac_sqlite_deinit();

/// Get SQLite database connection
/// \param conn   [OUT] pointer to object to receive object
/// \return
ACANE_API
ac_result_t ac_sqlite_get_connection(ac_sqlite_connection_t* conn);

ACANE_API
sqlite3* ac_sqlite3_get_object();

ACANE_EXTERN_C_END

#endif //ACANE_DATABASE_H
