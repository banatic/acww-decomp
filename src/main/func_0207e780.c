/* func_0207e780 @ 0x0207e780, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0207e780 {
    unsigned short v;
} UnkStruct_0207e780;

extern UnkStruct_0207e780 *func_02099728(void *self);
extern UnkStruct_0207e780 *func_020996f8(void *self);
extern UnkStruct_0207e780 *func_020996e0(void *self);

static __inline unsigned int chk(UnkStruct_0207e780 *q, unsigned short lo, unsigned short hi)
{
    unsigned int r = 0;
    if (q->v >= lo && q->v <= hi) {
        r = 1;
    }
    return r;
}

int func_0207e780(void *self)
{
    unsigned int res = 1;
    unsigned int ok = 1;

    if (chk(func_02099728(self), 0x137c, 0x137c) == 0) {
        if (chk(func_020996f8(self), 0x1408, 0x1428) == 0) {
            ok = 0;
        }
    }
    if (ok == 0) {
        if (chk(func_020996e0(self), 0x1471, 0x1491) == 0) {
            res = 0;
        }
    }
    return res;
}
