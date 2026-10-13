/* func_ov068_0226c820 @ 0x0226c820, 0x90 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3_0226c8;

extern int func_0203dff0(void *);
extern int func_020eaa2c(void *, void *);
extern int func_02096190(int);
extern int func_0203dfac(void);
extern void func_020eaca0(void *, void *, void *);
extern int FX_MulFunc(int, int);

extern unsigned char data_021fbee8[];

int func_ov068_0226c820(void *self, void *arg1, Vec3_0226c8 *arg2)
{
    int t4;
    int t6;
    Vec3_0226c8 v1;
    Vec3_0226c8 v2;
    int diff1;
    int diff2;

    if (func_0203dff0(self) == 0) {
        goto fail;
    }
    if (func_020eaa2c(arg2, (void *) data_021fbee8) == 0) {
        goto fail;
    }

    t4 = func_02096190(4);
    t6 = func_0203dfac();
    if (t4 == 0) {
        goto fail;
    }
    if (t6 == 0) {
        goto fail;
    }

    func_020eaca0(&v1, (char *) t4 + 0x5c, arg1);
    func_020eaca0(&v2, (char *) t6 + 0x5c, arg1);

    diff1 = FX_MulFunc(arg2->x, v1.z) - FX_MulFunc(arg2->z, v1.x);
    diff2 = FX_MulFunc(arg2->x, v2.z) - FX_MulFunc(arg2->z, v2.x);

    if (FX_MulFunc(diff1, diff2) > 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
