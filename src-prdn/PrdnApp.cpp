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
#include "PrdnApp.h"

namespace gwr::frqz
{

PrdnApp::PrdnApp() : dbm(":memory:")
{
    onDraw() = [&](visage::Canvas &canvas) {
        canvas.setColor(0xff00ffff);
        canvas.fill(0, 0, width(), height());
    };
}

} // namespace gwr::frqz