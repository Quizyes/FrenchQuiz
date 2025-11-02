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
#include "Label.h"

namespace gwr::frqz
{

typedef struct dbEntry
{
    std::string form, head, parse;
} dbEntry;

class QuizItem : public visage::Frame
{
  public:
    QuizItem();
    void clearColors();
    void clearData();
    void readEntries();
    void check();
    void color();
    void show();
    void mark();

    void red(Label *l);
    void red(visage::TextEditor *e);
    void grn(Label *l);
    void grn(visage::TextEditor *e);
    void blk(Label *l);
    void blk(visage::TextEditor *e);

    std::set<std::string> split(std::string &str, char delimiter = ' ');
    bool compareParses(std::string &user, std::string &db);
    std::string replaceAccentedCharacters(std::string &input);

    Label form;
    visage::TextEditor head, parse;
    std::string userHead, userParse, dbHead, dbParse;
    bool headIsCorrect{false}, parseIsCorrect{false};
    std::vector<dbEntry> dbEntries; // fill with alts from RcgnApp on newQuiz()
};

} // namespace gwr::frqz