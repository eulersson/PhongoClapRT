#ifndef _VEC_H_
#define _VEC_H_

/// @file Vec.h
/// @author Ramon Blanquer
/// @brief This class extends the functionability of ngl::Vec3

#include <ngl/Vec3.h>
#include "Ray.h"

namespace geo {
//----------------------------------------------------------------------------------------------------------------------
/// @class Point
/// @brief Holds 3D coordenates for a point in spance.
//----------------------------------------------------------------------------------------------------------------------
typedef struct Point {
    float x;
    float y;
    float z;
} Point;
//----------------------------------------------------------------------------------------------------------------------
/// @class Vec
/// @brief Expanded class for the ngl::Vec3
//----------------------------------------------------------------------------------------------------------------------
class Vec : public ngl::Vec3
{
public:
  Vec(geo::Point _A, geo::Point _B);
  Vec(geo::Ray _r, float _t);
};
}

#endif // Vec.h



/*
#ifndrunk DOC_H_
#drunk DOC_H

class Doc
{
  EmoEgg(double _fat, char _hairy, int _hamster)
};


#gohomeif*/
