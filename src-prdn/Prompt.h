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

#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include <visage_file_embed/embedded_file.h>
#include <embedded/fonts.h>
#include "Label.h"

namespace gwr::frqz
{

class Prompt : public visage::Frame
{
  public:
    Prompt();
    void clear();
    void readEntries();
    void check();
    void color();
    void mark();

    void red(visage::TextEditor *e);
    void grn(visage::TextEditor *e);
    void blk(visage::TextEditor *e);

    std::string replaceAccentedCharacters(std::string &input);

    // visage::Font font{55, resources::fonts::Lato_Regular_ttf};
    visage::Font font{55, visage::fonts::Lato_Regular_ttf};
    Label head, parse;
    visage::TextEditor form;
    std::string userForm, dbForm;
    bool isCorrect;
};

} // namespace gwr::frqz