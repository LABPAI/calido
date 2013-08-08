#ifndef SEGMENTATIONWIDGET_HXX
#define SEGMENTATIONWIDGET_HXX

#include "ui_segmentationwidget.h"

/* C++11 FEATURE */
enum class SegmentationMode { FULL, RIGHT, LEFT, NONE };

class SegmentationWidget : public QWidget, private Ui::SegmentationWidget
{
    Q_OBJECT
    
public:
    explicit SegmentationWidget(QWidget *parent = 0);

    void loadImage(QString path);

    void enableSegmentation(SegmentationMode m);



public slots:

    //Printa a posição do cursor no imageView
    void printCursorPosition(QString position);

    //Printa o zoom do imageView
    void printZoomScale(QString zoom);

    //Extrai a regiao segmentada
    void extractRegionOfInterest();

    void setSegmentationPolygon();


private:
    //As cenas
    QGraphicsScene *m_imageViewScene,
                   *m_fullViewScene,
                   *m_leftViewScene,
                   *m_rightViewScene,
                   *m_registerViewScene,
                   *m_errorViewScene;

    void setupScenes();

    void deleteScenes();

    SegmentationMode mode;

    bool insideOfSegmentation(QPoint p);

    QPolygonF segmentationPolygon;


};

#endif // SEGMENTATIONWIDGET_HXX
