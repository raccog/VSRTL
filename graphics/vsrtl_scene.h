#ifndef VSRTL_SCENE_H
#define VSRTL_SCENE_H

#include <QGraphicsScene>
#include <QPainter>
#include "vsrtl_graphics_defines.h"

#include "vsrtl_wiregraphic.h"

#include <set>

namespace vsrtl {

class VSRTLScene : public QGraphicsScene {
public:
    VSRTLScene(QObject* parent = nullptr);

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    void handleSelectionChanged();
    void handleWirePointMove(QGraphicsSceneMouseEvent* event);

    std::set<WirePoint*> m_currentDropTargets;
    WirePoint* m_selectedPoint = nullptr;


    /* Applies T::F to all items in the scene of type F, using the supplied arguments */
    template <typename T, typename F, typename... Args>
    void execOnItems(F f, Args... args) {
        for (auto* c : items()) {
            if (auto* t_c = dynamic_cast<T*>(c)) {
                (t_c->*f)(args...);
            }
        }
    }

    /* Applies T::F to all items in the scene of type F, using the supplied arguments, if predicate returns
     * true */
    template <typename T, typename F, typename... Args>
    void predicatedExecOnItems(std::function<bool(const T*)> pred, F f, Args... args) {
        for (auto* c : items()) {
            if (auto* t_c = dynamic_cast<T*>(c)) {
                if (pred(t_c)) {
                    (t_c->*f)(args...);
                }
            }
        }
    }protected:
#ifdef VSRTL_DEBUG_DRAW
    void drawBackground(QPainter* painter, const QRectF& rect) override {
        qreal left = int(rect.left()) - (int(rect.left()) % GRID_SIZE);
        qreal top = int(rect.top()) - (int(rect.top()) % GRID_SIZE);

        QVarLengthArray<QLineF, 100> lines;

        for (qreal x = left; x < rect.right(); x += GRID_SIZE)
            lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        for (qreal y = top; y < rect.bottom(); y += GRID_SIZE)
            lines.append(QLineF(rect.left(), y, rect.right(), y));

        painter->drawLines(lines.data(), lines.size());
    }
#endif
};

}  // namespace vsrtl

#endif  // VSRTL_SCENE_H
