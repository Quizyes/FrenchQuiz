#pragma once

#include <visage_ui/frame.h>
#include "Label.h"
#include <visage_file_embed/embedded_file.h>
#include "embedded/fonts.h"

namespace gwr::frqz
{

class Conjugation : public visage::Frame
{
  public:
    Conjugation();
    void draw(visage::Canvas &canvas) override;
    void clearAll();
    std::array<std::string, 6> userForms, dbForms;
    std::array<bool, 6> isCorrect{true};
    Label pn1, pn2, pn3, pn4, pn5, pn6;
    std::array<Label, 6> pns;
    visage::Frame singPns, plPns, singForms, plForms;
    visage::Frame header, body;
    visage::Font font{50, resources::fonts::Lato_Regular_ttf};
};

} // namespace gwr::frqz