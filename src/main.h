#ifndef MAIN_H
#define MAIN_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/timer.hpp>
#include "player.h"
#include "mob.h"

namespace godot
{

    class Main : public Node
    {
        GDCLASS(Main, Node)

    private:
        Ref<PackedScene> m_mob_scene;
        Timer *m_mob_timer;
        Player *m_player;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void set_mob_scene(const Ref<PackedScene> &p_mob_scene);
        Ref<PackedScene> get_mob_scene() const;
        void on_mob_timer_timeout();
    };
}

#endif