/* func_0202df18 @ 0x0202df18, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0202df18_2 {
    u8 pad_00[0x28];
    u16 id;
} UnkStruct_0202df18_2;
typedef struct UnkStruct_0202df18 {
    u8 pad_00[0x148];
    int unk_148;
} UnkStruct_0202df18;

extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_0202dfd0(UnkStruct_0202df18_2 *, UnkStruct_0202df18 *, u16 *);
extern int func_020b9d3c(UnkStruct_0202df18_2 *, int, int, int, int, int);
extern int data_020d8d2c;

static __inline int same_(UnkStruct_0202df18_2 *a, u16 *c)
{
    int t;
    if (func_0204bcdc(c) != 0) {
        t = func_0204bc64(c);
        if (t == func_0204bc64(&a->id)) {
            return 1;
        }
        return 0;
    }
    if (*c == a->id) {
        return 1;
    }
    return 0;
}

int func_0202df18(UnkStruct_0202df18_2 *a, UnkStruct_0202df18 *b, u16 *c)
{
    int ret;
    int r;
    unsigned int ok;

    ret = 0;
    if (same_(a, c) != 0) {
        ok = 0;
        if (*c >= 0x12a8 && *c <= 0x12af) {
            ok = 1;
        }
        if (ok == 0) {
            goto end;
        }
        ok = 0;
        if (a->id >= 0x12a8 && a->id <= 0x12af) {
            ok = 1;
        }
        if (ok == 0) {
            goto end;
        }
    }
    r = func_0202dfd0(a, b, c);
    if (r != 0) {
        ret = func_020b9d3c(a, b->unk_148, data_020d8d2c, r, 0, 0);
        a->id = *c;
    }
end:
    return ret;
}
