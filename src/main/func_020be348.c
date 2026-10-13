/* func_020be348 @ 0x020be348, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020bf064(void *);

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u8 unk_08;
    u8 unk_09;
} Elem;

void func_020be348(u8 *base)
{
    Elem *end = (Elem *) (base + 0x1b6c);
    Elem *p = (Elem *) (base + 0x1b30);

    while (p < end) {
        u32 f0 = p->unk_00;
        u8 f9 = p->unk_09;

        if (f9 != 0) {
            if (f0 == 0x34) {
                p->unk_09 = 0;
            } else if (p->unk_08 == 0) {
                func_020bf064(end);
            }
        }
        p++;
    }
}
