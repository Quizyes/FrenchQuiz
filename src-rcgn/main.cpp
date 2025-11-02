#include <visage_app/application_window.h>

int main()
{
    visage::ApplicationWindow app;

    app.onDraw() = [&app](visage::Canvas &canvas) {
        canvas.setColor(0xff00ffff);
        canvas.fill(0, 0, app.width(), app.height());
    };

    app.show(800, 600); // Opens as 800 x 600 pixel window
    app.runEventLoop(); // Runs window events. Returns when window is closed.
    return 0;
}