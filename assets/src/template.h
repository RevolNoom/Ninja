#ifndef 
#define

#include <Godot.hpp>

using namespace godot;

class xxx: public yyy
{
    GODOT_CLASS(xxx, yyy);
    public:
        void _init();
        static void _register_methods();
	xxx();
	~xxx();

        void _ready();
        void _process(double delta);
    private:
};

#endif
