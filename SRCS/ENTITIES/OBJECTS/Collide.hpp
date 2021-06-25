/*
** EPITECH PROJECT, 2021
** Collide
** File description:
** Collide
*/

#ifndef BOMBERMAN_COLLIDE_HPP
#define BOMBERMAN_COLLIDE_HPP

#include "raylib.h"
#include <vector>

class Collide {
public:
    BoundingBox _bbox;

    Collide(BoundingBox bbox, Vector3 position) : _bbox(setNewPosBBox(bbox, {0, 0, 0}, position)) {};
    virtual ~Collide() = default;

    static BoundingBox setNewPosBBox(BoundingBox bbox, Vector3 prev_pos, Vector3 new_pos) {
        float diff_x = new_pos.x - prev_pos.x;
        float diff_z = new_pos.z - prev_pos.z;

        bbox.max.x += diff_x;
        bbox.min.x += diff_x;
        bbox.max.z += diff_z;
        bbox.min.z += diff_z;

        return (bbox);
    };

    bool doCollide(Collide *other) {
        if (CheckCollisionBoxes(_bbox, other->_bbox))
            return true;
        return false;
    };

    bool doCollide(std::vector<Collide *> others) {
//        std::vector<Collide *> filtered;
//        for (int i = 0; i < others.size(); i++) {
//            if (_bbox.max.x > others[i]->_bbox.max.x) continue;
//            if (_bbox.max.y > others[i]->_bbox.max.y) continue;
//            if (_bbox.min.x < others[i]->_bbox.min.x) continue;
//            if (_bbox.min.y < others[i]->_bbox.min.y) continue;
//            filtered.emplace_back(others[i]);
//        } TODO opti collide

        for (auto ite = others.begin(); ite != others.end(); ite++) {
            if (ite.operator*() == this) continue;
            if (CheckCollisionBoxes(_bbox, ite.operator*()->_bbox))
                return true;
        }
        return false;
    };

    void drawBBox(Camera3D camera_3_d) {
        BeginMode3D(camera_3_d);

        DrawBoundingBox(_bbox, WHITE);
        EndMode3D();
    };
};

#endif //BOMBERMAN_COLLIDE_HPP
