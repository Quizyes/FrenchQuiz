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

#include "PdgmApp.h"

using namespace visage::dimension;

namespace gwr::frqz
{

VISAGE_THEME_COLOR(AppBkgd, 0xffbbbbbb);

PdgmApp::PdgmApp() : dbm(":memory:")
{
    setFlexLayout(true);
    layout().setFlexRows(true);
    addChild(header, true);
    addChild(body, true);
    header.setFlexLayout(true);
    header.layout().setDimensions(100_vw, 10_vh);
    header.layout().setFlexRows(false);
    header.layout().setFlexGap(1_vw);
    header.layout().setPadding(8_vh);

    header.addChild(lessonLabel, true);
    header.addChild(lesson, true);
    header.addChild(newBtn, true);
    header.addChild(markBtn, true);
    header.addChild(defnframe);
    defnframe.setFlexLayout(true);
    defnframe.layout().setFlexRows(true);
    defnframe.addChild(headword, true);
    defnframe.addChild(definition);
    header.addChild(cmpBtn, true);
    header.addChild(optionsBtn, false);
    header.addChild(quizUnderway, false);

    lessonLabel.layout().setDimensions(6_vw, 100_vh);
    lesson.layout().setDimensions(5_vw, 100_vh);
    newBtn.layout().setDimensions(10_vw, 100_vh);
    markBtn.layout().setDimensions(10_vw, 100_vh);
    defnframe.layout().setDimensions(19_vw, 100_vh);

    headword.layout().setDimensions(100_vw, 50_vh);
    definition.layout().setDimensions(100_vw, 50_vh);

    cmpBtn.layout().setDimensions(11_vw, 100_vh);
    optionsBtn.layout().setDimensions(11_vw, 100_vh);

    lessonLabel.setText("Part #");
    lessonLabel.setFont(font.withSize(17.f));
    lessonLabel.outline = false;
    lessonLabel.centered = false;

    lesson.setFont(font.withSize(25.f));
    lesson.onEnterKey() = [this]() {
        auto num = lesson.text().toInt();
        newQuiz(num);
    };
    lesson.setText("1");

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
        if (lesson.text().isEmpty())
            newQuiz();
        else
            newQuiz(lesson.text().toInt());
    };

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

    headword.setFont(font.withSize(25.f));
    headword.onEnterKey() = [this]() {
        auto head = headword.text().toUtf8();
        lesson.clear();
        newQuiz(head);
    };

    lesson.setFont(font.withSize(25.f));
    lesson.onEnterKey() = [this]() {
        auto num = lesson.text().toInt();
        newQuiz(num);
    };

    quizUnderway.setText("quiz underway");
    quizUnderway.layout().setDimensions(16_vw, 100_vh);
    quizUnderway.setFont(font.withSize(25.f));
    quizUnderway.outline = true;

    // ============================

    body.setFlexLayout(true);
    body.layout().setDimensions(100_vw, 90_vh);
    body.layout().setFlexRows(false);
    body.addChild(left, true);
    body.addChild(right, true);

    left.setFlexLayout(true);
    left.layout().setDimensions(49_vw, 100_vh);
    left.layout().setFlexGap(2.f);
    left.layout().setPadding(5.f);

    left.addChild(cPres, true);
    left.addChild(cImpf, true);
    left.addChild(cPs, true);
    left.addChild(cImper, true);

    cPres.setFlexLayout(true);
    cPres.layout().setDimensions(100_vw, 24_vh);
    cPres.name_ = "Present";

    cImpf.setFlexLayout(true);
    cImpf.layout().setDimensions(100_vw, 24_vh);
    cImpf.name_ = "Imperfect";

    cImper.setFlexLayout(true);
    cImper.layout().setDimensions(100_vw, 24_vh);
    cImper.name_ = "Imperative  /  Participles+";
    cImper.pn1.setText("(tu)");
    cImper.pn2.setText("(nous)");
    cImper.pn3.setText("(vous)");
    cImper.pn4.setText("pres.");
    cImper.pn5.setText("past");
    cImper.pn6.setText("aux.");

