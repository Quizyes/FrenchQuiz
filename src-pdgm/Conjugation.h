#pragma once

#include <visage_ui/frame.h>
#include <visage_widgets/text_editor.h>
#include <visage_file_embed/embedded_file.h>
#include <embedded/fonts.h>
#include "Label.h"

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