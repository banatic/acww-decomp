/* mail_particles: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a7a04 @ 0x020a7a04, 0x10 bytes, Thumb
 * func_020a79f8 @ 0x020a79f8, 0xc bytes, Thumb
 * func_020a79e0 @ 0x020a79e0, 0x18 bytes, Thumb
 * func_020a7994 @ 0x020a7994, 0x4c bytes, Thumb
 */

struct UnkStruct_020a7a04 {
    char *data;
    int unk_04;
    int unk_08;
};

struct Object {
    int *vtable;
};

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a7994;

extern char data_020e3d14[];
extern void func_020edb3c(struct Object *self);

void func_020a7a04(struct UnkStruct_020a7a04 *obj)
{
    obj->data = data_020e3d14;
    obj->unk_04 = 0;
    obj->unk_08 = 0;
}

void func_020a79f8(unsigned int *ptr)
{
    *ptr = (unsigned int) ((unsigned int *) data_020e3d14);
}

struct Object *func_020a79e0(struct Object *self)
{
    self->vtable = ((int *) data_020e3d14);
    func_020edb3c(self);
    return self;
}

void func_020a7994(UnkStruct_020a7994 *obj, char *str)
{
    int i = 0;
    obj->unk_04 = 0;
    while (str[i] != 0 || str[i + 1] != 0) {
        int val = ((str[i + 1] << 8) & 0x0000ff00) | (str[i] & 0xff);
        if (val >= 0x0000ac00 && val <= 0x0000d7a3) {
            obj->unk_04 = val;
        }
        i += 2;
    }
}
