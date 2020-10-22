#include "fighter.h"

#define KEYPRESS (*godot::Input::get_singleton())


void Fighter::_process(double delta)
{

    _Velocity.x = 0;
    if (KEYPRESS.is_key_pressed(_Key_Right))
        _Velocity.x += _Speed;

    if (KEYPRESS.is_key_pressed(_Key_Left))
        _Velocity.x -= _Speed;
    
    if (KEYPRESS.is_key_pressed(_Key_Jump) && 
        _Current_Gravity == 0) //See if we're standing on a platform
        _Velocity.y = - _Speed * _Jump_Power;

    _Velocity.y += _Current_Gravity*delta;

    if (_Current_Cooldown <= 0 && KEYPRESS.is_key_pressed(_Key_Throw))
    {
        //_Anim_Sprite->set_animation();
        _Anim_Sprite->play("throw_left");

        Vector2 Direction= Vector2(-1, 0);
        if (_Anim_Sprite->is_flipped_h())
            Direction.x = 1; 
        
        Godot::print("I threw a shuriken!");
        emit_signal("Shuriken_Throw", this, Direction);
        _Current_Cooldown = _Shuriken_Cooldown;
    }  

    _Current_Cooldown -= delta;
    _Current_Cooldown = _Current_Cooldown < 0? 0 : _Current_Cooldown;

    if (_Anim_Sprite->get_animation()!= "throw_left")
    {
        if (_Velocity.x != 0)
        {
            _Anim_Sprite->set_flip_h(_Velocity.x > 0);
            _Anim_Sprite->play();
        }
        else
        {
            _Anim_Sprite->stop();
        }
    }

    _Last_Position = get_global_position();
    auto new_position = get_global_position() + _Velocity*delta;

    set_global_position(new_position);
}


void Fighter::_on_AnimatedSprite_animation_finished()
{
    _Anim_Sprite->play("left");
}

void Fighter::_ready()
{
    // Initializing things that can't be called in init()
    // without breaking the game

    _Anim_Sprite=get_node<AnimatedSprite>("AnimatedSprite");

    auto Race_lowered = _Race.to_lower();
    
    if (Race_lowered == "human")
        setup_race();
    else if (Race_lowered == "goblin")
        setup_race(0.8, 
                    1.22, 
                    2,
                    GlobalConstants::KEY_UP, 
                    GlobalConstants::KEY_LEFT,
                    GlobalConstants::KEY_RIGHT,
                    GlobalConstants::KEY_DOWN);
    

    Ref<RectangleShape2D> Rect = get_node<CollisionShape2D>("CollisionShape2D")->get_shape();
    _Character_Size = Rect->get_extents();
    _Screen_Size = get_viewport_rect().get_size();
    
    
    // Setting Animations
    _Anim_Sprite->set_sprite_frames(ResourceLoader::get_singleton()
                        ->load("res://assets/anims/" + Race_lowered + "/"
                                     + Race_lowered + "_anim.tres" ));
    if (_Anim_Sprite==nullptr)
    {
        Godot::print_error("_Anim_Sprite nullptr", "_ready", "fighter.cpp", 95);
        return;
    }
    _Anim_Sprite->set_animation("left");
    _Anim_Sprite->show();
    _Anim_Sprite->set_global_scale(Vector2(1.5, 1.5));

    // Setting Signals
    connect("Shuriken_Throw", get_parent(), "_on_Fighter_Shuriken_Throw");
    connect("body_entered", this, "_on_Fighter_body_entered");
    connect("body_exited", this, "_on_Fighter_body_exited");

}

void Fighter::_init()
{
    _Race = String("Human");
}

