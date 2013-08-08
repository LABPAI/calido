#include "qpixel.hxx"

QPixel::QPixel() : QPoint()
{
    m_value = 0;
}

void QPixel::setValue(const unsigned short value)
{
    if( value >= 0 && value < 256 )// Intervalo válido
        m_value = value;
    else // se não estiver dentro do intervalo, configura como 0
        m_value = 0;
}





