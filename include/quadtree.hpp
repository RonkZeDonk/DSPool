#ifndef QUADTREE_INCLUDE
#define QUADTREE_INCLUDE

// https://en.wikipedia.org/wiki/Quadtree#Pseudocode

#include "vec2.hpp"

#define QUADTREE_MAX_QUERY_RESULTS 16

class AABB {
public:
    Vec2 centre;
    int halfSize;

    AABB(Vec2 centre, int halfSize);
    bool containsPoint(Vec2 point);
    bool intersectsAABB(AABB other);
};

class QuadTree {
    static const int CAPACITY = 2;

    AABB boundry;

    Vec2 points[CAPACITY];
    void* userData[CAPACITY];
    int pointCount = 0;

    QuadTree* nw = NULL;
    QuadTree* ne = NULL;
    QuadTree* sw = NULL;
    QuadTree* se = NULL;

    QuadTree(AABB boundry);
    bool insert(Vec2 p, void* data);
    bool subdivide();
    void queryRange(AABB range, void* results[QUADTREE_MAX_QUERY_RESULTS]);
    void clear();
};

#endif // QUADTREE_INCLUDE
