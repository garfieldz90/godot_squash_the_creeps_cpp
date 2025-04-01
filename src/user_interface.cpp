#include "user_interface.h"

using namespace godot;

void UserInterface::_bind_methods() {
    
}

void UserInterface::_ready()
{
    m_score_label = get_node<Label>("ScoreLabel");
    m_score_label->set_text("Score: hao");
}