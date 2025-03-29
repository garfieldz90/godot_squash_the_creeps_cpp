#include "player.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getSpeed"), &Player::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "speed"), &Player::setSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "speed"), "setSpeed", "getSpeed");

}

Player::Player() {
    m_nSpeed = 0;
}

Player::~Player() {
    
}

void Player::_process(double delta) {
}

void Player::_ready() {
}

void Player::setSpeed(const int &p_speed) {
    m_nSpeed = p_speed;
}

int Player::getSpeed() const {
    return m_nSpeed;
}