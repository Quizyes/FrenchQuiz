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
#include "DbManager.h"

namespace gwr::frqz
{

class RcgnApp : public visage::ApplicationWindow
{
  public:
    RcgnApp();
    DbManager dbm;
    std::string testOut;

    void newQuiz();
    void loadAlts();
    void markQuiz();

    bool userInputIsShown{true}; // true when fields show USER input
    bool quizIsMarked{false};

    visage::Frame header, colHead, body;
    visage::Font font{55, resources::fonts::Lato_Regular_ttf};
    void draw(visage::Canvas &canvas) override;
};

} // namespace gwr::frqz