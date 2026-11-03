/* field_actor_11: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220fd00 @ 0x0220fd00, 0x2 bytes, Thumb
 * func_ov003_0220fcb4 @ 0x0220fcb4, 0x4c bytes, Thumb
 * func_ov003_0220fc88 @ 0x0220fc88, 0x2c bytes, Thumb
 * func_ov003_0220fc34 @ 0x0220fc34, 0x54 bytes, Thumb
 * func_ov003_0220fbf8 @ 0x0220fbf8, 0x3c bytes, Thumb
 * func_ov003_0220fb94 @ 0x0220fb94, 0x64 bytes, Thumb
 * func_ov003_0220fb80 @ 0x0220fb80, 0x14 bytes, Thumb
 */

typedef struct UnkStruct_0220fc34 {
    char pad_first[0x2d0];
    char unk_2D0[8];
    unsigned int unk_2D8;
    char pad_2DC[0x7f0 - 0x2d8 - 4];
    unsigned int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    unsigned int unk_7FC;
} UnkStruct_0220fc34;

typedef struct Sub0x2d0 {
    int pad_00;
} Sub0x2d0;

typedef struct {
    char pad_00[0x2d0];
    Sub0x2d0 sub_2d0;
    char pad1[0x7f0 - (0x2d0 + sizeof(Sub0x2d0))];
    int unk_7F0;
    char pad_7F4[0x7fc - (0x7f0 + 4)];
    int unk_7FC;
} UnkStruct_0220fbf8;

typedef struct {
    int pad_00;
    int b;
    int c;
    int d;
} Sub_t;

typedef struct {
    char pad_00[0x7d4];
    Sub_t sub;
    char pad1[0x800 - 0x7d4 - sizeof(Sub_t)];
    int unk_800;
} Obj_t;

struct UnkStruct_0220fb80 {
    int a;
    int b;
    unsigned char c;
    unsigned char d;
};

extern void func_02010f5c(char *self);
extern int func_02056f28(char *ptr, int val);
extern int func_020912d4(int a, char *b, char *c, int d);
extern int func_020113e0(void *dst, short src);
extern void func_020110a0(void *object, short *values);
extern int func_02056f94(void *);
extern unsigned int func_02008258(void *, unsigned int);
extern int func_0200d4e8(void *, int, int, int);
extern int func_ov003_0220d268(void *);
extern int func_0200f434(void *, int *);
extern void func_02010d64(void *);
extern int func_02073908(int, int);
extern int data_020ccf94;

void func_ov003_0220fd00(void *receiver, int event) {}

void func_ov003_0220fcb4(char *self)
{
    func_02010f5c(self);
    if (*(int *) (self + 0x704) == 0x65) {
        if (func_02056f28(self + 0x2d0, 3) != 0 || func_02056f28(self + 0x2d0, 13) != 0) {
            func_020912d4(0x23, self + 0x5c, self + 0x8e, 0);
        }
    }
}

void func_ov003_0220fc88(void *self)
{
    short tmp;
    short *p = &tmp;
    *p = *(short *) ((char *) self + 0x8e);
    func_020113e0(p, *(short *) ((char *) self + 0x7d4));
    func_020110a0((void *) (self), (short *) (p));
}

void func_ov003_0220fc34(UnkStruct_0220fc34 *self)
{
    if (func_02056f94(self->unk_2D0)) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 3, 1, -1);
    }
    if (((self->unk_2D8 << 4) >> 16) >= 22) {
        func_ov003_0220d268(self);
    }
}

void func_ov003_0220fbf8(UnkStruct_0220fbf8 *s)
{
    s->unk_7FC = (int) func_02008258((void *) s, s->unk_7F0);
    if (func_02056f94((void *) (&s->sub_2d0)) != 0) {
        func_0200d4e8((void *) s, 3, 1, -1);
    }
}

void func_ov003_0220fb94(Obj_t *self)
{
    Sub_t *sub = &self->sub;
    int arr[3];
    int arg0, arg1;

    func_ov003_0220fcb4((char *) self);

    arr[0] = sub->b;
    arr[1] = sub->c;
    arr[2] = sub->d;
    if (func_0200f434(self, arr)) {
        func_ov003_0220fc88(self);
    }

    func_02010d64(self);

    arg0 = data_020ccf94;
    arg1 = self->unk_800;
    if (func_02073908(arg0, arg1)) {
        func_ov003_0220fc34((UnkStruct_0220fc34 *) self);
    } else {
        func_ov003_0220fbf8((UnkStruct_0220fbf8 *) self);
    }
}

void func_ov003_0220fb80(struct UnkStruct_0220fb80 *s, int a, int b, unsigned char c, unsigned char d)
{
    s->a = a;
    s->b = b;
    s->c = c;
    s->d = d;
}
