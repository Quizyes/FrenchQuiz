#pragma once
#include <visage_file_embed/embedded_file.h>
#include "embedded/mydbs.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <sqlite3.h>

namespace gwr::frqz
{

class ParadigmDbm
{
  public:
    SQLite::Database db;
    ParadigmDbm(std::string dbName);
    SQLite::Statement getStmt(std::string sql);
};

} // namespace gwr::frqz