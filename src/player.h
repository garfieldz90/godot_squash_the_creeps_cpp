#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot
{

    class Player : public CharacterBody3D
    {
        GDCLASS(Player, CharacterBody3D)

    private:
        int m_nSpeed, m_nFallAcceleration;
        Vector3 m_nVelocity, m_nPosition;
        Input* m_pInput;

    protected:
        static void _bind_methods();

    public:
        Player();
        ~Player();
        void _ready() override;
        void _process(double delta) override;
        void setSpeed(const int &p_speed);
        int getSpeed() const;
        void setFallAcceleration(const int &p_fallAcceleration);
        int getFallAcceleration() const;
    };
}

#endif