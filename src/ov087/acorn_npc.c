/* acorn_npc: 4 functions, module ov087
 * mwccarm 1.2/base -O4,s
 * func_ov087_02278a98 @ 0x02278a98, 0x20 bytes, Thumb
 * func_ov087_02278a54 @ 0x02278a54, 0x44 bytes, Thumb
 * func_ov087_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov087_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

typedef struct UnkStruct_02278a54 {
    void *vtable;
    int pad_04;
    void (*func)(void **);
} UnkStruct_02278a54;

typedef struct UnkStruct_02278a54_2 {
    char pad_00[0x658];
    UnkStruct_02278a54 *inner;
} UnkStruct_02278a54_2;

struct UnkStruct_02278a28 {
    char pad_00;
};

struct UnkStruct_02278a28_2 {
    void *unk_00;
    char pad_04[0x654];
    struct UnkStruct_02278a28 sub;
};

extern int func_02014868(int);
extern int func_0201c2a4(void *, int);
extern void func_02016108(void *, int);
extern void func_ov087_022790ac(void *, int);
extern void *func_ov087_02278fdc(struct UnkStruct_02278a28 *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_ov087_022794ec[];

int func_ov087_02278a98(int param)
{
    int result = 0;
    if (func_02014868(param + 0x618) == 0) {
        result = 1;
    }
    return result;
}

void func_ov087_02278a54(UnkStruct_02278a54_2 *self, int mode)
{
    switch (mode) {
        case 0:
            self->inner->func((void **) &self->inner);
            {
                int ret = func_0201c2a4(self, 4);
                func_02016108(&self->inner, ret);
            }
            func_ov087_022790ac(self, 1);
            break;
        case 8:
            func_ov087_022790ac(self, 0);
            break;
    }
}

struct UnkStruct_02278a28_2 *func_ov087_02278a28(struct UnkStruct_02278a28_2 *self)
{
    self->unk_00 = ((char *) data_ov087_022794ec);
    func_ov087_02278fdc(&self->sub);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

void *func_ov087_02278a00(void *self)
{
    *(void **) self = (void *) data_ov087_022794ec;
    func_ov087_02278fdc((struct UnkStruct_02278a28 *) ((char *) self + 0x658));
    func_0202ee5c(self);
    return self;
}
