#ifndef RIPES_COMPONENTGRAPHIC_H
#define RIPES_COMPONENTGRAPHIC_H

#include <QFont>
#include <QGraphicsItem>
#include <QToolButton>

#include "ripes_component.h"

namespace ripes {

class ComponentGraphic : public QGraphicsItem {
public:
    ComponentGraphic(Component* c);

    QRectF boundingRect() const override;
    /** @todo remember to implement shape()
     * We do not want our bounding rectangle to be the shape of the object, since the IO pins of an object shouldnt be
     * factored into collisions - wherease shape() should be ONLY the object
    */
    // QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget*) override;
    void setPosition(const QPointF& pos);
    void initialize();

    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private slots:
    void setExpandState(bool state);

private:
    void moveChildrenToAnchor(const QPointF& pos);
    void calculateBaseRect();
    void calculateTextPosition();

    bool m_isExpanded = false;

    QRectF m_baseRect;
    QRectF m_boundingRect;
    QRectF m_textRect;
    QFont m_font;
    QString m_displayText;

    QPointF m_textPos;
    QPointF m_expandButtonPos;

    Component* m_component;

    QToolButton* m_expandButton;
    QGraphicsProxyWidget* m_expandButtonProxy;
};
}

#endif  // RIPES_COMPONENTGRAPHIC_H