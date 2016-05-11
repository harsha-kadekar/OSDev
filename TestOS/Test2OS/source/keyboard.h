#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "idt.h"
#include "io.h"

#define KEYBOARD_DATA_PORT 0x60

void keyboard_handler(struct cpu_stack_state state);
void keyboard_install();

#endif
