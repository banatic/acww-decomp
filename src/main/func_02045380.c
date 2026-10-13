/* func_02045380 @ 0x02045380, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00;
    u8 sel : 5;
    u8 hi3 : 3;
    u8 pad[2];
    u16 unk_04;
} UnkStruct_02045380;

typedef struct {
    u8 pad[6];
    u16 w[3];
} UnkStruct_02045380_2;

extern int func_0204b910(volatile u16 *h);
extern void func_0204558c(UnkStruct_02045380_2 *self, void *c, int id);
extern int func_02044540(void);
extern void func_02045440(UnkStruct_02045380_2 *self, UnkStruct_02045380 *e, void *c);

int func_02045380(UnkStruct_02045380_2 *self, UnkStruct_02045380 *e, void *c)
{
    int result;
    volatile u16 h;
    int i;
    unsigned int ok;
    unsigned int hi, lo;

    result = 0;
    if (e->sel == 1 || e->sel == 6) {
        h = 0xfff1;
        for (i = 0; i < 3; i++) {
            self->w[i] = 0xffff;
        }
        h = e->unk_04;
        ok = 0;
        hi = h;
        lo = h;
        if (lo >= 0x2f && hi <= 0x56) {
            ok = 1;
        }
        if (ok != 0 || (hi >= 0xc8 && hi <= 0xcf) || (hi >= 0x57 && hi <= 0x5b)) {
            if (func_0204b910(&h) == 0) {
                goto end;
            }
            func_0204558c(self, c, e->unk_04);
            result = 1;
        } else if (hi == 0x67 || hi == 0x6b) {
            if (func_02044540() == 0) {
                goto end;
            }
            func_02045440(self, e, c);
            result = 1;
        } else if ((hi >= 0x66 && hi <= 0x68) || (hi >= 0x6a && hi <= 0x6c)) {
            func_02045440(self, e, c);
            result = 1;
        }
    }
end:
    return result;
}
