#pragma once

#include <visage_app/application_window.h>
#include "DbManager.h"

namespace gwr::frqz
{

class PdgmApp : public visage::ApplicationWindow
{
  public:
    PdgmApp();
    void newQuiz();
    void newQuiz(std::string &inverb);
    void markQuiz();
    void compare();
    bool userInputIsShown{true}, quizIsMarked{false};
    DbManager dbm;
};

} // namespace gwr::frqz