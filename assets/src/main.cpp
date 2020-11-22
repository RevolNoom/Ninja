#include "main.h"

void Main::_init()
{
}

void Main::_register_methods()
{
    register_method("_ready", &Main::_ready);
    register_method("_on_Fighter_Shuriken_Throw", &Main::_on_Fighter_Shuriken_Throw);
    register_method("_on_Fighter_die", &Main::_on_Fighter_die);
    register_method("_on_Button_pressed", &Main::_on_Button_pressed);

    register_property("_Shuriken_Scene", &Main::_Shuriken_Scene, 
                        Ref<PackedScene>(PackedScene::_new()));

}

void Main::_ready()
{ 
    _Shuriken_Scene = ResourceLoader::get_singleton()->load("res://scenes/Shuriken.tscn"); 
    
    auto Goblin = get_node<Fighter>("Players/Goblin");
    auto Human = get_node<Fighter>("Players/Human");

    Goblin->hide();
    Human->hide();
}

void Main::Start_Game()
{
    get_node<Control>("StartScreen")->hide();

    get_node<Control>("EndScreen")->hide();
    
    auto Goblin = get_node<Fighter>("Players/Goblin");
    auto Human = get_node<Fighter>("Players/Human");
    
    //Goblin->set_global_position(                get_node<Position2D>("StartPositionGoblin")->get_global_position());
    Goblin->Reset_For_New_Game();
    Goblin->show();


    //Human->set_global_position(                get_node<Position2D>("StartPositionHuman")->get_global_position());
    Human->Reset_For_New_Game();
    Human->show();
}

void Main::_on_Button_pressed()
{
    Start_Game();
}

void Main::_on_Fighter_die(Fighter *fighter)
{
    fighter->hide();
    get_node<Control>("EndScreen")->show(); 
}

void Main::_on_Fighter_Shuriken_Throw(Fighter *Thrower, Vector2 Direction)
{
    if (!(Thrower->is_visible()))
        return;
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

    s->set_global_position(
            Vector2(
                    Thrower->get_global_position().x + 
                            Thrower->_Character_Size.x * 
                                (Is_Facing_Right? 2 : -2)
                    ,
                    Thrower->get_global_position().y
    ));


    s->set_axis_velocity(Vector2( 2000 * (Is_Facing_Right? 1 : -1)
                                                                , 0));
}

Main::Main()
{}

Main::~Main()
{}



