#include "main.h"
int main(int argc, char* argv[])
{
    QApplication App(argc, argv);
    MyWindow window;
    window.setWindowTitle("Calculator");
    window.resize(800, 300);
    window.show();
    return App.exec();
}