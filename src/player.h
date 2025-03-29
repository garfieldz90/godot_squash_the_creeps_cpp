#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/character_body3d.hpp>

namespace godot
{

    class Player : public CharacterBody3D
    {
        GDCLASS(Player, CharacterBody3D)

    private:
        int m_nSpeed, m_nFallAcceleration;

    protected:
        static void _bind_methods();

    public:
        Player();
        ~Player();
        void _ready() override;
        void _process(double delta) override;
        void setSpeed(const int &p_speed);
        int getSpeed() const;
    };
}

#endif