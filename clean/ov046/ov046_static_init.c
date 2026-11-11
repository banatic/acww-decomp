/* Overlay 46's static initializer, run when the overlay is loaded: the six colors its source
 * file defines for itself, then the table of its character's states (astro.h) filled from the
 * overlay's constants. */
#include "astro.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* A color of four 5-bit components (the fourth always 31). */
typedef struct AstroInitColor {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} AstroInitColor;

static void astro_init_color(AstroInitColor *color, u8 c0, u8 c1, u8 c2, u8 c3)
{
    color->c0 = c0;
    color->c1 = c1;
    color->c2 = c2;
    color->c3 = c3;
}

/* Red, blue, yellow, green, cyan and gray. */
extern AstroInitColor data_ov046_02262444, data_ov046_02262448, data_ov046_02262460, data_ov046_02262450, data_ov046_02262440,
    data_ov046_0226244c;

/* The constants of the states' table: each state's entry, then its run; ASTRO_TALKED has no
 * entry. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov046_02261ea8, data_ov046_02261fe0, data_ov046_02261fd8, data_ov046_02261fd0,
    data_ov046_02261fc8, data_ov046_02261fc0, data_ov046_02261fb8, data_ov046_02261fb0, data_ov046_02261fa8;

/* __sinit_ov046_02261cac: the colors, then the states' table in order. */
void AstroInit_Tables(void)
{
    static const MemberPointer *const states[2 * ASTRO_STATE_COUNT] = {
        &data_ov046_02261ea8, &data_ov046_02261fe0, /* ASTRO_IDLE: Astro_EnterIdle, Astro_UpdateIdle */
        &data_ov046_02261fd8, &data_ov046_02261fd0, /* ASTRO_TURN_BACK */
        &data_ov046_02261fc8, &data_ov046_02261fc0, /* ASTRO_ASLEEP */
        &data_ov046_02261fb8, &data_ov046_02261fb0, /* ASTRO_TALK */
        &__ptmf_null,         &data_ov046_02261fa8, /* ASTRO_TALKED: no entry, Astro_UpdateTalked */
    };

    astro_init_color(&data_ov046_02262444, 31, 20, 20, 31);
    astro_init_color(&data_ov046_02262448, 20, 20, 31, 31);
    astro_init_color(&data_ov046_02262460, 31, 31, 20, 31);
    astro_init_color(&data_ov046_02262450, 20, 31, 20, 31);
    astro_init_color(&data_ov046_02262440, 20, 31, 31, 31);
    astro_init_color(&data_ov046_0226244c, 20, 24, 24, 31);
    for (int i = 0; i < ASTRO_STATE_COUNT; i++) {
        data_ov046_0226248c[i].enter = *states[2 * i];
        data_ov046_0226248c[i].run = *states[2 * i + 1];
    }
}
CLEAN_AS(__sinit_ov046_02261cac, AstroInit_Tables)
