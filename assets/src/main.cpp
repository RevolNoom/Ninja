#include "main.h"

void Main::_init()
{
    _Shuriken_Scene = ResourceLoader::get_singleton()->load("res://scenes/Shuriken.tscn");  
}

void Main::_register_methods()
{
    register_method("_ready", &Main::_ready);
    register_method("_on_Fighter_Shuriken_Throw", &Main::_on_Fighter_Shuriken_Throw);
    
    register_property("_Shuriken_Scene", &Main::_Shuriken_Scene, 
                        Ref<PackedScene>(PackedScene::_new()));
}

void Main::_ready()
{
    Start_Game();
}


void Main::Start_Game()
{
    get_node<Area2D>("Goblin")->set_position(
                            get_node<Position2D>("StartPositionGoblin")->get_position());

    get_node<Area2D>("Human")->set_position(
                            get_node<Position2D>("StartPositionHuman")->get_position());
}

void Main::_on_Fighter_Shuriken_Throw(Fighter *Thrower, Vector2 Direction)
{
    if (!(_Shuriken_Scene->can_instance()))
    {
        Godot::print("Can't instance Shuriken");
        return;
    }

    Shuriken *s = (Shuriken*) _Shuriken_Scene->instance();

    if (s == nullptr)
    {
        Godot::print("I'm NULL!");
        return;
    }

    add_child(s);

    s->show();
    
    auto Is_Facing_Right = Thrower->get_node<AnimatedSprite>("AnimatedSprite")->is_flipped_h();

    Godot::print("Character size: " + Thrower->_Character_Size);
    s->set_global_position(
            Vector2(
                    Thrower->get_global_position().x + 
                            Thrower->_Character_Size.x * 
                                (Is_Facing_Right? 2 : -2)
                    ,
                    Thrower->get_global_position().y
    ));
    

    s->set_axis_velocity(
            Vector2(Is_Facing_Right? 1000 : -1000
                    , 0));
}

Main::Main()
{}

Main::~Main()
{}



