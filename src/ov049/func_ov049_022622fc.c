/* func_ov049_022622fc @ 0x022622fc, 0x40 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);

struct UnkStruct_022622fc {
    char pad_00[0x564];
    char sub[0x413];
    char unk_977;
};

int func_ov049_022622fc(struct UnkStruct_022622fc *self)
{
    self->unk_977 = 0x32;
    func_02019d0c(self->sub, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
