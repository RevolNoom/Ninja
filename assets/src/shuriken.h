#ifndef SHURIKEN_H
#define SHURIKEN_H

#include <Godot.hpp>
#include <RigidBody2D.hpp>
#include <CollisionObject2D.hpp>
#include <PhysicsBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <StaticBody2D.hpp>
#include "fighter.h"
#include <Timer.hpp>

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
        // After a collision, the shuriken won't ever collide anymore  
        void _on_Shuriken_body_entered(PhysicsBody2D *body);
        

    
        // After a collision, start the timer
        // When the timer clocks out, delete the shuriken
        void _on_Timer_timeout();

        // Also delete the shuriken when it goes out of the screen
        void _on_VisibilityNotifier2D_screen_exited();

        double _Damage,
                _Speed,
                _Angular_Velocity;
    private:
        //Vector2 _Direction;
};

#endif