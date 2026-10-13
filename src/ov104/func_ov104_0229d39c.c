/* func_ov104_0229d39c @ 0x0229d39c, 0x10 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

struct FuncOv104 {
    char pad_00[0xb8];
    unsigned char b8;
};

extern void func_ov104_0229d858(struct FuncOv104 *self, unsigned char b);

void func_ov104_0229d39c(struct FuncOv104 *self)
{
    func_ov104_0229d858(self, self->b8);
}
