#include "QuizItem.h"

namespace gwr::frqz
{
QuizItem::QuizItem() {}

void QuizItem::clearColors() {}

void QuizItem::clearData() {}

void QuizItem::readEntries() {}

void QuizItem::check() {}

void QuizItem::color() {}

void QuizItem::show() {}

void QuizItem::mark() {}

void QuizItem::red(Label *l) {}

void QuizItem::red(visage::TextEditor *e) {}

void QuizItem::grn(Label *l) {}

void QuizItem::grn(visage::TextEditor *e) {}

void QuizItem::blk(Label *l) {}

void QuizItem::blk(visage::TextEditor *e) {}

bool QuizItem::compareParses(std::string &user, std::string &db)
{
    auto userParts = split(userParse);
    auto dbParts = split(dbParse);
    size_t matches{0};
    for (auto &part : dbParts)
    {
        if (userParts.contains(part))
            ++matches;
    }
    if (matches == dbParts.size())
        return true;
    return false;
}

std::string QuizItem::replaceAccentedCharacters(std::string &input) { return std::string(); }

} // namespace gwr::frqz