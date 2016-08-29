#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#define UNUSED(x) (void)(x)

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_COMMAND_PORT 0x64

void keyboardinterrupthandler(struct cpu_stack_state state);
void install_keyboard_interrupt();
void remove_keyboard_interrupt();

#endif
