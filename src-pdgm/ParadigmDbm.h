#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

namespace gwr::frqz
{

class ParadigmDbm
{
  public:
    ParadigmDbm();
    ParadigmDbm(std::string &dbName);
};

} // namespace gwr::frqz