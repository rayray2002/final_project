#include "CollisionClass.h"
#include "./ECS/ColliderComponent.h"
using namespace std;



bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
    if (recA.x + recA.w >= recB.x
     && recB.x + recB.w >= recA.x
     && recA.y + recA.h >= recB.y
     && recB.y + recB.h >= recA.y) {
         return true;
    }
    return false;
}

bool Collision::AABB(const ColliderComponent& colA, ColliderComponent& colB) {
    if ( AABB(colA.collider, colB.collider) ) {
        cout << colA.tag << " hit: " << colB.tag << endl;
        return true;
    }
    else {
        return false;
    }
}