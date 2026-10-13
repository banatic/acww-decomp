/* func_ov095_0229b3a0 @ 0x0229b3a0, 0x4a bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct State {
    u16 arr[6];
    int count;
};

extern void func_ov095_0229b3ec(struct State *self, int count, int idx);
extern u16 func_ov095_0229b704(struct State *self, struct State *other);

int func_ov095_0229b3a0(struct State *self, u16 *out, int idx)
{
    int cnt;
    u16 result;

    cnt = self->count;
    if (cnt <= 1) {
        func_ov095_0229b3ec(self, cnt, idx);
        return 0;
    } else {
        if (idx == 0) {
            return 0;
        }
        self->count = cnt - 1;
        self->arr[self->count] = 0;
        if (self->count <= 1) {
            result = self->arr[0];
        } else {
            result = func_ov095_0229b704(self, self);
        }
        out[idx - 1] = result;
        return 1;
    }
}
