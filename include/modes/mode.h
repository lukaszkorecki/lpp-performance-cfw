#ifndef MODE_H
#define MODE_H

#include "app_defs.h"

#include "led/led.h"
#include "flash/flash.h"

#define mode_performance 0
#include "modes/normal/performance.h"

#define mode_ableton 1
#include "modes/normal/ableton.h"

#define mode_note 2
#include "modes/normal/note.h"

#define mode_drum 3
#include "modes/normal/drum.h"

#define mode_fader 4
#include "modes/normal/fader.h"

#define mode_programmer 5
#include "modes/normal/programmer.h"

#define mode_piano 6
#include "modes/normal/piano.h"

#define mode_mpc 7
#include "modes/normal/mpc.h"

#define mode_text 8
#include "modes/normal/text.h"

#define mode_normal 9

#define mode_scale_setup 9
#include "modes/special/scale.h"

#define mode_editor 10
#include "modes/special/editor.h"

#define mode_setup 11
#include "modes/special/setup.h"

#define mode_boot 12
#include "modes/special/boot.h"

#define mode_puyo 13
#include "modes/special/puyo.h"

#define mode_idle 14
#include "modes/special/idle.h"

void (*const mode_init[15])();
void (*const mode_timer_event[15])();
void (*const mode_surface_event[15])(u8 p, u8 v, u8 x, u8 y);
void (*const mode_midi_event[15])(u8 port, u8 t, u8 ch, u8 p, u8 v);
void (*const mode_aftertouch_event[15])(u8 v);
void (*const mode_poly_event[15])(u8 p, u8 v);

u8 mode, mode_default;

void mode_refresh();
void mode_update(u8 x);
void mode_default_update(u8 x);

#endif