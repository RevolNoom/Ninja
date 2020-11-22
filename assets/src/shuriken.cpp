#include "shuriken.h"


void Shuriken::_init()
{
    //set_collision_layer(0b1);
    //set_collision_mask(0b1);
    _Speed = 2000;
    _Damage= 5000;
    //set_inertia(0);
    _Angular_Velocity = ANGULAR_VELOCITY;
    set_angular_velocity(_Angular_Velocity);
    connect("body_entered", this, "_on_Shuriken_body_entered");
    //_Direction = Vector2();
}

void Shuriken::_register_methods()
{
    register_method("_ready", &Shuriken::_ready);
    //register_method("_process", &Shuriken::_process);


    register_method("_on_Shuriken_body_entered", &Shuriken::_on_Shuriken_body_entered);
    register_method("_on_Timer_timeout", &Shuriken::_on_Timer_timeout);
    register_method("_on_VisibilityNotifier2D_screen_exited", &Shuriken::_on_VisibilityNotifier2D_screen_exited);


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

void Shuriken::_on_Shuriken_body_entered(PhysicsBody2D *body)
{
    auto Fighter_Body = cast_to<Fighter>(body); 
    if (Fighter_Body != nullptr)
    {
        Fighter_Body->Take_Damage(_Damage);
        set_deferred("disabled", true);
        queue_free();
    }
    else
    {   
        set_gravity_scale(10);
        get_node<Timer>("Timer")->start();
    }
}

void Shuriken::_on_Timer_timeout()
{
    set_deferred("disabled", true);
    queue_free();
}

void Shuriken::_on_VisibilityNotifier2D_screen_exited()
{
    set_deferred("disabled", true);
    queue_free();
}


void Shuriken::_ready()
{
    set_angular_velocity(ANGULAR_VELOCITY);
    get_node<Timer>("Timer")->set_wait_time(2);
    _Speed = 2000;
}

void Shuriken::_process(double delta)
{
}
