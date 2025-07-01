#include "quadtree.hpp"

AABB::AABB(Vec2 centre, int halfSize) {
    this->centre = centre;
    this->halfSize = halfSize;
}

bool AABB::containsPoint(Vec2 point) {
    return point.x >= (centre.x - halfSize) &&
           point.x <= (centre.x + halfSize) &&
           point.y >= (centre.y - halfSize) &&
           point.y <= (centre.y + halfSize);
}

bool AABB::intersectsAABB(AABB other) {
    return !(other.centre.x - other.halfSize > centre.x + halfSize ||
             other.centre.x + other.halfSize < centre.x - halfSize ||
             other.centre.y - other.halfSize > centre.y + halfSize ||
             other.centre.y + other.halfSize < centre.y - halfSize);
}



// -- QuadTree --
QuadTree::QuadTree(AABB boundry) : boundry(boundry) {}

bool QuadTree::insert(Vec2 p, void* data) {
    if (!boundry.containsPoint(p)) {
        return false;
    }

    if (pointCount < CAPACITY && nw == NULL) {
        points[pointCount] = p;
        userData[pointCount++] = data;

        return true;
    }

    if (nw == NULL) {
        if (!subdivide()) {
            return false;
        }
    }

    if (nw->insert(p, data) ||
        ne->insert(p, data) ||
        sw->insert(p, data) ||
        se->insert(p, data)
    ) {
        return true;
    }

    return false;
}

bool QuadTree::subdivide() {
    nw = (QuadTree*) malloc(sizeof(QuadTree));
    ne = (QuadTree*) malloc(sizeof(QuadTree));
    sw = (QuadTree*) malloc(sizeof(QuadTree));
    se = (QuadTree*) malloc(sizeof(QuadTree));

    if (!nw || !ne || !sw || !se) {
        if (nw) free(nw);
        if (ne) free(ne);
        if (sw) free(sw);
        return false;
    }

    int subdividedSize = boundry.halfSize / 2;

    nw->boundry = AABB(
            Vec2(
                boundry.centre.x - subdividedSize,
                boundry.centre.y - subdividedSize
            ),
            subdividedSize
    );
    ne->boundry = AABB(
            Vec2(
                boundry.centre.x + subdividedSize,
                boundry.centre.y - subdividedSize
            ),
            subdividedSize
    );
    sw->boundry = AABB(
            Vec2(
                boundry.centre.x - subdividedSize,
                boundry.centre.y + subdividedSize
            ),
            subdividedSize
    );
    se->boundry = AABB(
            Vec2(
                boundry.centre.x + subdividedSize,
                boundry.centre.y + subdividedSize
            ),
            subdividedSize
    );

    while (pointCount > 0) {
        Vec2 point = points[--pointCount];
        void* data = userData[pointCount];
        if (!nw->insert(point, data) &&
            !ne->insert(point, data) &&
            !sw->insert(point, data) &&
            !se->insert(point, data)
        ) {
            return false;
        }
    }

    return true;
}

void QuadTree::queryRange(AABB range, void* result[QUADTREE_MAX_QUERY_RESULTS]) {
    int count = 0;
    result[count] = NULL;

    if (!boundry.intersectsAABB(range)) {
        return;
    }

    for (int i = 0; i < pointCount && count < QUADTREE_MAX_QUERY_RESULTS; i++) {
        if (range.containsPoint(points[i])) {
            result[count++] = &userData[i];
        }
    }

    if (nw == NULL) {
        return;
    }

    // TODO !!WARNING!! BUFFER OVERFLOW POSSIBILITY
    nw->queryRange(range, result + count);
    ne->queryRange(range, result + count);
    sw->queryRange(range, result + count);
    se->queryRange(range, result + count);
}

// TODO userData may get lost
void QuadTree::clear() {
    pointCount = 0;

    if (nw) {
        nw->clear();
        ne->clear();
        sw->clear();
        se->clear();

        free(nw);
        free(ne);
        free(sw);
        free(se);

        nw = NULL;
        ne = NULL;
        sw = NULL;
        se = NULL;
    }
}
