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

#include "RcgnApp.h"
#include <emscripten.h>

using namespace visage::dimension;

namespace gwr::frqz
{
VISAGE_THEME_COLOR(AppBkgd, 0xffbbbbbb);
VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

RcgnApp::RcgnApp() : dbm(":memory:")
{
    setFlexLayout(true);
    layout().setFlexRows(true);
    addChild(header, true);
    addChild(colHead, true);
    addChild(body, true);
    header.setFlexLayout(true);
    header.layout().setDimensions(100_vw, 10_vh);
    header.layout().setFlexSelfAlignment(visage::Layout::ItemAlignment::Center);
    header.layout().setFlexRows(false);
    header.layout().setFlexGap(1_vw);
    header.layout().setPadding(8_vh);
    // header.outline = false;

    header.addChild(helpBtn, true);
    header.addChild(newBtn, true);
    header.addChild(markBtn, true);
    header.addChild(cmpBtn, true);
    header.addChild(optionsBtn, true);

    newBtn.layout().setDimensions(15_vw, 100_vh);
    markBtn.layout().setDimensions(15_vw, 100_vh);
    cmpBtn.layout().setDimensions(15_vw, 100_vh);
    helpBtn.layout().setDimensions(5_vw, 100_vh);
    optionsBtn.layout().setDimensions(15_vw, 100_vh);

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

    markBtn.setFont(font.withSize(25.f));
    markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { markQuiz(); };

    cmpBtn.setFont(font.withSize(25.f));
    cmpBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
        if (cmpBtn.isActive())
        {
            compare();
        }
    };
    cmpBtn.setActive(false);

    helpBtn.setFont(font.withSize(25.f));
    helpBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
        // clang-format off
        EM_ASM(window.open("help.html", "myPopup", "width=900,height=600,resizable=yes,scrollbars=yes,location=no,menubar=no,toolbar=no,status=no"));
        // clang-format on
    };

    optStrs[1][true] = "(Simple) Past        ✅";
    optStrs[1][false] = "(Simple) Past         ";
    optBools[1] = true;
    optStrs[2][true] = "Future/Conditional        ✅";
    optStrs[2][false] = "Future/Conditional         ";
    optBools[2] = false;
    optStrs[3][true] = "Pres. Subjunctive        ✅";
    optStrs[3][false] = "Pres. Subjunctive         ";
    optBools[3] = false;
    optStrs[4][true] = "Impf. Subjunctive        ✅";
    optStrs[4][false] = "Impf. Subjunctive         ";
    optBools[4] = false;
    optionsBtn.setFont(font.withSize(25.f));
    optionsBtn.setActionButton();
    optionsBtn.onToggle() = [this](visage::Button *button, bool checked) {
        visage::PopupMenu pp;
        for (int i = 1; i < 5; ++i)
        {
            pp.addOption(i, optStrs[i][optBools[i]]);
        }
        pp.onSelection() = [&](int id) {
            switch (id)
            {
            case 1:
                optBools[1] = !optBools[1];
                break;
            case 2:
                optBools[2] = !optBools[2];
                break;
            case 3:
                optBools[3] = !optBools[3];
                break;
            case 4:
                optBools[4] = !optBools[4];
                break;
            default:
                break;
            }
        };
        pp.show(&optionsBtn);
    };
    optionsBtn.setToggleOnMouseDown(true);

    // ============================

    colHead.setFlexLayout(true);
    colHead.layout().setFlexRows(false);
    colHead.layout().setFlexGap(2_vw);
    colHead.layout().setPaddingLeft(1_vw);
    colHead.layout().setDimensions(100_vw, 10_vh);
    colHead.addChild(formCol, true);
    colHead.addChild(headCol, true);
    colHead.addChild(parseCol, true);
    formCol.layout().setDimensions(20_vw, 100_vh);
    headCol.layout().setDimensions(20_vw, 100_vh);
    parseCol.layout().setDimensions(55_vw, 100_vh);
    formCol.setFont(font.withSize(25.f));
    headCol.setFont(font.withSize(25.f));
    parseCol.setFont(font.withSize(25.f));
    formCol.setText("Inflected");
    headCol.setText("Headword");
    parseCol.setText("Parse");
    formCol.outline = false;
    headCol.outline = false;
    parseCol.outline = false;

    // ============================

    body.setFlexLayout(true);
    body.layout().setDimensions(100_vw, 90_vh);
    body.layout().setFlexRows(true);
    body.layout().setFlexGap(4_vh);

    items[0] = &q1;
    items[1] = &q2;
    items[2] = &q3;
    items[3] = &q4;
    items[4] = &q5;
    items[5] = &q6;
    items[6] = &q7;
    items[7] = &q8;
    // body.outline = false;
    for (size_t i = 0; i < 8; ++i)
    {
        body.addChild(items[i], true);
        items[i]->layout().setDimensions(100_vw, 6_vh);
    }
}

