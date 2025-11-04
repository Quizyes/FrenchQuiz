#pragma once
#include <visage_file_embed/embedded_file.h>
#include "embedded/dbs.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <sqlite3.h>

namespace gwr::frqz
{

class ParadigmDbm
{
  public:
    ParadigmDbm(std::string dbName);
    SQLite::Database db;
    SQLite::Statement getStmt(std::string sql);
};

} // namespace gwr::frqz