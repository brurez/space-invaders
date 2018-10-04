//
// Created by bruno.rezende on 29/09/18.
//

#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Collision.h"

namespace Collision {
    class BitmaskManager {
    public:
        ~BitmaskManager() {
            std::map<const sf::Texture *, sf::Uint8 *>::const_iterator end = Bitmasks.end();
            for (std::map<const sf::Texture *, sf::Uint8 *>::const_iterator iter = Bitmasks.begin();
                 iter != end; iter++)
                delete[] iter->second;
        }

        sf::Uint8 GetPixel(const sf::Uint8 *mask, const sf::Texture *tex, unsigned int x, unsigned int y) {
            if (x > tex->getSize().x || y > tex->getSize().y)
                return 0;

            return mask[x + y * tex->getSize().x];
        }

        sf::Uint8 *GetMask(const sf::Texture *tex) {
            sf::Uint8 *mask;
            std::map<const sf::Texture *, sf::Uint8 *>::iterator pair = Bitmasks.find(tex);
            if (pair == Bitmasks.end()) {
                sf::Image img = tex->copyToImage();
                mask = CreateMask(tex, img);
            } else
                mask = pair->second;

            return mask;
        }

        sf::Uint8 *CreateMask(const sf::Texture *tex, const sf::Image &img) {
            sf::Uint8 *mask = new sf::Uint8[tex->getSize().y * tex->getSize().x];

            for (unsigned int y = 0; y < tex->getSize().y; y++) {
                for (unsigned int x = 0; x < tex->getSize().x; x++)
                    mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
            }

            Bitmasks.insert(std::pair<const sf::Texture *, sf::Uint8 *>(tex, mask));

            return mask;
        }

    private:
        std::map<const sf::Texture *, sf::Uint8 *> Bitmasks;
    };

    BitmaskManager Bitmasks;

    bool PixelPerfectTest(const sf::Sprite &Object1, const sf::Sprite &Object2, sf::Uint8 AlphaLimit) {
        sf::FloatRect Intersection;
        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
            sf::IntRect O1SubRect = Object1.getTextureRect();
            sf::IntRect O2SubRect = Object2.getTextureRect();

            sf::Uint8 *mask1 = Bitmasks.GetMask(Object1.getTexture());
            sf::Uint8 *mask2 = Bitmasks.GetMask(Object2.getTexture());

            // Loop through our pixels
            for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
                for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

                    sf::Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
                    sf::Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);

                    // Make sure pixels fall within the sprite's subrect
                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
                        o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
                        o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

                        if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int) (o1v.x) + O1SubRect.left,
                                              (int) (o1v.y) + O1SubRect.top) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, Object2.getTexture(), (int) (o2v.x) + O2SubRect.left,
                                              (int) (o2v.y) + O2SubRect.top) > AlphaLimit)
                            return true;

                    }
                }
            }
        }
        return false;
    }

    bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string &Filename) {
        sf::Image img;
        if (!img.loadFromFile(Filename))
            return false;
        if (!LoadInto.loadFromImage(img))
            return false;

        Bitmasks.CreateMask(&LoadInto, img);
        return true;
    }

    sf::Vector2f GetSpriteCenter(const sf::Sprite &Object) {
        sf::FloatRect AABB = Object.getGlobalBounds();
        return sf::Vector2f(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
    }

    sf::Vector2f GetSpriteSize(const sf::Sprite &Object) {
        sf::IntRect OriginalSize = Object.getTextureRect();
        sf::Vector2f Scale = Object.getScale();
        return sf::Vector2f(OriginalSize.width * Scale.x, OriginalSize.height * Scale.y);
    }

    bool CircleTest(const sf::Sprite &Object1, const sf::Sprite &Object2) {
        sf::Vector2f Obj1Size = GetSpriteSize(Object1);
        sf::Vector2f Obj2Size = GetSpriteSize(Object2);
        float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
        float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;

        sf::Vector2f Distance = GetSpriteCenter(Object1) - GetSpriteCenter(Object2);

        return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
    }

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

    bool BoundingBoxTest(Sprite* sprite1, Sprite* sprite2) {
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


