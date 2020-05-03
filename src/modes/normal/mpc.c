#include "modes/normal/mpc.h"

#define mpc_nav_r 0
#define mpc_nav_g 0
#define mpc_nav_b 63

#define mpc_color_pressed_r 0
#define mpc_color_pressed_g 63
#define mpc_color_pressed_b 0

/*
	Banks:

	BD FH
	AC EG
*/

const u8 mpc_map[128] = {    // Banks are flipped vertically - TODO Fill this
	// Bank A
	// C#2, C2, F#2, A#5, E#2(???), D2, A#2, G#2, C3, B2, A2, G2, C#3, G3, D#3, F3

	// Bank B
	// ...
};

u8 mpc_page = 0;

void draw_page() {
	rgb_led(93 + mpc_page, mpc_nav_r, mpc_nav_g, mpc_nav_b);
	rgb_led(94 - mpc_page, mpc_nav_r >> 3, mpc_nav_g >> 3, mpc_nav_b >> 3);
}

s8 mpc_press(u8 x, u8 y, u8 p, u8 v) {
	rgb_led(p, mpc_color_pressed_r * v / 63, mpc_color_pressed_g * v / 63, mpc_color_pressed_b * v / 63);
	return mpc_map[(x - 1) * 4 + (y - 1) % 4 + (y >= 5)? 32 : 0 + mpc_page * 64];
}

void mpc_init() {
	draw_page();

	rgb_led(99, mode_mpc_r, mode_mpc_g, mode_mpc_b); // MPC mode LED

	active_port = USBSTANDALONE;
}

void mpc_timer_event() {}

void mpc_surface_event(u8 p, u8 v, u8 x, u8 y) {
	if (p == 0) { // Enter Setup mode
		if (v != 0) mode_update(mode_setup);
	
	} else if (x == 9 && 3 <= y && y <= 4) { // Navigation buttons
		if (v != 0) {
			mpc_page = y - 3;
			draw_page();
		}
	
	} else if (1 <= x && x <= 8 && 1 <= y && y <= 8) { // Main grid
		send_midi(USBSTANDALONE, (v == 0)? 0x85 : 0x95, mpc_press(x, y, p, v), v);
	}
}

void mpc_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}

void mpc_aftertouch_event(u8 v) {
	aftertouch_send(USBSTANDALONE, 0xD5, v);
}

void mpc_poly_event(u8 p, u8 v) {
	send_midi(USBSTANDALONE, 0xA5, mpc_press(p / 10, p % 10, p, v), v);
}