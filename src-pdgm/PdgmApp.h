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

#pragma once

#include <iostream>
#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include <visage_widgets/button.h>
#include "Conjugation.h"
#include "ParadigmDbm.h"
#include "Utils.h"

namespace gwr::frqz
{

class PdgmApp : public visage::ApplicationWindow
{
  public:
    PdgmApp();
    void draw(visage::Canvas &canvas) override;
    void newQuiz();
    void newQuiz(std::string &inverb);
    void markQuiz();
    void compare();
    SQLite::Statement getQuery(std::string &inverb);
    std::string replaceAccents(std::string verb);
    std::string replaceUnaccented(std::string verb);
    std::vector<std::string> splitForms(std::string &entry);
    visage::Frame header, body, left, right;
    Conjugation cPres, cImpf, cPs, cImper, cFut, cCond, cSubjPres, cSubjImpf;
    std::array<Conjugation *, 8> cs;
    visage::UiButton newBtn{"New"}, markBtn{"Mark"}, cmpBtn{"Compare"};
    visage::TextEditor headword;
    bool userInputIsShown{true}, quizIsMarked{false};
    visage::Font font{80, visage::fonts::Lato_Regular_ttf};
    ParadigmDbm dbm;
    Label quizUnderway;
};

} // namespace gwr::frqz