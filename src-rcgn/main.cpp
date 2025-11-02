#include "RcgnApp.h"

int main()
{
    gwr::frqz::RcgnApp app;

    app.onDraw() = [&app](visage::Canvas &canvas) {
        canvas.setColor(0xffffffff);
        canvas.fill(0, 0, app.width(), app.height());
    };

    app.show(1200, 900); // Opens as 800 x 600 pixel window
    app.runEventLoop();  // Runs window events. Returns when window is closed.
    return 0;
}