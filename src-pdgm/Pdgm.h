#pragma once

#include <visage_app/application_window.h>
#include "DbManager.h"
#include <visage_file_embed/embedded_file.h>
#include "embedded/fonts.h"
#include "Conjugation.h"

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
    Conjugation cPres, cImpf, cPs, cImperat, cFut, cCond, cSubjPres, cSubjPast;
    bool userInputIsShown{true}, quizIsMarked{false};
    visage::Font font{50, resources::fonts::Lato_Regular_ttf};
    DbManager dbm;
};

} // namespace gwr::frqz