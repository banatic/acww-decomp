/* func_ov134_0229a1f0 @ 0x0229a1f0, 0x5a bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229a44c(void *p, int x, int y);
extern int func_ov134_02299b98(void *p, int x, int y);
extern void func_ov002_0220a574(void *p);

typedef struct {
    char pad_00[0x60];
    int unk_60;
} UnkStruct_0229a1f0;

int func_ov134_0229a1f0(UnkStruct_0229a1f0 *self, int x, int y)
{
    int ret;
    int v;

    ret = func_ov134_0229a44c(self, x, y);
    switch (ret) {
        case 1:
            return 0;
        case 2:
            return 4;
        default:
            break;
    }

    if (func_ov134_02299b98(self, x, y) != 0) {
        return 3;
    }

    if (y >= 32 && y <= 168) {
        v = self->unk_60;
        if (x > v + 24) {
            goto fail;
        }
        if (x < v) {
            goto fail;
        }
        func_ov002_0220a574((char *) self + 0x18);
        return 2;
    }

fail:
    return 1;
}
