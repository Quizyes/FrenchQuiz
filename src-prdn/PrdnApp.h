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
#include <visage_widgets/button.h>
#include <visage_ui/popup_menu.h>
#include <visage_utils/dimension.h>
#include <visage_file_embed/embedded_file.h>
#include <embedded/fonts.h>
#include <emscripten.h>
#include "DbManager.h"
#include "Label.h"
#include "Prompt.h"

namespace gwr::frqz
{

class PrdnApp : public visage::ApplicationWindow
{
  public:
    PrdnApp();
    DbManager dbm;
    void newQuiz();
    void newQuiz(int lesson);
    void markQuiz();
    void compare();
    void draw(visage::Canvas &canvas) override;

    bool userInputIsShown{true}; // true when fields show USER input
    bool quizIsMarked{false};

    visage::Font font{55, visage::fonts::Lato_Regular_ttf};
    visage::Frame header, colHead, body;
    Label lessonLabel;
    visage::TextEditor lesson;
    int currentLesson{10}; // default max
    visage::UiButton helpBtn{"?"}, newBtn{"New"}, markBtn{"Mark"}, cmpBtn{"Compare"},
        optionsBtn{"Options"};
    Label formCol, headCol, parseCol;
    Prompt q1, q2, q3, q4, q5, q6, q7, q8;
    std::array<Prompt *, 8> items;
    std::map<int, std::map<bool, std::string>> optStrs;
    std::map<int, bool> optBools;
};

} // namespace gwr::frqz