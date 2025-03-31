#include "main.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/path_follow3d.hpp>

using namespace godot;

void Main::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_mob_scene", "mob_scene"), &Main::set_mob_scene);
    ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mob_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_mob_scene", "get_mob_scene");
    ClassDB::bind_method(D_METHOD("on_mob_timer_timeout"), &Main::on_mob_timer_timeout);
}

void Main::_ready()
{
    m_mob_timer = get_node<Timer>("MobTimer");
    m_mob_timer->connect("timeout", Callable(this, "on_mob_timer_timeout"), CONNECT_PERSIST);
    m_player = get_node<Player>("Player");
    m_player->connect("hit", Callable(this, "hit"), CONNECT_PERSIST);
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
    RandomNumberGenerator *rnd = memnew(RandomNumberGenerator);
    Mob *mob = cast_to<Mob>(m_mob_scene->instantiate());
    PathFollow3D *mob_spawn_location = cast_to<PathFollow3D>(get_node_or_null("SpawnPath/SpawnLocation"));
    mob_spawn_location->set_progress_ratio(rnd->randf());
    Vector3 player_position = m_player->get_position();
    mob->initialize(mob_spawn_location->get_position(), player_position);
    add_child(mob);
    memdelete(rnd);
    rnd = nullptr;
}

void Main::on_player_hit()
{
    m_mob_timer->stop();
}