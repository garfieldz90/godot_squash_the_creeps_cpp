#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <godot_cpp/classes/control.hpp>

namespace godot
{
    class UserInterface : public Control
    {
        GDCLASS(UserInterface, Control);

    private:
    protected:
        static void _bind_methods();

    public:
    };
}

#endif