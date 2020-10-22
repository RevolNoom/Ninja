#include "shuriken.h"


void Shuriken::_init()
{
    set_collision_layer(0b1);
    set_collision_mask(0b1);
    _Speed = 1000;
    _Damage= 1000;
    _Angular_Velocity = ANGULAR_VELOCITY;
    set_angular_velocity(_Angular_Velocity);
    //_Direction = Vector2();
}

void Shuriken::_register_methods()
{
    register_method("_ready", &Shuriken::_ready);
    register_method("_process", &Shuriken::_process);


    //register_method("_on_Shuriken_body_entered", &Shuriken::_on_Shuriken_body_entered);

    register_property("Speed", &Shuriken::_Speed, 1000.0);
    register_property("Damage", &Shuriken::_Damage, 1000.0);
    register_property("Angular_Velocity", &Shuriken::_Angular_Velocity, ANGULAR_VELOCITY);
}

Shuriken::Shuriken()
{
}

Shuriken::~Shuriken()
{
}

void Shuriken::_ready()
{
    set_angular_velocity(ANGULAR_VELOCITY);
    
    auto Anim=get_node<AnimatedSprite>("AnimatedSprite");
    if (Anim == nullptr)
    {
        Godot::print("Shuriken: Can't find anim sprite");
        return;
    }

    Anim->set_animation("default");
    show();
    Anim->play();
}

void Shuriken::_process(double delta)
{
    
}
