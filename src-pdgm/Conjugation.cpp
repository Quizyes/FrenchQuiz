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

#include "Conjugation.h"

using namespace visage::dimension;

namespace gwr::frqz
{
VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

Conjugation::Conjugation()
{
    setFlexLayout(true);
    layout().setFlexRows(true);
    addChild(header, true);
    addChild(body, true);
    header.setFlexLayout(true);
    header.layout().setDimensions(100_vw, 18_vh);
    body.setFlexLayout(true);
    body.layout().setFlexRows(false);
    body.layout().setDimensions(100_vw, 75_vh);
    body.addChild(singPns, true);
    body.addChild(singForms, true);
    body.addChild(plPns, true);
    body.addChild(plForms, true);
    singPns.setFlexLayout(true);
    singPns.layout().setFlexGap(5.f);
    singPns.layout().setFlexRows(true);
    singPns.layout().setDimensions(10_vw, 100_vh);
    plPns.setFlexLayout(true);
    plPns.layout().setFlexRows(true);
    plPns.layout().setFlexGap(5.f);
    plPns.layout().setDimensions(10_vw, 100_vh);
    pn1.setText("je/j'");
    pn2.setText("tu");
    pn3.setText("elle");
    for (auto &pn : {&pn1, &pn2, &pn3})
    {
        singPns.addChild(pn, true);
        pn->layout().setDimensions(100_vw, 28_vh);
        pn->outline = false;
    }
    pn4.setText("nous");
    pn5.setText("vous");
    pn6.setText("ils");
    for (auto &pn : {&pn4, &pn5, &pn6})
    {
        plPns.addChild(pn, true);
        pn->layout().setDimensions(100_vw, 28_vh);
        pn->outline = false;
    }
    singForms.setFlexLayout(true);
    singForms.layout().setDimensions(40_vw, 100_vh);
    singForms.layout().setFlexRows(true);
    singForms.layout().setFlexGap(5.f);
    singForms.layout().setFlexItemAlignment(visage::Layout::ItemAlignment::Center);
    plForms.setFlexLayout(true);
    plForms.layout().setDimensions(40_vw, 100_vh);
    plForms.layout().setFlexRows(true);
    plForms.layout().setFlexGap(5.f);
    plForms.layout().setFlexItemAlignment(visage::Layout::ItemAlignment::Center);
    singForms.addChild(e1, true);
    singForms.addChild(e2, true);
    singForms.addChild(e3, true);
    plForms.addChild(e4, true);
    plForms.addChild(e5, true);
    plForms.addChild(e6, true);

    for (auto &fr : {&pn1, &pn2, &pn3, &pn4, &pn5, &pn6})
    {
        fr->setFont(font.withSize(20.f));
    }

    for (auto &fr : {&e1, &e2, &e3, &e4, &e5, &e6})
    {
        fr->setFlexLayout(true);
        fr->setFont(font.withSize(20.f));
        fr->setDefaultText("...");
        fr->setJustification(visage::Font::Justification::kCenter);
        fr->layout().setDimensions(95_vw, 28_vh);
        fr->setTextFieldEntry();
    }

    es[0] = &e1;
    es[1] = &e2;
    es[2] = &e3;
    es[3] = &e4;
    es[4] = &e5;
    es[5] = &e6;
    pns[0] = &pn1;
    pns[1] = &pn2;
    pns[2] = &pn3;
    pns[3] = &pn4;
    pns[4] = &pn5;
    pns[5] = &pn6;
}

void Conjugation::draw(visage::Canvas &canvas)
{
    if (name_.empty())
        return;
    else
        canvas.text(name_, font, visage::Font::Justification::kCenter, 0, 0, 100_vw, 15_vh);
}

void Conjugation::clearAll()
{
    for (size_t i = 0; i < 6; ++i)
    {
        es[i]->clear();
        dbForms[i].clear();
    }
}

void Conjugation::readContents()
{
    for (size_t i = 0; i < 6; ++i)
    {
        userForms[i] = es[i]->text().toUtf8();
    }
}

void Conjugation::color()
{
    for (size_t i = 0; i < 6; ++i)
    {
        if (userForms[i].empty())
            continue;
        if (isCorrect[i])
        {
            grn(es[i]);
            grn(pns[i]);
        }
        else
        {
            red(es[i]);
            red(pns[i]);
        }
    }
}

void Conjugation::clearColors()
{
    for (size_t i = 0; i < 6; ++i)
    {
        blk(es[i]);
        blk(pns[i]);
    }
}

void Conjugation::clearPronouns()
{
    for (size_t i = 0; i < 6; ++i)
    {
        blk(pns[i]);
    }
}
void Conjugation::red(Label *l)
{
    l->setColor(visage::theme::ColorId::defaultColor(WRONG));
    l->redraw();
}
void Conjugation::red(visage::TextEditor *e)
{
    e->setBackgroundColorId(WRONG);
    e->redraw();
}
void Conjugation::grn(Label *l)
{
    l->setColor(visage::theme::ColorId::defaultColor(RIGHT));
    l->redraw();
}
void Conjugation::grn(visage::TextEditor *e)
{
    e->setBackgroundColorId(RIGHT);
    e->redraw();
}
void Conjugation::blk(Label *l)
{
    l->setColor(0xff000000);
    l->redraw();
}
void Conjugation::blk(visage::TextEditor *e)
{
    e->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    e->redraw();
}

} // namespace gwr::frqz