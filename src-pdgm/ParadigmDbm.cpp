//////////////////////////////////////////////////////////////////////////
//                                                                      //
// French Quiz - a suite of apps for learning the French verb.          //
//                                                                      //
// Copyright 2025, Greg Recco                                           //
//                                                                      //
// French Quiz is released under the GNU General Public Licence v3      //
// or later (GPL-3.0-or-later). The license is found in the "LICENSE"   //
// file in the root of this repository, or at                           //
// https://www.gnu.org/licenses/gpl-3.0.en.html                         //
//                                                                      //
// The source code repository for French Quiz is available at           //
// https://github.com/Quizyes/FrenchQuiz                                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

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