/* func_ov118_0229b3d8 @ 0x0229b3d8, 0x64 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b3d8 {
    char pad_00[0xaa];
    unsigned char byte_a9;
    char pad_AB[0x723 - 0xaa];
    char sub;
};

extern void func_ov118_0229b6e0(struct UnkStruct_0229b3d8 *);
extern void func_ov118_0229b530(struct UnkStruct_0229b3d8 *);
extern int func_ov118_0229b374(struct UnkStruct_0229b3d8 *);
extern void func_ov118_0229a440(struct UnkStruct_0229b3d8 *, int);
extern void func_ov118_0229a450(struct UnkStruct_0229b3d8 *, int);
extern void func_0206fdd4(char *, int, int, int, int, int);
extern void func_ov118_0229af64(struct UnkStruct_0229b3d8 *, unsigned char);

void func_ov118_0229b3d8(struct UnkStruct_0229b3d8 *self)
{
    int result;
    int flag;

    func_ov118_0229b6e0(self);
    func_ov118_0229b530(self);
    result = func_ov118_0229b374(self);

    if (result == 0) {
        func_ov118_0229a440(self, 8);
        flag = 4;
    } else {
        func_ov118_0229a450(self, 8);
        flag = 3;
    }

    func_0206fdd4(&self->sub, 0x1d, 0xa, 0x1d, 0x15, flag);
    func_ov118_0229a450(self, 0x20);
    func_ov118_0229af64(self, self->byte_a9);
}
