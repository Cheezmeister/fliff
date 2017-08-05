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
    capsule.active = true;
    capsule.pos.x = bml::normrand();
    capsule.pos.y = bml::normrand();
    capsule.cost = 10;
    capsule.triggered = false;
}

bool collide(const Player& player, const FliffCapsule& capsule)
{
    return length(player.pos - capsule.pos) < 0.20;
}

void spawn_nugget(FliffNugget& nugget, bml::Vec pos)
{
    nugget.active = true;
    nugget.pos = pos;
    nugget.vel.x = 0; //bml::normrand() * 0.01;
    nugget.vel.y = 0; //bml::normrand() * 0.01;
    nugget.amount = rand() % 10;
}

void hatch_capsule(GameState& state, FliffCapsule& capsule)
{
    capsule.active = false;
    if (bml::normrand() > 1) return; // SCAM!

    int nuggetcount = 10;
    /* int nuggetcount = rand() % 10; */


    for (int i = 0; i < nuggetcount; ++i)
    {
        for (int j = 0; j < MAX_NUGGETS; ++j)
        {
            FliffNugget& n = state.nuggets[j];
            if (n.active) continue;
            DEBUGVAR(capsule.pos);
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

    for (int i = 0; i < 1; ++i)
    {
        FliffCapsule& capsule = state.capsules[i];
        if (capsule.active)
        {
            if (collide(state.player, capsule))
            {
                hatch_capsule(state, capsule);
            }
        }
        else if (bml::normrand() > 0.9)
        {
            spawn_capsule(capsule);
        }

    }

}

}
