#include "user_interface.h"
#include <godot_cpp/core/class_db.hpp>


using namespace godot;

void UserInterface::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("add_score"), &UserInterface::add_score);
}

void UserInterface::_ready()
{
    m_score_label = get_node<Label>("ScoreLabel");
    m_score_label->set_text("Score: " + String::num(m_score, 0));
}

void UserInterface::add_score()
{
    m_score += 1;
    m_score_label->set_text("Score: " + String::num(m_score, 0));
}

UserInterface::UserInterface()
{
    m_score = 0;
}

UserInterface::~UserInterface()
{
}