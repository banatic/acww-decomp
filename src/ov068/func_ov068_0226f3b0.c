/* func_ov068_0226f3b0 @ 0x0226f3b0, 0x94 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x26c - 0x68];
    int unk_26C;
    int unk_270;
    char pad_274[0x388 - 0x274];
    char unk_388[32];
} UnkStruct_0226f3b0;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0226f3b0_2;

extern void func_020eaca0(UnkStruct_0226f3b0_2 *, char *, int *);
extern int func_020ea838(UnkStruct_0226f3b0_2 *);
extern void func_020eabc8(UnkStruct_0226f3b0_2 *, int);
extern int func_020ea990(int *, char *);
extern int _s32_div_f(int, int);
extern int func_ov003_0221abf8(void *object, int flag);
extern void func_ov068_0226fd80(UnkStruct_0226f3b0 *);

void func_ov068_0226f3b0(UnkStruct_0226f3b0 *self)
{
    UnkStruct_0226f3b0_2 local;
    int r4;
    int v;

    self->unk_270 = self->unk_26C;

    func_020eaca0(&local, self->unk_388, &self->unk_5C);
    func_020ea838(&local);
    func_020eabc8(&local, 0x80);

    self->unk_5C += local.a;
    self->unk_64 += local.c;

    func_ov068_0226fd80(self);

    r4 = func_020ea990(&self->unk_5C, self->unk_388);

    v = 0;
    if (r4 < 0x1000) {
        v = -_s32_div_f(0x1000 - r4, 5);
    }

    if (self->unk_60 < v) {
        self->unk_60 = v;
        if (r4 < 0x333) {
            func_ov003_0221abf8(self, 1);
        }
    }
}
