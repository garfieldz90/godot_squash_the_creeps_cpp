#include "main.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/path_follow3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void Main::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_mob_scene", "mob_scene"), &Main::set_mob_scene);
    ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mob_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_mob_scene", "get_mob_scene");
    ClassDB::bind_method(D_METHOD("on_mob_timer_timeout"), &Main::on_mob_timer_timeout);
    ClassDB::bind_method(D_METHOD("on_mob_squash"), &Main::on_mob_squash);
    ClassDB::bind_method(D_METHOD("on_player_hit"), &Main::on_player_hit);
}

void Main::_ready()
{
    m_mob_timer = get_node<Timer>("MobTimer");
    m_mob_timer->connect("timeout", Callable(this, "on_mob_timer_timeout"), CONNECT_PERSIST);
    m_player = get_node<Player>("Player");
    m_player->connect("hit", Callable(this, "on_player_hit"), CONNECT_PERSIST);
    m_ui = get_node<UserInterface>("UserInterface");
    m_player->connect("squash_creep", Callable(this, "on_mob_squash"), CONNECT_PERSIST);
    m_retry = get_node<ColorRect>(NodePath("UserInterface/Retry"));
    m_retry->hide();
}

void Main::set_mob_scene(const Ref<PackedScene> &p_mob_scene)
{
    m_mob_scene = p_mob_scene;
}

Ref<PackedScene> Main::get_mob_scene() const
{
    return m_mob_scene;
}

void Main::on_mob_timer_timeout()
{
    // if (!m_player->is_queued_for_deletion())
    // {
        RandomNumberGenerator *rnd = memnew(RandomNumberGenerator);
        Mob *mob = cast_to<Mob>(m_mob_scene->instantiate());
        PathFollow3D *mob_spawn_location = cast_to<PathFollow3D>(get_node_or_null("SpawnPath/SpawnLocation"));
        mob_spawn_location->set_progress_ratio(rnd->randf());
        Vector3 player_position = m_player->get_position();
        mob->initialize(mob_spawn_location->get_position(), player_position);
        add_child(mob);
        memdelete(rnd);
        rnd = nullptr;
    // }
}

void Main::on_player_hit()
{
    m_mob_timer->stop();
    m_retry->show();
}

void Main::on_mob_squash()
{
    m_ui->add_score();
}

void Main::_unhandled_input(const Ref<InputEvent> &p_event)
{
    if (p_event->is_action_pressed("ui_accept") && m_retry->is_visible())
    {
        get_tree()->reload_current_scene();
    }
}