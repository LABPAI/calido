#include <iostream>
#include <QApplication>
#include "segmentationwidget.hxx"
#include "qpixel.hxx"


using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QPixel p1,p2;
    p2.setValue(243);
    if( p1 == p2) std::cout << "Iguais";

    SegmentationWidget v;

    v.show();

    return app.exec();
}

