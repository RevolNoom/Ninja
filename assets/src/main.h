#ifndef MAIN_H
#define MAIN_H

#include <Godot.hpp>
#include <ResourceLoader.hpp>
#include <CollisionObject2D.hpp>
#include <Position2D.hpp>
#include <Area2D.hpp>
#include <PackedScene.hpp>
#include <Node.hpp>
#include "shuriken.h"
#include "fighter.h"

using namespace godot;

class Main: public Node
{
    GODOT_CLASS(Main, Node);

    public:
        void _init();
        static void _register_methods();
        void _ready();
        Main();
        ~Main();
        
        void Start_Game();
        void _on_Fighter_Shuriken_Throw(Fighter *Thrower, Vector2 Direction);

    private:
        Ref<PackedScene> _Shuriken_Scene;

};

#endif