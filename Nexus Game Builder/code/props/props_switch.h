#ifndef _PROPS_SWITCH_H
#define _PROPS_SWITCH_H

// enable all switches with the given id
void switch_enable_by_id(var num);

// disable all switches with the given id
void switch_disable_by_id(var num);

// function used to trigger props with the same id
void switch_trigger_props();

// switch's event function
void switch_event_function();

#endif