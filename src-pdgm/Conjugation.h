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

#include <visage_ui/frame.h>
#include <visage_widgets/text_editor.h>
#include <visage_file_embed/embedded_file.h>
#include <embedded/fonts.h>
#include "Label.h"
#include "Utils.h"

namespace gwr::frqz
{

class Conjugation : public visage::Frame
{
  public:
    Conjugation();
    void draw(visage::Canvas &canvas) override;
    void clearAll();
    void readContents();
    void color();
    void clearColors();
    void clearPronouns();
    void red(Label *l);
    void red(visage::TextEditor *e);
    void grn(Label *l);
    void grn(visage::TextEditor *e);
    void blk(Label *l);
    void blk(visage::TextEditor *e);
    std::string replaceAccents(std::string &verb);
    std::string name_;
    std::array<std::string, 6> userForms, dbForms;
    std::array<bool, 6> isCorrect{true};
    visage::TextEditor e1, e2, e3, e4, e5, e6;
    std::array<visage::TextEditor *, 6> es;
    Label pn1, pn2, pn3, pn4, pn5, pn6;
    std::array<Label *, 6> pns;
    visage::Frame singPns, plPns, singForms, plForms;
    visage::Frame header, body;
    visage::Font font{50, visage::fonts::Lato_Regular_ttf};
};

} // namespace gwr::frqz