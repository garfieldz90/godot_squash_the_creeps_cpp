#include "mob.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

using namespace godot;

void Mob::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_mini_speed", "mini_speed"), &Mob::set_min_speed);
    ClassDB::bind_method(D_METHOD("get_mini_speed"), &Mob::get_min_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "mini_speed"), "set_mini_speed", "get_mini_speed");
    ClassDB::bind_method(D_METHOD("set_max_speed", "max_speed"), &Mob::set_max_speed);
    ClassDB::bind_method(D_METHOD("get_max_speed"), &Mob::get_max_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_speed"), "set_max_speed", "get_max_speed");
    ClassDB::bind_method(D_METHOD("squash"), &Mob::squash);
    ADD_SIGNAL(MethodInfo("squash"));
}

Mob::Mob()
{
    m_min_speed = 10;
    m_max_speed = 18;
}
Mob::~Mob()
{
}

void Mob::_physics_process(double delta)
{
    move_and_slide();
}

int Mob::get_min_speed() const
{
    return m_min_speed;
}

void Mob::set_min_speed(const int &p_mini_speed)
{
    m_min_speed = p_mini_speed;
}

int Mob::get_max_speed() const
{
    return m_max_speed;
}

void Mob::set_max_speed(const int &p_max_speed)
{
    m_max_speed = p_max_speed;
}

void Mob::initialize(Vector3 p_start_position, Vector3 p_player_position)
{
    RandomNumberGenerator *rnd = memnew(RandomNumberGenerator);
    look_at_from_position(p_start_position, p_player_position, Vector3(0, 1, 0));
    rotate_y(rnd->randf_range(-M_PI / 4, M_PI / 4));
    int random_speed = rnd->randi_range(m_min_speed, m_max_speed);
    Vector3 velocity = Vector3(0, 0, -1) * random_speed;
    velocity = velocity.rotated(Vector3(0, 1, 0), get_rotation().y);
    set_velocity(velocity);
    memdelete(rnd);
    rnd = nullptr;
    // m_animation_player->set_speed_scale(4.0f);
}

void Mob::on_visibility_notifier_screen_exited()
{
    queue_free();
}

void Mob::squash()
{
    emit_signal("squash");
    queue_free();
}

void Mob::_ready()
{
    m_animation_player = get_node<AnimationPlayer>("AnimationPlayer");
}