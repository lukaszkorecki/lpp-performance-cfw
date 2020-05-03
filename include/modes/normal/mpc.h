#ifndef MPC_H
#define MPC_H

#include "app.h"
#include "modes/mode.h"
#include "send/send.h"

#include "aftertouch/aftertouch.h"

#define mode_mpc_r 0
#define mode_mpc_g 0
#define mode_mpc_b 63

void mpc_init();
void mpc_timer_event();
void mpc_surface_event(u8 p, u8 v, u8 x, u8 y);
void mpc_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void mpc_aftertouch_event(u8 v);
void mpc_poly_event(u8 p, u8 v);

#endif