/* func_0208c734 @ 0x0208c734, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xC];
    u8 arr[9][0x14];
    u32 unk_C0;
    u8 pad_C4[0xC];
    u32 unk_D0;
} UnkStruct_0208c734;

extern int func_0208aef0(void *);
extern int func_0208aeec(void *);
extern int func_0208a1d0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208a198(void *, int);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);

void func_0208c734(UnkStruct_0208c734 *self)
{
    int first;
    int second;
    int i;
    int zero;
    int minus1;

    if (self->unk_C0 == 0) {
        return;
    }

    first = func_0208aef0(self);
    second = func_0208aeec(self);

    minus1 = -1;
    zero = 0;
    for (i = 0; i < 9; i++) {
        int result1;
        int result2;
        int result3;
        void *elem;
        int mode;

        elem = (u8 *) self + 0xC + i * 0x14;
        result1 = func_0208a1d0(elem);
        if (result1 != 0) {
            result2 = func_0208a1b0(elem, minus1);
            result3 = func_0208a198(elem, minus1);
            mode = (i == self->unk_D0) ? 6 : 5;
            func_02088df8(zero, result1, first + result2, second + result3, mode, minus1, 0x1000, 0x1000, zero, minus1, zero,
                          zero);
        }
    }
}
