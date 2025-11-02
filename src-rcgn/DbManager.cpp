#include "DbManager.h"

namespace gwr::frqz
{

SQLite::Statement DbManager::getStmt(std::string s) { return SQLite::Statement{db, s}; }

DbManager::DbManager(std::string dbFilename)
    : db(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    int rv = sqlite3_deserialize(
        db.getHandle(), "main", (unsigned char *)resources::dbs::recognitions_db.data,
        resources::dbs::recognitions_db.size, resources::dbs::recognitions_db.size,
        SQLITE_DESERIALIZE_RESIZEABLE);
}

} // namespace gwr::frqz