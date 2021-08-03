#ifndef CUSTOMHEADERVIEW_HPP
#define CUSTOMHEADERVIEW_HPP

#include <QHeaderView>


class CustomHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    CustomHeaderView(Qt::Orientation orientation, QWidget * parent = nullptr);
    ~CustomHeaderView() { }

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

    QRect sectionRect(int logicalIndex) const;
    QRect buttonMenuRect(int logicalIndex) const;

    void drawMenuButton(QPainter *painter, int logicalIndex, bool enabled) const;
private:

};


#endif // CUSTOMHEADERVIEW_HPP
