#include "segmentationwidget.hxx"

SegmentationWidget::SegmentationWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    setupScenes();

    connect(imageView,SIGNAL(positionText(QString)), this, SLOT(printCursorPosition(QString)) );

    connect(imageView, SIGNAL(zoomText(QString)), this, SLOT(printZoomScale(QString)) );

    loadImage("lesao.jpg");

    enableSegmentation(SegmentationMode::FULL);
}

void SegmentationWidget::loadImage(QString path)
{
    QPixmap img(path);

    imageView->addImageToScene(img);

}

void SegmentationWidget::enableSegmentation(SegmentationMode m)
{
    mode = m;
    imageView->enableSegmentation(true);

}

void SegmentationWidget::printCursorPosition(QString position)
{
    positionLabel->setText(position);
}

void SegmentationWidget::printZoomScale(QString zoom)
{
    zoomLabel->setText(zoom);
}

void SegmentationWidget::extractRegionOfInterest()
{
}

void SegmentationWidget::setSegmentationPolygon()
{
    segmentationPolygon = imageView->segmentationPolygon();
}

void SegmentationWidget::setupScenes()
{
    m_imageViewScene = new QGraphicsScene();
    imageView->setScene(m_imageViewScene);

    m_fullViewScene = new QGraphicsScene();
    fullSegmentationView->setScene(m_fullViewScene);

    m_leftViewScene = new QGraphicsScene(leftView);
    leftView->setScene(m_leftViewScene);

    m_rightViewScene = new QGraphicsScene( rightView);
    rightView->setScene(m_rightViewScene);

    m_registerViewScene = new QGraphicsScene( registerView);
    registerView->setScene(m_registerViewScene);

    m_errorViewScene = new QGraphicsScene( errorView );
    errorView->setScene(m_errorViewScene);

}

void SegmentationWidget::deleteScenes()
{
    delete m_imageViewScene;
    delete m_fullViewScene;
    delete m_rightViewScene;
    delete m_leftViewScene;
    delete m_registerViewScene;
    delete m_errorViewScene;
}

//Dado um ponto, verifica se está dentro do feixo convexo
bool SegmentationWidget::insideOfSegmentation(QPoint p)
{

    unsigned counter = 0;

    double xinters;

    unsigned size = segmentationPolygon.size();

    QPoint p1,p2;

    p1 = segmentationPolygon[0].toPoint();

    for( int i = 1 ; i < size ; i++)
    {
        p2 = segmentationPolygon[i % size].toPoint();
        if( p.y() > std::min(p1.y() , p2.y() ) )
        {
            if( p.y()  <= std::max( p1.y() , p2.y()))
            {
                if( p.x() <= std::max( p1.x(), p2.x() ) )
                {
                    if( p1.y() != p2.y() )
                    {
                        xinters = ( p.y() - p1.y() ) * ( p2.x() - p1.x() ) / ( p2.y() - p1.y() ) + p1.x();
                        if( p1.x() == p2.x() ||  p.x() <= xinters )
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }

    if( counter %2 == 0 ) return false;
    return true;

}



