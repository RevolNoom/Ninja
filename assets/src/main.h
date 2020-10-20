#ifndef MAIN_H
#define MAIN_H

#include <Godot.hpp>
#include <ResourceLoader.hpp>
#include <Position2D.hpp>
#include <Area2D.hpp>
#include <PackedScene.hpp>
#include <Node.hpp>

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
        void _on_Fighter_Shuriken_Throw();

    private:
        Ref<PackedScene> _Shuriken_Scene;

};

#endif