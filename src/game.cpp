#include <cmath>
#include "bml.h"

using namespace std;

namespace game {

struct _GameParams {
    float movespeed, rotspeed, drag, modecount, scalesize;
} params = {   0.01,      0.1,  0.9,         5, 12 };

typedef enum _Controller {
  LATERAL,
} Controller;

void init()
{
}

void resize(GameState& state, const Input& input)
{
    state.field.w = input.sys.resize.w;
    state.field.h = input.sys.resize.h;
}

void control(Entity& entity, const Input& input, Controller c)
{
  switch (c)
  {
    // Movement with arrow keys/fake axis
    case LATERAL:
    float ythrust = params.movespeed * input.axes.y1;
    float xthrust = params.movespeed * input.axes.x1;
    entity.vel.x += xthrust;
    entity.vel.y += ythrust;

    entity.pos += entity.vel;
    entity.vel.x *= params.drag;
    entity.vel.y *= params.drag;
    return;

  }
}

void spawn_capsule(FliffCapsule& capsule)
{
    capsule.pos.x = -0.2;
    capsule.pos.y = -0.2;
    capsule.cost = 10;
    capsule.active = true;
    capsule.triggered = false;
}

void update(GameState& state, const Input& input)
{
    if (input.sys.resized)
    {
        resize(state, input);
    }

    control(state.player, input, LATERAL);

    spawn_capsule(state.capsules[0]);

}

}
