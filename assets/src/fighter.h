#ifndef FIGHTER_H
#define FIGHTER_H

#include <Godot.hpp>
#include <Area2D.hpp>
#include <PhysicsBody2D.hpp>
#include <CollisionShape2D.hpp>
#include <AnimatedSprite.hpp>
#include <PackedScene.hpp>
#include <SpriteFrames.hpp>
#include <RectangleShape2D.hpp>
#include <Input.hpp>
#include <GlobalConstants.hpp>
#include <ResourceLoader.hpp>
#include "shuriken.h"

using namespace godot;

constexpr double DEFAULT_GRAVITY = 981.0 * 2;

class Fighter: public Area2D
{

        GODOT_CLASS(Fighter, Area2D);
        public:
                void _init();
                static void _register_methods();
                Fighter();
                ~Fighter();

                void _ready();
                void _process(double delta);

                // Setup the input keypress, frames,...
                // to correspond to its race
                void setup_race(double HpMultiplier = 1.0,
                                double SpdMultiplier = 1.0,
                                double JumpPower = 2.5,
                                int KeyJump = GlobalConstants::KEY_W,
                                int KeyLeft = GlobalConstants::KEY_A,
                                int KeyRight = GlobalConstants::KEY_D,
                                int KeyThrow = GlobalConstants::KEY_S,
                                int TotalShuriken = 3,
                                double ShurikenCooldown = 1,
                                double HitPoint = 10000,
                                double Speed = 400);

                void _on_Fighter_body_entered(godot::PhysicsBody2D *body);
                void _on_Fighter_body_exited(godot::PhysicsBody2D *body);

        private:
                godot::String _Race;
                //Pointers to child nodes
                AnimatedSprite *_Anim_Sprite;

                Vector2 _Velocity,
                        _Last_Position,
                        _Character_Size,
                        _Screen_Size;
                
                int     _Key_Jump,
                        _Key_Left,
                        _Key_Right,
                        _Key_Throw,
                        _Total_Shuriken,
                        _Shuriken_Left;
                double  _Shuriken_Cooldown,
                        _Current_Cooldown,
                        _Jump_Power,
                        _Hit_Point,
                        _Speed,
                        _Gravity,  

                        // Temporary gravity that's affecting the fighter
                        // Becomes zero when standing on platforms
                        _Current_Gravity;                         
};

#endif
