/* func_ov104_0229e714 @ 0x0229e714, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229e714 {
    char pad_00[0xb5];
    unsigned char b5;
    char pad_B6[0x09];
    unsigned char bf;
};

extern int func_ov002_02207cc0(int object);
extern void func_ov104_0229cf14(struct UnkStruct_0229e714 *self, unsigned char val, int flag);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov104_0229e714(struct UnkStruct_0229e714 *self)
{
    if (func_ov002_02207cc0((int) ((char *) self + 0x23b8)) == 0) {
        return;
    }
    if (self->bf != 0) {
        self->bf--;
    } else {
        func_ov104_0229cf14(self, self->b5, 1);
        func_ov002_02208098((void *) (self), 2);
    }
}
