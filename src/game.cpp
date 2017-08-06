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

GameState init()
{
  GameState state = {0};
  state.player.fliff = 10;
  return state;
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

void bounce_in_bounds(Entity& entity)
{
    float right = 1;
    float left = -1;
    float top = 1;
    float bottom = -1;

    if (entity.pos.x > right) entity.vel.x = -entity.vel.x;
    if (entity.pos.x < left) entity.vel.x = -entity.vel.x;

    if (entity.pos.y > top) entity.vel.y = -entity.vel.y;
    if (entity.pos.y < bottom) entity.vel.y = -entity.vel.y;
}

/* void move(Entity& entity) */
/* { */
/*     entity.pos += entity.vel; */
/* } */

void spawn_capsule(FliffCapsule& capsule)
{
    capsule.active = true;
    capsule.pos.x = bml::normrand();
    capsule.pos.y = bml::normrand();
    capsule.cost = rand() % 10;
    capsule.triggered = false;
}

bool collide(const Player& player, const FliffNugget& nug)
{
    return length(player.pos - nug.pos) < 0.10;
}

bool collide(const Player& player, const FliffCapsule& capsule)
{
    return length(player.pos - capsule.pos) < 0.20;
}

void spawn_nugget(FliffNugget& nugget, bml::Vec pos)
{
    nugget.active = true;
    nugget.pos = pos;
    nugget.vel.x = 0.01 * bml::normrand();
    nugget.vel.y = 0.01 * bml::normrand();
    nugget.amount = rand() % 10;
}

void hatch_capsule(GameState& state, FliffCapsule& capsule)
{
    capsule.active = false;
    if (bml::normrand() > 1) return; // SCAM!

    int nuggetcount = rand() % 10;


    for (int i = 0; i < nuggetcount; ++i)
    {
        for (int j = 0; j < MAX_NUGGETS; ++j)
        {
            FliffNugget& n = state.nuggets[j];
            if (n.active) continue;
            spawn_nugget(n, capsule.pos);
        }
    }

}

void update(GameState& state, const Input& input)
{
    if (input.sys.resized)
    {
        resize(state, input);
    }

    control(state.player, input, LATERAL);
    bounce_in_bounds(state.player);

    // Capsules
    for (int i = 0; i < MAX_CAPSULES; ++i)
    {
        FliffCapsule& capsule = state.capsules[i];
        if (capsule.active)
        {
            if (capsule.triggered)
            {
              if (--capsule.fuse <= 0)
              {
                hatch_capsule(state, capsule);
              }
              if (collide(state.player, capsule))
              {
                bml::Vec axis = capsule.pos - state.player.pos;
                /* bml::Vec projection = bml::project(state.player.vel, axis); */
                state.player.vel += (0.02 / length(axis) * -axis);
              }
            }
            else if (collide(state.player, capsule))
            {
                // hatch_capsule(state, capsule);
                capsule.triggered = true;
                capsule.fuse = 60;
                state.player.fliff -= capsule.cost;
            }
        }
        else if (bml::normrand() > 0.9)
        {
            spawn_capsule(capsule);
        }

    }

    // Nuggets
    for (int i = 0; i < MAX_NUGGETS; ++i)
    {
        FliffNugget& nugget = state.nuggets[i];
        if (!nugget.active) continue;
        nugget.pos += nugget.vel;
        bounce_in_bounds(nugget);

        if (collide(state.player, nugget))
        {
            state.player.fliff += nugget.amount;
            nugget.active = false;
        }
    }

}

}
