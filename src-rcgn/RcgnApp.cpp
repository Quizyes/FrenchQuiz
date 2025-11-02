#include "RcgnApp.h"

namespace gwr::frqz
{

RcgnApp::RcgnApp() : dbm(":memory:")
{
    auto st = dbm.getStmt("select * from recogs order by random() limit 1;");
    st.executeStep();
    testOut = st.getColumn("parse").getString();
}

void RcgnApp::newQuiz() {}

void RcgnApp::loadAlts() {}

void RcgnApp::markQuiz() {}

void RcgnApp::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xff2299bb);
    canvas.fill(0, 0, width(), height());
    canvas.setColor(0xff000000);
    canvas.text(visage::String{testOut}, font, visage::Font::Justification::kCenter, 300, 400, 300,
                100);
}

} // namespace gwr::frqz
