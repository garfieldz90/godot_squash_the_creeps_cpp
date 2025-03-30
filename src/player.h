#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/basis.hpp>

namespace godot
{

    class Player : public CharacterBody3D
    {
        GDCLASS(Player, CharacterBody3D)

    private:
        int m_speed, m_fall_acceleration;
        Vector3 m_target_velocity, m_position;
        Input *m_input;
        Node3D *m_pivot;
        Basis *m_basis;

    protected:
        static void _bind_methods();

    public:
        Player();
        ~Player();
        void _ready() override;
        void _physics_process(double delta) override;
        void set_speed(const int &p_speed);
        int get_speed() const;
        void set_fall_acceleration(const int &p_fall_acceleration);
        int get_fall_acceleration() const;
    };
}

#endif