    cPs.setFlexLayout(true);
    cPs.layout().setDimensions(100_vw, 24_vh);
    cPs.name_ = "Simple Past";

    right.setFlexLayout(true);
    right.layout().setDimensions(49_vw, 100_vh);
    right.layout().setFlexGap(2.f);
    right.layout().setPadding(5.f);

    right.addChild(cFut, true);
    right.addChild(cCond, true);
    right.addChild(cSubjPres, true);
    right.addChild(cSubjImpf, true);

    cFut.setFlexLayout(true);
    cFut.layout().setDimensions(100_vw, 24_vh);
    cFut.name_ = "Future";

    cCond.setFlexLayout(true);
    cCond.layout().setDimensions(100_vw, 24_vh);
    cCond.name_ = "Conditional";

    cSubjPres.setFlexLayout(true);
    cSubjPres.layout().setDimensions(100_vw, 24_vh);
    cSubjPres.name_ = "Subjunctive Present";

    cSubjImpf.setFlexLayout(true);
    cSubjImpf.layout().setDimensions(100_vw, 24_vh);
    cSubjImpf.name_ = "Subjunctive Imperfect";

    cs = {&cPres, &cImpf, &cPs, &cImper, &cFut, &cCond, &cSubjPres, &cSubjImpf};

    optStrs[1][true] = "✅ (Simple) Past";
    optStrs[1][false] = "  (Simple) Past";
    optBools[1] = true;
    optStrs[2][true] = "✅ Future/Conditional";
    optStrs[2][false] = "  Future/Conditional";
    optBools[2] = false;
    optStrs[3][true] = "✅ Pres. Subjunctive";
    optStrs[3][false] = "  Pres. Subjunctive";
    optBools[3] = false;
    optStrs[4][true] = "✅ Impf. Subjunctive";
    optStrs[4][false] = "  Impf. Subjunctive";
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
}

void PdgmApp::draw(visage::Canvas &canvas)
{
    canvas.setColor(AppBkgd);
    canvas.fill(0, 0, width(), height());
}

void PdgmApp::newQuiz()
{
    std::string d;
    newQuiz(d);
}

void PdgmApp::newQuiz(std::string &inverb)
{
    quizUnderway.setVisible(true);

    auto st = getQuery(inverb);

    std::string verb, pres, impf, imperat, pastPart, presPart, aux, fut, cond, ps, subjPres,
        subjImpf, english;
    while (st.executeStep())
    {
        verb = st.getColumn("inf").getString();
        pres = st.getColumn("pres").getString();
        impf = st.getColumn("impf").getString();
        imperat = st.getColumn("imperat").getString();
        pastPart = st.getColumn("pastPart").getString();
        presPart = st.getColumn("presPart").getString();
        aux = st.getColumn("aux").getString();
        fut = st.getColumn("fut").getString();
        cond = st.getColumn("cond").getString();
        ps = st.getColumn("past").getString();
        subjPres = st.getColumn("subjPres").getString();
        subjImpf = st.getColumn("subjImpf").getString();
        english = st.getColumn("english").getString();
    }
    headword.setText(verb);
    definition.setText(english);

    auto presForms = splitForms(pres);
    auto impfForms = splitForms(impf);
    auto imperForms = splitForms(imperat);
    std::vector<std::string> impPartForms;
    impPartForms.push_back(imperForms[1]); // 2nd sg imperat. to first position
    impPartForms.push_back(imperForms[3]); // 1st pl imperat. to second
    impPartForms.push_back(imperForms[4]); // 2nd pl imp. to third
    impPartForms.push_back(presPart);
    impPartForms.push_back(pastPart);
    impPartForms.push_back(aux);
    auto futForms = splitForms(fut);
    auto condForms = splitForms(cond);
    auto psForms = splitForms(ps);
    auto subjPresForms = splitForms(subjPres);
    auto subjImpfForms = splitForms(subjImpf);

    for (size_t i = 0; i < 6; ++i)
    {
        for (auto c : cs)
        {
            c->es[i]->clear();
            c->es[i]->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
            c->pns[i]->setColor(0xff000000);
        }

        cPres.dbForms[i] = presForms[i];
        cImpf.dbForms[i] = impfForms[i];
        cPs.dbForms[i] = psForms[i];
        cImper.dbForms[i] = impPartForms[i];
        cFut.dbForms[i] = futForms[i];
        cCond.dbForms[i] = condForms[i];
        cSubjPres.dbForms[i] = subjPresForms[i];
        cSubjImpf.dbForms[i] = subjImpfForms[i];
    }

    userInputIsShown = true;
    quizIsMarked = false;
    cmpBtn.setActive(false);
    redraw();
}

