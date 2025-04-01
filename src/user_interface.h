#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>

namespace godot
{
    class UserInterface : public Control
    {
        GDCLASS(UserInterface, Control);

    private:
        int m_score;
        Label *m_score_label;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void add_score();
        UserInterface();
        ~UserInterface();
    };
}

#endif