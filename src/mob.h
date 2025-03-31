#ifndef MOB_H
#define MOB_H

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot
{
    class Mob : public CharacterBody3D
    {
        GDCLASS(Mob, CharacterBody3D)

    private:
        int m_min_speed, m_max_speed;

    protected:
        static void _bind_methods();

    public:
        Mob();
        ~Mob();
        void _physics_process(double delta) override;
        void set_min_speed(const int &p_min_speed);
        int get_min_speed() const;
        void set_max_speed(const int &p_max_speed);
        int get_max_speed() const;
        void initialize(Vector3 p_start_position, Vector3 p_player_position);
        void on_visibility_notifier_screen_exited();
        void squash();
    };
}

#endif