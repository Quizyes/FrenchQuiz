#include "RcgnApp.h"

int main()
{
    gwr::frqz::RcgnApp app;

    app.show(1200, 900); // Opens as 800 x 600 pixel window
    app.runEventLoop();  // Runs window events. Returns when window is closed.
    return 0;
}