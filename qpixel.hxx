#ifndef QPIXEL_HXX
#define QPIXEL_HXX

#include <QPoint>

class QPixel : public QPoint
{
public:
    QPixel();

    void setValue( const unsigned short value);

    unsigned short value() const;


    /*Sobrecarga de operadores*/

   friend inline bool operator !=( const QPixel &p1, const QPixel &p2);

   friend inline bool operator ==( const QPixel &p1, const QPixel &p2);




private:

    unsigned short m_value; // Valor em escala de cinza (0-255)


};


/*********** Inline functions ***********/

inline bool operator !=(const QPixel &p1, const QPixel &p2)
{
    return(
           //Se satisfazer pelo menos uma das condições, os pixels são diferentes
           p1.x() != p2.x() ||
           p1.y() != p2.y() ||
           p1.value() != p2.value()
       );


}

inline bool operator ==(const QPixel &p1, const QPixel &p2)
{
    // Se todos os atributos forem iguais
    return ( p1.x() == p2.x() && p1.y() == p2.y() && p1.value() == p2.value() );
}

inline unsigned short QPixel::value() const
{
    return m_value;
}
#endif // QPIXEL_HXX