void Fighter::setup_race(double HpMultiplier,
                        double SpdMultiplier,
                        double JumpPower,
                        int KeyJump, 
                        int KeyLeft, 
                        int KeyRight,
                        int KeyThrow,
                        int TotalShuriken,
                        double ShurikenCooldown,
                        double HitPoint,
                        double Speed)
{
    _Jump_Power=JumpPower;
    _Key_Jump = KeyJump;
    _Key_Left = KeyLeft;
    _Key_Throw = KeyThrow;
    _Key_Right = KeyRight;
    _Total_Shuriken = TotalShuriken;
    _Shuriken_Cooldown = ShurikenCooldown;
    _Hit_Point=HitPoint*HpMultiplier;
    _Speed=Speed*SpdMultiplier;

    _Velocity = Vector2();
    _Gravity = DEFAULT_GRAVITY;
    _Current_Cooldown = 0;
    _Current_Gravity = _Gravity;

    
}

void Fighter::_on_Fighter_body_entered(godot::PhysicsBody2D *body)
{
    //Godot::print(String("Hey, a ") + body->___get_class_name() + String(" hit me! :("));
    
    //One way collision on the upper side of the platform
    if (body->is_class("StaticBody2D"))
    {
        //Godot::print(String("Luckily, it's only a StaticBody2D"));

        auto ColliShape = body->get_node<CollisionShape2D>("CollisionShape2D");
        auto rect = ColliShape->get_shape();
        Vector2 rectpos= cast_to<RectangleShape2D>(rect.ptr())->get_extents();
    
        if (ColliShape->get_global_position().y  >= _Last_Position.y)
        {
            //Put the fighter on the platform, instead of
            //hanging in the mid-air
            set_global_position(Vector2(get_position().x, ColliShape->get_global_position().y - _Character_Size.y));
            
            _Velocity.y = 0;
            _Current_Gravity = 0;
        }
    }
    
    //Note to self:
    // For precise type checking, use cast_to
    //else if (body->is_class("Shuriken"))
    
    else if (cast_to<Shuriken>(body)!=nullptr)
    {
        //Godot::print("Finally a shuriken");

        _Hit_Point -= (double) body->get("Damage");
        if (_Hit_Point<=0)
        {
            set_deferred("disabled", true);
            queue_free();
        }
        
        body->set_deferred("disabled", true);
        body->queue_free();
    }
    else 
           Godot::print("_on_Fighter_body_entered: Unknown body collided");
}


void Fighter::_on_Fighter_body_exited(godot::PhysicsBody2D *body)
{
    if (body->is_class("StaticBody2D"))
        _Current_Gravity = _Gravity;
}


void Fighter::_register_methods()
{
    register_method("_ready", &Fighter::_ready);
    register_method("_process", &Fighter::_process);
    register_method("_on_Fighter_body_exited", &Fighter::_on_Fighter_body_exited);
    register_method("_on_Fighter_body_entered", &Fighter::_on_Fighter_body_entered);
    register_method("_on_AnimatedSprite_animation_finished", &Fighter::_on_AnimatedSprite_animation_finished);

    register_property("Race", &Fighter::_Race, String("Human"));
    register_property("Key_Right", &Fighter::_Key_Right, GlobalConstants::KEY_D);
    register_property("Key_Left", &Fighter::_Key_Left, GlobalConstants::KEY_A);
    register_property("Key_Jump", &Fighter::_Key_Jump, GlobalConstants::KEY_W);
    register_property("Key_Throw", &Fighter::_Key_Throw, GlobalConstants::KEY_S);
    register_property("Total_Shuriken", &Fighter::_Total_Shuriken, 3);
    register_property("Shuriken_Cooldown", &Fighter::_Shuriken_Cooldown, 1.0);
    register_property("Hit_Point", &Fighter::_Hit_Point, 10000.0);
    register_property("Speed", &Fighter::_Speed, 400.0);
    register_property("Gravity", &Fighter::_Gravity, DEFAULT_GRAVITY);
    
    register_signal<Fighter>("Shuriken_Throw", "Thrower", GODOT_VARIANT_TYPE_OBJECT,     
                                                "Direction", GODOT_VARIANT_TYPE_VECTOR2);
    
    //register_property()
}

Fighter::Fighter()
{
}

Fighter::~Fighter()
{
}
