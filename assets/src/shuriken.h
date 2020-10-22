#ifndef SHURIKEN_H
#define SHURIKEN_H

#include <Godot.hpp>
#include <RigidBody2D.hpp>
#include <CollisionObject2D.hpp>
#include <AnimatedSprite.hpp>
#include "fighter.h"

using namespace godot;

constexpr double ANGULAR_VELOCITY = 20;

class Shuriken: public RigidBody2D
{
    
    GODOT_CLASS(Shuriken, RigidBody2D);

    public: 
        void _init();
        static void _register_methods();
        Shuriken();
        ~Shuriken();

        void _ready();
        void _process(double delta);
        //void _physics_process(double delta);

        //Note to self:
        // Fighter is an Area2D. It does not inherit from physicsbody2D
        // so the shuriken won't register collision with a Fighter 
        //void _on_Shuriken_body_entered(CollisionObject2D *body);
    
    private:
        double _Damage,
                _Speed,
                _Angular_Velocity;
        //Vector2 _Direction;
};

#endif