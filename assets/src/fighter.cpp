#include "fighter.h"

#define KEYPRESS (*godot::Input::get_singleton())


void Fighter::_process(double delta)
{
    
    if (KEYPRESS.is_key_pressed(_Key_Right))
        _Velocity.x = _Speed;

    if (KEYPRESS.is_key_pressed(_Key_Left))
        _Velocity.x = -_Speed;

    if (KEYPRESS.is_key_pressed(_Key_Jump) && is_on_floor())
    {
        _Velocity.y = - _Speed * _Jump_Power;
    }


    if (_Throw_Current_Cooldown <= 0 
        && KEYPRESS.is_key_pressed(_Key_Throw)
        && _Shuriken_Left > 0)
    {
        --_Shuriken_Left;

        get_node<Label>("Control/HBoxContainer/Shuriken_Left")->set_text(String::num_int64(_Shuriken_Left));

        _Anim_Sprite->play("throw_left");

        Vector2 Direction= Vector2(-1, 0);
        if (_Anim_Sprite->is_flipped_h())
            Direction.x = 1; 
        
        emit_signal("Shuriken_Throw", this, Direction);
        _Throw_Current_Cooldown = _Throw_Cooldown;
    }  

    _Throw_Current_Cooldown -= delta;
    _Throw_Current_Cooldown = _Throw_Current_Cooldown < 0? 0 : _Throw_Current_Cooldown;

    if (_Shuriken_Left<_Total_Shuriken)
    {
        _New_Shuriken_Current_Cooldown -= delta;
        if (_New_Shuriken_Current_Cooldown < 0)
        {
            ++_Shuriken_Left;
            _New_Shuriken_Current_Cooldown = _New_Shuriken_Cooldown;
            get_node<Label>("Control/HBoxContainer/Shuriken_Left")->set_text(String::num_int64(_Shuriken_Left));
        }
    }

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
}

void Fighter::_physics_process(double delta)
{
    _Velocity = move_and_slide(_Velocity, Vector2(0, -1));

    _Velocity.y += DEFAULT_GRAVITY * delta;

    _Velocity.x = std::abs(_Velocity.x) < _Speed/3 ? 0 : _Velocity.x * 0.95;
}


void Fighter::_on_AnimatedSprite_animation_finished()
{
    _Anim_Sprite->play("left");
}

void Fighter::_ready()
{
    // Initializing things that can't be called in init()
    // without breaking the game
    //connect()
    
    _Anim_Sprite=get_node<AnimatedSprite>("AnimatedSprite");

    auto Race_lowered = _Race.to_lower();
    
    if (Race_lowered == "human")
        setup_race();
    else if (Race_lowered == "goblin")
        setup_race(0.9, 
                    1.1, 
                    DEFAULT_JUMP_POWER,
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
    get_node<Label>("Control/HBoxContainer/Shuriken_Left")->set_text(String::num_int64(_Shuriken_Left));
    //Godot::print("Character size: " + _Race + _Character_Size);

    if (_Anim_Sprite==nullptr)
    {
        Godot::print_error("_Anim_Sprite nullptr", "_ready", "fighter.cpp", 95);
        return;
    }
    _Anim_Sprite->set_animation("left");
    _Anim_Sprite->show();
    _Anim_Sprite->set_global_scale(Vector2(1.5, 1.5));

    // Setting Signals
    connect("Shuriken_Throw", get_tree()->get_current_scene(), "_on_Fighter_Shuriken_Throw");
    connect("die", get_tree()->get_current_scene(), "_on_Fighter_die");
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
                        double ThrowCooldown,
                        double NewShurikenCooldown,
                        double HitPoint,
                        double Speed)
{
    _Jump_Power=JumpPower;
    _Key_Jump = KeyJump;
    _Key_Left = KeyLeft;
    _Key_Throw = KeyThrow;
    _Key_Right = KeyRight;
    _Total_Shuriken = TotalShuriken;
    _Shuriken_Left=_Total_Shuriken;

    _Throw_Cooldown = ThrowCooldown;
    _Throw_Current_Cooldown = 0;
    _New_Shuriken_Cooldown = NewShurikenCooldown;
    _New_Shuriken_Current_Cooldown = _New_Shuriken_Cooldown;
    _Hit_Point=HitPoint*HpMultiplier;
    _Speed=Speed*SpdMultiplier;
}


void Fighter::Reset_For_New_Game()
{
    _Hit_Point = DEFAULT_HIT_POINT * DEFAULT_HP_MULTIPLIER;
    _Shuriken_Left=_Total_Shuriken;
    _Throw_Cooldown = DEFAULT_THROW_COOLDOWN;
    _Throw_Current_Cooldown = 0;
    _New_Shuriken_Cooldown = DEFAULT_NEW_SHURIKEN_COOLDOWN;
    _New_Shuriken_Current_Cooldown = _New_Shuriken_Cooldown;
}


void Fighter::Take_Damage(double damage)
{
    _Hit_Point -= damage;
    if (_Hit_Point <= 0)
    {
        emit_signal("die", this);
    }
}

void Fighter::_register_methods()
{
    register_method("_ready", &Fighter::_ready);
    register_method("_process", &Fighter::_process);
    register_method("_physics_process", &Fighter::_physics_process);
    register_method("_on_AnimatedSprite_animation_finished", &Fighter::_on_AnimatedSprite_animation_finished);

    register_property("Race", &Fighter::_Race, String("Human"));
    register_property("Key_Right", &Fighter::_Key_Right, GlobalConstants::KEY_D);
    register_property("Key_Left", &Fighter::_Key_Left, GlobalConstants::KEY_A);
    register_property("Key_Jump", &Fighter::_Key_Jump, GlobalConstants::KEY_W);
    register_property("Key_Throw", &Fighter::_Key_Throw, GlobalConstants::KEY_S);
    register_property("Total_Shuriken", &Fighter::_Total_Shuriken, 3);
    register_property("New_Shuriken_Cooldown", &Fighter::_New_Shuriken_Cooldown, DEFAULT_NEW_SHURIKEN_COOLDOWN);
    register_property("Throw_Cooldown", &Fighter::_Throw_Cooldown, DEFAULT_THROW_COOLDOWN);
    register_property("Hit_Point", &Fighter::_Hit_Point, DEFAULT_HIT_POINT);
    register_property("Speed", &Fighter::_Speed, DEFAULT_SPEED);
    
    register_signal<Fighter>("Shuriken_Throw", "Thrower", GODOT_VARIANT_TYPE_OBJECT,     
                                                "Direction", GODOT_VARIANT_TYPE_VECTOR2);

    register_signal<Fighter>("die", "Fighter", GODOT_VARIANT_TYPE_OBJECT);
                                
    
}

Fighter::Fighter()
{
}

Fighter::~Fighter()
{
}
