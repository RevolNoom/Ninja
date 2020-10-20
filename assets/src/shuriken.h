#ifndef SHURIKEN_H
#define SHURIKEN_H

#include <Godot.hpp>
#include <RigidBody2D.hpp>
#include <AnimatedSprite.hpp>

using namespace godot;

constexpr double ANGULAR_VELOCITY = 2;

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
        void _physics_process(double delta);
    
    private:
        double _Damage,
                _Speed,
                _Angular_Velocity;
        //Vector2 _Direction;
};

#endif