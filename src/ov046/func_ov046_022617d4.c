/* func_ov046_022617d4 @ 0x022617d4, 0x4c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8e];
    unsigned char unk_8E[0x478 - 0x8e];
    unsigned char unk_478[0x740 - 0x478];
    int unk_740;
} SelfType;

extern int func_ov046_02260474(SelfType *self);
extern int func_020912d4(int a, void *b, void *c, int _x);
extern void func_02091278(int a, void *b, void *c);

int func_ov046_022617d4(SelfType *self)
{
    if (func_ov046_02260474(self)) {
        return 1;
    }
    if (self->unk_740 == -1) {
        self->unk_740 = func_020912d4(0x3c, &self->unk_478, &self->unk_8E, 0);
    } else {
        func_02091278(self->unk_740, &self->unk_478, &self->unk_8E);
    }
    return 1;
}