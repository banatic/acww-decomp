/* func_02055954 @ 0x02055954, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x10];
    u32 unk_10;
    u8 unk_14[0x0D];
    u8 unk_21;
    u8 pad_22[0x0E];
    u8 unk_30;
} UnkStruct_02055954;

extern void func_02055b50(int, void *);
extern int func_020b9eec(void *, int, int);
extern int func_020561cc(int, int);

int func_02055954(UnkStruct_02055954 *self, int arg2, int arg3, int arg4)
{
    u8 state = self->unk_30;
    if (state == 3) {
        return state;
    }
    if (state == 0) {
        func_02055b50(arg3, (void *) arg2);
        func_020b9eec(self->unk_14, arg2, 1);
        self->unk_30 = 1;
        return self->unk_30;
    }
    if (state == 1) {
        unsigned int flag = (self->unk_21 == 2) ? 1 : 0;
        if (flag != 0) {
            self->unk_30 = 2;
        } else {
            return state;
        }
    }
    if (self->unk_30 == 2) {
        self->unk_10 = func_020561cc(arg2, arg4);
        self->unk_30 = 3;
    }
    return self->unk_30;
}
