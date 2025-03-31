#include "player.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Player::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "speed"), "set_speed", "get_speed");
    ClassDB::bind_method(D_METHOD("get_fall_acceleration"), &Player::get_fall_acceleration);
    ClassDB::bind_method(D_METHOD("set_fall_acceleration", "fall_acceleration"), &Player::set_fall_acceleration);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "fall_acceleration"), "set_fall_acceleration", "get_fall_acceleration");
    ClassDB::bind_method(D_METHOD("set_jump_impulse", "jump_impulse"), &Player::set_jump_impulse);
    ClassDB::bind_method(D_METHOD("get_jump_impulse"), &Player::get_jump_impulse);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "jump_impulse"), "set_jump_impulse", "get_jump_impulse");
}

Player::Player()
{
    m_speed = 14;
    m_fall_acceleration = 75;
    m_jump_impulse = 20;
    m_target_velocity = Vector3(0, 0, 0);
    m_input = Input::get_singleton();
}

Player::~Player()
{
}

void Player::_physics_process(double delta)
{
    Vector3 direction = Vector3(0, 0, 0);
    m_position = get_position();

    if (m_input->is_action_pressed("move_right"))
    {
        direction.x += 1.0f;
    }
    if (m_input->is_action_pressed("move_left"))
    {
        direction.x -= 1.0f;
    }
    if (m_input->is_action_pressed("move_back"))
    {
        direction.z += 1.0f;
    }
    if (m_input->is_action_pressed("move_forward"))
    {
        direction.z -= 1.0f;
    }

    if (direction != Vector3(0, 0, 0))
    {
        direction = direction.normalized();
        m_pivot->set_basis(Basis::looking_at(direction));
    }

    m_target_velocity.x = direction.x * m_speed;
    m_target_velocity.z = direction.z * m_speed;

    if (!is_on_floor())
    {
        m_target_velocity.y = m_target_velocity.y - (m_fall_acceleration * delta);
    }

    if (is_on_floor() && m_input->is_action_just_pressed("jump"))
    {
        m_target_velocity.y = m_jump_impulse;
    }

    set_velocity(m_target_velocity);
    move_and_slide();
}

void Player::_ready()
{
    m_pivot = get_node<Node3D>("Pivot");
}

void Player::set_speed(const int &p_speed)
{
    m_speed = p_speed;
}

int Player::get_speed() const
{
    return m_speed;
}

void Player::set_fall_acceleration(const int &p_fall_acceleration)
{
    m_fall_acceleration = p_fall_acceleration;
}

int Player::get_fall_acceleration() const
{
    return m_fall_acceleration;
}

void Player::set_jump_impulse(const int &p_jump_impulse)
{
    m_jump_impulse = p_jump_impulse;
}

int Player::get_jump_impulse() const
{
    return m_jump_impulse;
}