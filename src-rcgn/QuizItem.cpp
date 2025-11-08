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

#include "QuizItem.h"

using namespace visage::dimension;

namespace gwr::frqz
{
VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

QuizItem::QuizItem()
{
    setFlexLayout(true);
    layout().setFlexRows(false);
    layout().setFlexGap(2_vw);
    layout().setPaddingLeft(1_vw);

    addChild(form, true);
    addChild(head, true);
    addChild(parse, true);

    form.layout().setDimensions(20_vw, 100_vh);

    head.setFont(font.withSize(20.f));
    head.setDefaultText("...");
    head.setJustification(visage::Font::Justification::kCenter);
    head.layout().setDimensions(20_vw, 100_vh);
    head.setTextFieldEntry();

    parse.setFont(font.withSize(20.f));
    parse.setDefaultText("...");
    parse.setJustification(visage::Font::Justification::kCenter);
    parse.layout().setDimensions(55_vw, 100_vh);
    parse.setTextFieldEntry();
}

void QuizItem::clearUi()
{
    blk(&head);
    blk(&parse);
    blk(&form);
    parse.clear();
    head.clear();
}

void QuizItem::clearData()
{
    for (auto &p : {&userHead, &userParse, &dbHead, &dbParse})
    {
        p->clear();
    }
    dbEntries.clear();
}

void QuizItem::clearColors()
{
    blk(&head);
    blk(&form);
    blk(&parse);
}

void QuizItem::readEntries()
{
    userHead = head.text().toUtf8();
    userParse = parse.text().toUtf8();
}

void QuizItem::check()
{
    int idx{0};
    headIsCorrect = checkHead();
    parseIsCorrect = checkParse();
    for (auto &dbEntry : dbEntries)
    {
        bool headC{false}, parseC{false};
        if (replaceAccentedCharacters(userHead) == replaceAccentedCharacters(dbEntry.head))
            headC = true;
        if (compareParses(userParse, dbEntry.parse))
        {
            parseC = true;
            dbParse = dbEntry.parse;
            idxOfCorrectParse = idx;
        }
        if (parseC && headC)
        {
            idxOfCorrectParse = idx;
            dbHead = dbEntry.head;
            dbParse = dbEntry.parse;
            parseIsCorrect = true;
            headIsCorrect = true;
            return;
        }
        ++idx;
    }
}

bool QuizItem::checkHead()
{
    for (auto &entry : dbEntries)
    {
        if (replaceAccentedCharacters(userHead) == replaceAccentedCharacters(entry.head))
        {
            return true;
        }
    }
    return false;
}

bool QuizItem::checkParse()
{
    size_t idx{0};
    if (parse.text().isEmpty())
        return false;
    for (auto entry : dbEntries)
    {
        if (compareParses(userParse, entry.parse))
        {
            idxOfCorrectParse = idx;
            return true;
        }
        ++idx;
    }
    return false;
}

void QuizItem::color()
{
    if (!userHead.empty())
    {
        if (headIsCorrect)
        {
            grn(&head);
            grn(&form);
        }
        else
        {
            red(&head);
            red(&form);
        }
    }
    else
    {
        blk(&head);
        blk(&form);
    }
    if (!userParse.empty())
    {
        if (parseIsCorrect)
        {
            grn(&parse);
            grn(&form);
        }
        else
        {
            red(&parse);
            red(&form);
        }
    }
    else
    {
        blk(&parse);
        blk(&form);
    }
}

void QuizItem::show()
{
    size_t idx{0};
    if (parseIsCorrect)
        idx = idxOfCorrectParse;
    dbHead = dbEntries[idx].head;
    dbParse = dbEntries[idx].parse;
    redraw();
}

void QuizItem::mark()
{
    readEntries();
    check();
    color();
    show();
    redraw();
}

void QuizItem::red(Label *l)
{
    l->setColor(visage::Color(0xffbb3232));
    l->redraw();
}
void QuizItem::red(visage::TextEditor *e)
{
    e->setBackgroundColorId(WRONG);
    e->redraw();
}

void QuizItem::grn(Label *l)
{
    l->setColor(visage::Color(0xff32bb32));
    l->redraw();
}
void QuizItem::grn(visage::TextEditor *e)
{
    e->setBackgroundColorId(RIGHT);
    e->redraw();
}

void QuizItem::blk(Label *l)
{
    l->setColor(visage::Color(0xff000000));
    l->redraw();
}
void QuizItem::blk(visage::TextEditor *e)
{
    e->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    e->redraw();
}

std::set<std::string> QuizItem::split(std::string &str, char delimiter)
{
    std::set<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        tokens.insert(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    tokens.insert(str.substr(start));
    return tokens;
}

bool QuizItem::compareParses(std::string &user, std::string &db)
{
    if (user.empty())
        return false;
    auto userParts = split(user);
    auto dbParts = split(db);
    size_t matches{0};
    for (auto &part : dbParts)
    {
        if (userParts.contains(part))
            ++matches;
    }
    if (matches == dbParts.size())
    {
        return true;
    }
    return false;
}

std::string QuizItem::replaceAccentedCharacters(std::string input)
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