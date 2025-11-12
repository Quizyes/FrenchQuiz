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

#include "Prompt.h"

using namespace visage::dimension;

namespace gwr::frqz
{
VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

Prompt::Prompt()
{
    setFlexLayout(true);
    layout().setFlexRows(false);
    layout().setFlexGap(2_vw);
    layout().setPaddingLeft(1_vw);

    addChild(form, true);
    addChild(head, true);
    addChild(parse, true);

    form.setFont(font.withSize(20.f));
    form.setDefaultText("...");
    form.setJustification(visage::Font::Justification::kCenter);
    form.layout().setDimensions(20_vw, 100_vh);
    form.setTextFieldEntry();
    form.onTextChange() += [&]() {
        auto str = form.text().toUtf8();
        std::set<char> set{'/', '\\', '=', '^', ',', '+', ':'};
        std::unordered_map<std::string, std::string> accs = {
            {"a\\", "à"}, {"a=", "â"}, {"a^", "â"}, {"c,", "ç"}, {"e/", "é"}, {"e\\", "è"}, {"e=", "ê"}, {"e^", "ê"},
            {"i=", "î"},  {"i^", "î"}, {"i:", "ï"}, {"i+", "ï"}, {"o=", "ô"}, {"o^", "ô"},  {"u+", "ü"}, {"u:", "ü"}};
        std::string outstr;
        char p{0}; // previous (to be modified by accent)
        for (char c : str)
        {
            if (!set.contains(c))
                outstr.append(1, c);
            else
            {
                auto s = std::string{p}.append(1, c);
                bool found = false;
                for (const auto &[key, value] : accs)
                {
                    if (s.compare(key) == 0)
                    {
                        outstr.erase(outstr.length() - 1, 1);
                        outstr.append(value);
                        found = true;
                    }
                }
                if (!found)
                {
                    outstr.append(1, c);
                }
            }
            p = c;
        }
        if (outstr.compare(str) != 0)
        {
            form.setText(outstr);
        }
    };

    head.layout().setDimensions(20_vw, 100_vh);
    parse.layout().setDimensions(55_vw, 100_vh);
    for (auto p : {&head, &parse})
    {
        p->setFont(font.withSize(25.f));
    }
}

void Prompt::clear()
{
    userForm.clear();
    form.clear();
    blk(&form);
}
void Prompt::readEntries() { userForm = form.text().toUtf8(); }
void Prompt::check()
{
    bool matches{false};
    if (strictAccentuation)
    {
        matches = (userForm.compare(dbForm) == 0);
    }
    else
    {
        matches = replaceAccentedCharacters(userForm) == replaceAccentedCharacters(dbForm);
    }
    if (matches)
        isCorrect = true;
    else
        isCorrect = false;
}
void Prompt::color()
{
    if (userForm.empty())
        return;
    if (isCorrect)
        grn(&form);
    else
        red(&form);
}
void Prompt::mark(bool strict)
{
    strictAccentuation = strict;
    readEntries();
    check();
    color();
    redraw();
}

void Prompt::red(visage::TextEditor *e)
{
    e->setBackgroundColorId(WRONG);
    e->redraw();
}
void Prompt::grn(visage::TextEditor *e)
{
    e->setBackgroundColorId(RIGHT);
    e->redraw();
}
void Prompt::blk(visage::TextEditor *e)
{
    e->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    e->redraw();
}

std::string Prompt::replaceAccentedCharacters(std::string input)
{
    Utils::replace(input, "\u00E0", "a");
    Utils::replace(input, "\u00E2", "a");
    Utils::replace(input, "\u00E7", "c");
    Utils::replace(input, "\u00E8", "e");
    Utils::replace(input, "\u00E9", "e");
    Utils::replace(input, "\u00EA", "e");
    Utils::replace(input, "\u00EE", "i");
    Utils::replace(input, "\u00EF", "i");
    Utils::replace(input, "\u00F4", "o");
    Utils::replace(input, "\u00FB", "u");
    return input;
}

} // namespace gwr::frqz