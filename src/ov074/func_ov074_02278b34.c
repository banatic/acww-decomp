/* func_ov074_02278b34 @ 0x02278b34, 0x50 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

struct Vtbl {
    void (*unk_00)(void *);
    void (*unk_04)(void *);
    void (*unk_08)(void *);
};

struct UnkStruct_02278b34 {
    struct Vtbl *vtbl;
};

struct UnkStruct_02278b34_2 {
    unsigned char pad_00[0x658];
    struct UnkStruct_02278b34 obj;
};

extern void func_ov074_02279778(struct UnkStruct_02278b34_2 *self, int mode);
extern int func_0201c2a4(struct UnkStruct_02278b34_2 *self, int val);
extern void func_02016108(struct UnkStruct_02278b34 *obj, int val);

void func_ov074_02278b34(struct UnkStruct_02278b34_2 *self, int mode)
{
    switch (mode) {
        case 0:
            func_ov074_02279778(self, 0);
            break;
        case 3:
            self->obj.vtbl->unk_08(&self->obj);
            func_02016108(&self->obj, func_0201c2a4(self, 4));
            func_ov074_02279778(self, 4);
            break;
        case 8:
            func_ov074_02279778(self, 2);
            break;
    }
}
