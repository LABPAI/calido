#include "segmentationgraphicsview.hxx"

SegmentationGraphicsView::SegmentationGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    QWidget::setMouseTracking(true);

    currentZoomScale = 1.0;

    nullPoint.setX(-11999);
    nullPoint.setY(-11999);

    enableSegmentation(false);

    connect(this,SIGNAL(pointDrawn()), this, SLOT(drawLine()));

}

void SegmentationGraphicsView::addImageToScene(QPixmap img)
{
    clearScene();

    this->scene()->setSceneRect(0, 0, img.width(), img.height() );

    this->scene()->addPixmap(img);

    currentImage = img;

}


void SegmentationGraphicsView::wheelEvent(QWheelEvent *event)
{
    //Zoom speed 1.2x
    const double scaleFactor = 1.1;

    //Max zoom
    const double maxScale = 4.0;

    //Min zoom
    const double minScale = 0.5;

    //Giro pra cima
    if(event->delta() > 0)
    {
        //Se o zoom já nao está no maximo
        if( currentZoomScale * scaleFactor <= maxScale )
        {
            scale(scaleFactor,scaleFactor);

            //Multiplicar o zoom atual pelo scaleFactor
            currentZoomScale *= scaleFactor;

            //Emit current zoom string
            QString percent = QString::number(currentZoomScale * 100, 'f', 0);
            emit zoomText(QString("Zoom: %1\%").arg(percent) );
        }
    }
    //Giro pra baixo
    else
    {
        //Se é maior que o zoom minimo
        if(currentZoomScale * (1.0/scaleFactor) >= minScale)
        {
            scale(1.0/scaleFactor, 1.0/scaleFactor);

            currentZoomScale *= 1.0/scaleFactor;

            //emit current zoom String
            QString percent = QString::number(currentZoomScale * 100, 'f', 0);
            emit zoomText(QString("Zoom: %1\%").arg(percent) );
        }
    }


}

void SegmentationGraphicsView::mousePressEvent(QMouseEvent *event)
{

    //RightButton
    if( event->button() == Qt::RightButton)
    {
        if( segmentationEnabled)
            resetImage();
    }

    //LeftButton
    else if(event->button() == Qt::LeftButton)
    {
        //Se estiver ligado o modo de segmentação
        if( segmentationEnabled )
        {
            double rad = 2;

            QPointF pos = mapToScene( event->pos() );

            //Se o ponto existe na cena
            if(insideSceneSize(pos) )
            {
                //Se não há ponto no local onde foi clicado, marca o local
                QPointF p = hasPoint(pos);
                if( p == nullPoint)
                {
                    polygon << pos;
                    scene()->addRect(pos.x() - rad , pos.y() - rad, rad*2, rad*2, QPen() , QBrush( Qt::red) );
                    emit pointDrawn();
                }

                //Fecha o poligono
                else
                {

                    if(polygon.size() > 2)
                    {

                        //Desenha a linha entre ultimo e primeiro ponto
                        scene()->addLine(polygon.first().x(), polygon.first().y(), polygon.last().x(), polygon.last().y(),
                                         QPen(Qt::green) );

                        emit polygonClosed();
                        enableSegmentation();


                    }
                }
            }


        }

    }
    //Mid button
    else
    {
        resetZoom();
        QString percent = QString::number(currentZoomScale * 100, 'f', 0);
        emit zoomText(QString("Zoom: %1\%").arg(percent) );
    }



}

void SegmentationGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF p = mapToScene( event->pos());

    QString position = QString("Pos: %1, %2").arg(p.toPoint().x()).arg(p.toPoint().y());

    emit positionText(position);
}

void SegmentationGraphicsView::drawLine()
{
    if( polygon.size() >= 2)
    {
           QPointF ini = polygon[ polygon.size() - 2 ];
           QPointF end = polygon[ polygon.size() - 1 ];



           scene()->addLine(end.x(), end.y(), ini.x() , ini.y(),QPen(Qt::green));
    }
}

void SegmentationGraphicsView::resetImage()
{
    clearScene();

    scene()->setSceneRect(0, 0, currentImage.width(), currentImage.height() );

    scene()->addPixmap(currentImage);


}

void SegmentationGraphicsView::clearScene()
{
    scene()->clear();

    resetZoom();

    polygon.clear();
}

void SegmentationGraphicsView::resetZoom()
{
    double resetFactor = 1.0/currentZoomScale;

    scale(resetFactor, resetFactor);

    currentZoomScale = 1.0;
}

QPointF SegmentationGraphicsView::hasPoint(QPointF p)
{
    for(int i = 0 ; i < polygon.size() ; ++i)
    {
        //Se Coincide com o ponto no eixo x
        if(p.x() < polygon[i].x() + radius && p.x() > polygon[i].x() - radius)
        {
            //Se coincide com o ponto no eixo y
            if( p.y() < polygon[i].y() + radius  && p.y() > polygon[i].y() - radius)
            {
                return polygon[i];
            }
        }
    }
    return nullPoint;
}

bool SegmentationGraphicsView::insideSceneSize(QPointF p)
{
    if(p.x() >= 0 && p.x() < scene()->width() )
    {
        if( p.y() >= 0 && p.y() < scene()->height() )
            return true;
    }
    return false;
}


