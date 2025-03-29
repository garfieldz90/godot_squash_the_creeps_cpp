#ifndef MAIN_H
#define MAIN_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/godot.hpp>

namespace godot {
    
    class Main : public Node {
        GDCLASS(Main, Node)

        protected:
        static void _bind_methods() ;


    };
}

#endif