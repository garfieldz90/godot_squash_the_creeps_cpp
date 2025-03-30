#include "player.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getSpeed"), &Player::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "speed"), &Player::setSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "speed"), "setSpeed", "getSpeed");
    ClassDB::bind_method(D_METHOD("getFallAcceleration"), &Player::getFallAcceleration);
    ClassDB::bind_method(D_METHOD("setFallAcceleration", "fall_acceleration"), &Player::setFallAcceleration);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "FallAcceleration"), "setFallAcceleration", "getFallAcceleration");
}

Player::Player() {
    m_nSpeed = 0;
    m_nFallAcceleration = 0;
    m_nVelocity = Vector3(0, 0, 0);
    m_pInput = Input::get_singleton();
}

Player::~Player() {
    
}

void Player::_process(double delta) {
    Vector3 direction = Vector3(0, 0, 0);
    if (m_pInput->is_action_pressed("move_right"))
    {
        direction.x += 1;
    }
}

void Player::_ready() {
}

void Player::setSpeed(const int &p_speed) {
    m_nSpeed = p_speed;
}

int Player::getSpeed() const {
    return m_nSpeed;
}

void Player::setFallAcceleration(const int &p_fallAcceleration) {
    m_nFallAcceleration = p_fallAcceleration;
}

int Player::getFallAcceleration() const {
    return m_nFallAcceleration;
}