#include <visage_app/application_window.h>

int main()
{
    visage::ApplicationWindow app;

    app.onDraw() = [&app](visage::Canvas &canvas) {
        canvas.setColor(0xffff00ff);
        canvas.fill(0, 0, app.width(), app.height());
    };

    app.show(1200, 900);
    app.runEventLoop();
    return 0;
}