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

    head.layout().setDimensions(20_vw, 100_vh);
    parse.layout().setDimensions(55_vw, 100_vh);
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
    if (replaceAccentedCharacters(userForm).compare(replaceAccentedCharacters(dbForm)) == 0)
    {
        isCorrect = true;
    }
    else
        isCorrect = false;
}
void Prompt::color()
{
    if (userForm.empty())
        return;
    if (isCorrect)
    {
        grn(&form);
    }
    else
        red(&form);
}
void Prompt::mark()
{
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

std::string Prompt::replaceAccentedCharacters(std::string &input)
{
    std::string result;
    for (size_t i = 0; i < input.size(); ++i)
    {
        if ((int)input[i] >= 0)
        {
            result.append(1, input[i]);
        }
        else
        {
            if ((int)input[i] == -61)
            {
                if (((int)input[i + 1] >= -96) && ((int)input[i + 1] <= -90))
                {
                    result.append("a");
                }
                if (((int)input[i + 1] == -89))
                {
                    result.append("c");
                }
                if (((int)input[i + 1] >= -88) && ((int)input[i + 1] <= -85))
                {
                    result.append("e");
                }
                if (((int)input[i + 1] >= -84) && ((int)input[i + 1] <= -81))
                {
                    result.append("i");
                }
                if (((int)input[i + 1] >= -78) && ((int)input[i + 1] <= -72))
                {
                    result.append("o");
                }
                if (((int)input[i + 1] >= -71) && ((int)input[i + 1] <= -68))
                {
                    result.append("u");
                }
            }
        }
    }
    return result;
}

} // namespace gwr::frqz