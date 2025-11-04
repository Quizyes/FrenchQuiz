#include "PdgmApp.h"

using namespace visage::dimension;

namespace gwr::frqz
{
PdgmApp::PdgmApp() : dbm(std::string{":memory:"}) {}

void PdgmApp::newQuiz()
{
    std::string d;
    newQuiz(d);
}

void PdgmApp::newQuiz(std::string &inverb)
{
    if (!inverb.empty())
    {
        auto likeV = replaceAccents(inverb);
        auto st = dbm.getStmt("select infinitive from frenchVerbs where infinitive like ?;");
        st.bind(1, likeV);
    }
}

void PdgmApp::markQuiz() {}

void PdgmApp::compare() {}

std::string PdgmApp::replaceAccents(std::string &verb) { return std::string(); }

} // namespace gwr::frqz