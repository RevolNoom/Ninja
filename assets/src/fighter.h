#ifndef FIGHTER_H
#define FIGHTER_H

#include <cmath>
#include <SceneTree.hpp>
#include <Godot.hpp>
#include <Label.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <PhysicsBody2D.hpp>
#include <CollisionShape2D.hpp>
#include <PhysicsMaterial.hpp>
#include <AnimatedSprite.hpp>
#include <PackedScene.hpp>
#include <SpriteFrames.hpp>
#include <RectangleShape2D.hpp>
#include <Input.hpp>
#include <GlobalConstants.hpp>
#include <ResourceLoader.hpp>
#include "shuriken.h"

using namespace godot;

constexpr double DEFAULT_GRAVITY= 981.0*2,
                DEFAULT_HIT_POINT=10000,
                DEFAULT_SPEED = 350,
                DEFAULT_HP_MULTIPLIER = 1,
                DEFAULT_SPD_MULTIPLIER= 1,
                DEFAULT_JUMP_POWER = 3,
                DEFAULT_NEW_SHURIKEN_COOLDOWN=3,
                DEFAULT_TOTAL_SHURIKEN=3,
                DEFAULT_THROW_COOLDOWN=0.5;


class Fighter: public KinematicBody2D
{

        GODOT_CLASS(Fighter, KinematicBody2D);
        public:
                void _init();
                static void _register_methods();
                Fighter();
                ~Fighter();

                void _ready();

                //
                void _process(double delta);
                void _physics_process(double delta);

                // Setup the input keypress, frames,...
                // to correspond to its race
                void setup_race(double HpMultiplier = DEFAULT_HP_MULTIPLIER,
                                double SpdMultiplier = DEFAULT_SPD_MULTIPLIER,
                                double JumpPower = DEFAULT_JUMP_POWER,
                                int KeyJump = GlobalConstants::KEY_W,
                                int KeyLeft = GlobalConstants::KEY_A,
                                int KeyRight = GlobalConstants::KEY_D,
                                int KeyThrow = GlobalConstants::KEY_S,
                                int TotalShuriken = DEFAULT_TOTAL_SHURIKEN,
                                double ThrowCooldown = DEFAULT_THROW_COOLDOWN,
                                double NewShurikenCooldown = DEFAULT_NEW_SHURIKEN_COOLDOWN,
                                double HitPoint = DEFAULT_HIT_POINT,
                                double Speed = DEFAULT_SPEED);

                void _on_AnimatedSprite_animation_finished();
                void Take_Damage(double damage);
                void Reset_For_New_Game();


        public:
                godot::String _Race;

                Vector2 _Character_Size,
                        _Screen_Size;
                        
        private:
                //Pointers to child nodes
                AnimatedSprite *_Anim_Sprite;

                Vector2 _Velocity;

                int     _Key_Jump,
                        _Key_Left,
                        _Key_Right,
                        _Key_Throw,
                        _Total_Shuriken,
                        _Shuriken_Left;
                double  _New_Shuriken_Cooldown,
                        _New_Shuriken_Current_Cooldown,
                        _Throw_Cooldown,
                        _Throw_Current_Cooldown,
                        _Jump_Power,
                        _Hit_Point,
                        _Speed;                         
};

#endif
