#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/kinematic_collision3d.hpp>
#include <godot_cpp/classes/object.hpp>

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
    ClassDB::bind_method(D_METHOD("set_bounce_impulse", "bounce_impulse"), &Player::set_bounce_impulse);
    ClassDB::bind_method(D_METHOD("get_bounce_impulse"), &Player::get_bounce_impulse);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bounce_impulse"), "set_bounce_impulse", "get_bounce_impulse");
    ClassDB::bind_method(D_METHOD("die"), &Player::die);
    ClassDB::bind_method(D_METHOD("on_mob_detector_body_entered"), &Player::on_mob_detector_body_entered);
    ADD_SIGNAL(MethodInfo("hit"));
}

Player::Player()
{
    m_speed = 14;
    m_fall_acceleration = 75;
    m_jump_impulse = 20;
    m_bounce_impulse = 16;
    m_target_velocity = Vector3(0, 0, 0);
    m_input = Input::get_singleton();
}

Player::~Player()
{
}

void Player::_physics_process(double delta)
{
    Vector3 direction = Vector3(0, 0, 0);
    if (is_visible())
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
        m_pivot->look_at(m_position + direction), Vector3(0, 1, 0);
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

    for (int index = 0; index < get_slide_collision_count(); index++)
    {
        Ref<KinematicCollision3D> collision = get_slide_collision(index);
        Object *collider = collision->get_collider();
        if (collider == nullptr)
        {
            continue;
        }

        if (cast_to<Node>(collider)->is_in_group("mob"))
        {
            m_mob = cast_to<Mob>(collider);
            if (Vector3(0, 1, 0).dot(collision->get_normal()) > 0.1f)
            {
                m_mob->squash();
                m_target_velocity.y = m_bounce_impulse;
                break;
            }
        }
    }

    set_velocity(m_target_velocity);
    move_and_slide();
}

void Player::_ready()
{
    m_pivot = get_node<Node3D>("Pivot");
    m_mob_detector = get_node<Area3D>("MobDetector");
    m_mob_detector->connect("body_entered", Callable(this, "on_mob_detector_body_entered"), CONNECT_PERSIST);
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

void Player::set_bounce_impulse(const int &p_bounce_impulse)
{
    m_bounce_impulse = p_bounce_impulse;
}

int Player::get_bounce_impulse() const
{
    return m_bounce_impulse;
}

void Player::die()
{
    emit_signal("hit");
    queue_free();
}

void Player::on_mob_detector_body_entered(Mob *p_mob)
{
    die();
}