void RcgnApp::newQuiz()
{
    auto st = dbm.getStmt("select head, form, parse from recogs where (parse not like ?) and "
                          "(parse not like ? and parse not like ?) and (parse not like ?) and "
                          "(parse not like ?) order "
                          "by random() limit 8;");
    if (!optBools[1])
        st.bind(1, "%past%");
    else
        st.bind(1, "zz");
    if (!optBools[2])
    {
        st.bind(2, "%cond%");
        st.bind(3, "%fut%");
    }
    else
    {
        st.bind(2, "zz");
        st.bind(3, "zz");
    }
    if (!optBools[3])
        st.bind(4, "%subj pres%");
    else
        st.bind(4, "zz");
    if (!optBools[4])
        st.bind(5, "%subj impf%");
    else
        st.bind(5, "zz");

    std::array<std::string, 8> heads, forms, parses;
    size_t idx{0};
    while (st.executeStep())
    {
        items[idx]->clearData();
        items[idx]->clearUi();
        heads[idx] = st.getColumn("head").getString();
        forms[idx] = st.getColumn("form").getString();
        parses[idx] = st.getColumn("parse").getString();
        items[idx]->form.setText(forms[idx]);
        items[idx]->dbHead = heads[idx];
        items[idx]->dbParse = parses[idx];
        items[idx]->dbEntries.push_back({forms[idx], heads[idx], parses[idx]});
        ++idx;
    }

    userInputIsShown = true;
    quizIsMarked = false;
    cmpBtn.setActive(false);
    redraw();
}

void RcgnApp::loadAlts()
{
    size_t idx{0};
    for (auto &r : items)
    {
        auto st = dbm.getStmt(
            "select form, head, parse from recogs where form = ? and (parse != ? or head != ?)");
        st.bind(1, r->form.text_.toUtf8());
        st.bind(2, r->dbParse);
        st.bind(3, r->dbHead);
        while (st.executeStep())
        {
            auto f = st.getColumn("form").getString();
            auto h = st.getColumn("head").getString();
            auto p = st.getColumn("parse").getString();
            r->dbEntries.push_back({f, h, p});
        }
    }
}

void RcgnApp::markQuiz()
{
    if (!userInputIsShown)
        return;
    for (auto &item : items)
    {
        item->mark();
        item->redraw();
    }
    userInputIsShown = true;
    quizIsMarked = true;
    cmpBtn.setActive(true);
    redraw();
}

void RcgnApp::compare()
{
    if (!quizIsMarked)
    {
        return;
    }

    if (userInputIsShown)
    {
        for (auto &item : items)
        {
            item->head.setText(item->dbHead);
            item->parse.setText(item->dbParse);
            item->clearColors();
        }
    }
    else
    {
        for (auto &item : items)
        {
            item->head.setText(item->userHead);
            item->parse.setText(item->userParse);
            item->color();
        }
    }
    userInputIsShown = !userInputIsShown;
    redraw();
}

void RcgnApp::draw(visage::Canvas &canvas)
{
    canvas.setColor(AppBkgd);
    canvas.fill(0, 0, width(), height());
}

} // namespace gwr::frqz
