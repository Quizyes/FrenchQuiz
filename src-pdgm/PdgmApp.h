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

#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/fonts.h"
#include "Conjugation.h"
#include "ParadigmDbm.h"

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
    std::string replaceAccents(std::string &verb);
    Conjugation cPres, cImpf, cPs, cImperat, cFut, cCond, cSubjPres, cSubjPast;
    bool userInputIsShown{true}, quizIsMarked{false};
    visage::Font font{50, resources::fonts::Lato_Regular_ttf};
    ParadigmDbm dbm;
};

} // namespace gwr::frqz