#ifndef MAIN_H
#define MAIN_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/timer.hpp>
#include "player.h"
#include "mob.h"
#include "user_interface.h"
#include <godot_cpp/classes/color_rect.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot
{

    class Main : public Node
    {
        GDCLASS(Main, Node)

    private:
        Ref<PackedScene> m_mob_scene;
        Timer *m_mob_timer;
        Player *m_player;
        UserInterface *m_ui;
        ColorRect *m_retry;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void set_mob_scene(const Ref<PackedScene> &p_mob_scene);
        Ref<PackedScene> get_mob_scene() const;
        void on_mob_timer_timeout();
        void on_player_hit();
        void on_mob_squash();
        void _unhandled_input(const Ref<InputEvent> &p_event) override;
    };
}

#endif