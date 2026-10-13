/* func_ov105_0229d03c @ 0x0229d03c, 0x58 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d03c;
extern int func_ov105_0229cff4(struct UnkStruct_0229d03c *self);
extern int func_ov105_0229cfe4(struct UnkStruct_0229d03c *self);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern int func_ov105_0229d750(struct UnkStruct_0229d03c *self, unsigned char b);
extern void func_ov002_0220a374(void *ptr, int v);
extern void func_ov105_0229cd9c(struct UnkStruct_0229d03c *self);

struct UnkStruct_0229d03c {
    char pad_00[0x2ba];
    unsigned char byte_at_2ba;
    char pad_2BB[0x24a4 - 0x2bb];
    char field_at_24a4;
};

void func_ov105_0229d03c(struct UnkStruct_0229d03c *self)
{
    int a;
    int b;

    a = func_ov105_0229cff4(self);
    b = func_ov105_0229cfe4(self);
    func_ov002_0220a0b4(&self->field_at_24a4, a, b);
    if (func_ov105_0229d750(self, self->byte_at_2ba) != 0) {
        func_ov002_0220a374(&self->field_at_24a4, 7);
    } else {
        func_ov002_0220a374(&self->field_at_24a4, 1);
    }
    func_ov105_0229cd9c(self);
}
