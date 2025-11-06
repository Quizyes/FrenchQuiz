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

#include <visage/app.h>
#include "embedded/fonts.h"

class Label : public visage::Frame
{
  public:
    Label() = default;
    visage::String text_;
    bool outline{true};
    std::vector<visage::String> tokens_;
    visage::Font fontEn{55, visage::fonts::Lato_Regular_ttf};
    visage::Color color_{visage::Color(0xff000000)};
    bool centered{true};
    void setColor(const visage::Color &color)
    {
        color_ = color;
        redraw();
    }
    void setText(const visage::String &text)
    {
        text_ = text;
        redraw();
    }
    void setText2(const char text[])
    {
        text_ = visage::String(text);
        redraw();
    }
    void setFont(const visage::Font &font)
    {
        fontEn = font.withDpiScale(dpiScale());
        redraw();
    }
    visage::Point indexToPosition(int index) const
    {
        if (index < 0 || index >= text_.length())
            return {0.0f, 0.0f};

        float x = fontEn.stringWidth(text_.c_str(), index);
        float y = fontEn.lineHeight();
        return {x, y};
    }

    void draw(visage::Canvas &canvas) override
    {
        canvas.setColor(0xff000000);
        if (outline)
        {
            canvas.roundedRectangleBorder(0, 0, width(), height(), 5.f, 1.f);
        }
        if (text_.isEmpty())
        {
            return;
        }
        canvas.setColor(color_);
        if (centered)
            canvas.text(text_, fontEn.withSize(25.f), visage::Font::Justification::kCenter, 0, 0,
                        width(), height());
        else
            canvas.text(text_, fontEn.withSize(25.f), visage::Font::Justification::kTop, 0, 0,
                        width(), height());
    }
};