void PdgmApp::newQuiz(int lesson)
{
    currentLesson = (lesson > 0) ? lesson : 1;
    newQuiz();
}

void PdgmApp::markQuiz()
{
    if (!userInputIsShown)
        return;

    // compare userForms with dbForms
    for (auto conj : cs)
    {
        conj->clearColors();
        conj->readContents();
        for (size_t i = 0; i < 6; ++i)
        {
            if (replaceAccents(conj->userForms[i]).compare(replaceAccents(conj->dbForms[i])) == 0)
                conj->isCorrect[i] = true;
            else
                conj->isCorrect[i] = false;
        }
        conj->color();
    }

    // color fields by correctness
    userInputIsShown = true;
    quizIsMarked = true;
    quizUnderway.setVisible(false);
    cmpBtn.setActive(true);
    redraw();
}

void PdgmApp::compare()
{
    if (!quizIsMarked)
    {
        return;
    }

    if (userInputIsShown)
    {
        for (auto conj : cs)
        {
            for (size_t i = 0; i < 6; ++i)
            {
                conj->es[i]->setText(conj->dbForms[i]);
            }
            conj->clearColors();
        }
    }
    else
    {
        for (auto conj : cs)
        {
            for (size_t i = 0; i < 6; ++i)
            {
                conj->es[i]->setText(conj->userForms[i]);
            }
            conj->color();
        }
    }
    userInputIsShown = !userInputIsShown;
    redraw();
}

SQLite::Statement PdgmApp::getQuery(std::string &inverb)
{
    if (!inverb.empty())
    {
        auto likeV = replaceUnaccented(inverb);
        auto st = dbm.getStmt("select inf from paradigms where inf like ?;");
        st.bind(1, likeV);
        std::vector<std::string> infs;
        while (st.executeStep())
        {
            infs.push_back(st.getColumn("inf").getString());
        }

        std::string finalForm;
        for (auto inf : infs)
        {
            if (replaceAccents(inf).compare(replaceAccents(inverb)) == 0)
            {
                finalForm = inf;
            }
        }
        if (!finalForm.empty())
        {
            std::cout << "form of verb: " << finalForm << std::endl;
            st = dbm.getStmt("select inf, pres, impf, presPart, pastPart, aux, "
                             "imperat, fut, cond, past, english, "
                             "subjPres, subjImpf from paradigms where inf = ?;");
            st.bind(1, finalForm);
            return st;
        }
    } // else
    auto st = dbm.getStmt("select inf, pres, impf, presPart, pastPart, "
                          "aux, imperat, fut, cond, past, english, subjPres, subjImpf "
                          "from paradigms where lesson <= ? order by random() limit 1;");
    st.bind(1, currentLesson);
    return st;
}

std::string PdgmApp::replaceAccents(std::string input)
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

std::string PdgmApp::replaceUnaccented(std::string verb)
{
    Utils::replace(verb, "a", "_");
    Utils::replace(verb, "e", "_");
    Utils::replace(verb, "i", "_");
    Utils::replace(verb, "u", "_");
    return verb;
}

std::vector<std::string> PdgmApp::splitForms(std::string &str)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    std::string delimiter{", "};
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start));
    return tokens;
}

} // namespace gwr::frqz