#include "ParadigmDbm.h"
namespace gwr::frqz
{

ParadigmDbm::ParadigmDbm(std::string dbName)
    : db(dbName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    int rv = sqlite3_deserialize(db.getHandle(), "main",
                                 (unsigned char *)resources::dbs::paradigms_db.data,
                                 resources::dbs::paradigms_db.size,
                                 resources::dbs::paradigms_db.size, SQLITE_DESERIALIZE_RESIZEABLE);
}

SQLite::Statement ParadigmDbm::getStmt(std::string sql) { return SQLite::Statement{db, sql}; }

} // namespace gwr::frqz