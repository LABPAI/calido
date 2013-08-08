#ifndef SEGMENTATIONGRAPHICSVIEW_HXX
#define SEGMENTATIONGRAPHICSVIEW_HXX

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>


class SegmentationGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SegmentationGraphicsView(QWidget *parent = 0);

    //Coloca a imagem na cena do view
    void addImageToScene(QPixmap img);

    void enableSegmentation(bool flag = false)
    {
        segmentationEnabled = flag;
    }

    QPolygonF segmentationPolygon() const
    {
        return polygon;
    }

    
signals:
    void pointDrawn();

    void polygonClosed();

    void positionText(QString position);

    void zoomText(QString zoom);

public slots:

    // Zoom ao rolar a mouse wheel
    void wheelEvent(QWheelEvent *event);

    //Se a segmentação estiver acionada, segmenta a imagem manualmente ao clicar na scene
    void mousePressEvent(QMouseEvent *event);

    //Desenha uma circunferencia quando passar por um ponto que já foi alocado
    void mouseMoveEvent(QMouseEvent *event);

    //Desenha as linhas
    void drawLine();

private:
    double currentZoomScale;

    QPixmap currentImage;

    QPolygonF polygon;

    const unsigned radius = 3;

    QPointF nullPoint;






    void resetImage();

    void clearScene();

    void resetZoom();

    QPointF hasPoint(QPointF p);

    bool insideSceneSize(QPointF p);

    bool segmentationEnabled;

};


#endif // SEGMENTATIONGRAPHICSVIEW_HXX
