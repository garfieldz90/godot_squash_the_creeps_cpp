#include "player.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Player::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("getSpeed"), &Player::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "speed"), &Player::setSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "speed"), "setSpeed", "getSpeed");
    ClassDB::bind_method(D_METHOD("getFallAcceleration"), &Player::getFallAcceleration);
    ClassDB::bind_method(D_METHOD("setFallAcceleration", "fall_acceleration"), &Player::setFallAcceleration);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "FallAcceleration"), "setFallAcceleration", "getFallAcceleration");
}

Player::Player()
{
    m_nSpeed = 0;
    m_nFallAcceleration = 0;
    m_ntargetVelocity = Vector3(0, 0, 0);
    m_pInput = Input::get_singleton();
}

Player::~Player()
{
}

void Player::_physics_process(double delta)
{
    Vector3 direction = Vector3(0, 0, 0);
    m_nPosition = get_position();

    if (m_pInput->is_action_pressed("move_right"))
    {
        direction.x += 1.0f;
    }
    if (m_pInput->is_action_pressed("move_left"))
    {
        direction.x -= 1.0f;
    }
    if (m_pInput->is_action_pressed("move_back"))
    {
        direction.z += 1.0f;
    }
    if (m_pInput->is_action_pressed("move_forward"))
    {
        direction.z -= 1.0f;
    }

    if (direction != Vector3(0, 0, 0))
    {
        direction = direction.normalized();
        m_pPivot->set_basis(Basis::looking_at(direction));
    }

    m_ntargetVelocity.x = direction.x * m_nSpeed;
    m_ntargetVelocity.z = direction.z * m_nSpeed;

    if (!is_on_floor())
    {
        m_ntargetVelocity.y = m_ntargetVelocity.y - (m_nFallAcceleration * delta);
    }

    set_velocity(m_ntargetVelocity);
    move_and_slide();
}

void Player::_ready()
{
    m_pPivot = get_node<Node3D>("Pivot");
}

void Player::setSpeed(const int &p_speed)
{
    m_nSpeed = p_speed;
}

int Player::getSpeed() const
{
    return m_nSpeed;
}

void Player::setFallAcceleration(const int &p_fallAcceleration)
{
    m_nFallAcceleration = p_fallAcceleration;
}

int Player::getFallAcceleration() const
{
    return m_nFallAcceleration;
}