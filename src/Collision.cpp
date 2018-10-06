//
// Created by bruno.rezende on 29/09/18.
//

#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Collision.h"

namespace Collision {
    void ProjectOntoAxis(vector<sf::Vector2f> box, const sf::Vector2f &Axis, float &Min,
                         float &Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
    {
        Min = (box[0].x * Axis.x + box[0].y * Axis.y);
        Max = Min;
        for (int j = 1; j < 4; j++) {
            float Projection = (box[j].x * Axis.x + box[j].y * Axis.y);

            if (Projection < Min)
                Min = Projection;
            if (Projection > Max)
                Max = Projection;
        }
    }

    bool BoundingBoxTest(Sprite *sprite1, Sprite *sprite2) {
        vector<sf::Vector2f> box1 = sprite1->getBox();
        vector<sf::Vector2f> box2 = sprite2->getBox();

        sf::Vector2f Axes[4] = {
                sf::Vector2f(box1[1].x - box1[0].x,
                             box1[1].y - box1[0].y),
                sf::Vector2f(box1[1].x - box1[2].x,
                             box1[1].y - box1[2].y),
                sf::Vector2f(box2[0].x - box2[3].x,
                             box2[0].y - box2[3].y),
                sf::Vector2f(box2[0].x - box2[1].x,
                             box2[0].y - box2[1].y)
        };

        for (auto Axe : Axes) // For each axis...
        {
            float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

            // ... project the points of both OBBs onto the axis ...
            Collision::ProjectOntoAxis(box1, Axe, MinOBB1, MaxOBB1);
            Collision::ProjectOntoAxis(box2, Axe, MinOBB2, MaxOBB2);

            // ... and check whether the outermost projected points of both OBBs overlap.
            // If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
            if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
                return false;
        }
        return true;

    }
};


