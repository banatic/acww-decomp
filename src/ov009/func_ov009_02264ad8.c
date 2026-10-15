/* func_ov009_02264ad8 @ 0x02264ad8, 0x8c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02264ad8 {
    int unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14, unk_18, unk_1C;
};

extern int func_ov009_022648e4(char *, int, int, int);
extern struct UnkStruct_02264ad8 *func_ov009_02264884(char *);
extern int func_02055f2c(void *, int, int);
extern int func_ov003_022203c8(void);
extern int func_ov003_0221fe2c(void *argument0);
extern int NNS_G3dBindMdlPltt(int, int);
extern int NNS_G3dBindMdlTex(int, int);

int func_ov009_02264ad8(char *self, int a, int b, int c)
{
    struct UnkStruct_02264ad8 *e;
    int p;

    if (*(int *) (self + 0x284) != 0 || *(int *) (self + 0x198) != 0) {
        return 1;
    }
    func_ov009_022648e4(self, a, b, c);
    e = func_ov009_02264884(self);
    if (e == 0 || e->unk_00 == 0) {
        goto ret1b;
    }
    p = e->unk_00;
    if (func_02055f2c(self + 0x13c, p, 0) == 0) {
        goto ret0;
    }

    NNS_G3dBindMdlPltt(e->unk_00, func_ov003_0221fe2c((void *) func_ov003_022203c8()));
    if (e->unk_14 != 0) {
        NNS_G3dBindMdlTex(e->unk_00, e->unk_14);
    }
    if (e->unk_18 != 0) {
        NNS_G3dBindMdlTex(e->unk_00, e->unk_18);
        NNS_G3dBindMdlPltt(e->unk_00, e->unk_18);
    }
    return 1;
ret0:
    return 0;
ret1b:
    return 1;
}
