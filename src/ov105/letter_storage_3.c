/* letter_storage_3: 3 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229d03c @ 0x0229d03c, 0x58 bytes, Thumb
 * func_ov105_0229cff4 @ 0x0229cff4, 0x48 bytes, Thumb
 * func_ov105_0229cfe4 @ 0x0229cfe4, 0x10 bytes, Thumb
 */

struct UnkStruct_0229d03c;

struct UnkStruct_0229d03c {
    char pad_00[0x2ba];
    unsigned char byte_at_2ba;
    char pad_2BB[0x24a4 - 0x2bb];
    char field_at_24a4;
};

struct UnkStruct_0229cfe4 {
    unsigned char pad_00[0x2ba];
    unsigned char byte;
};

extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern int func_ov105_0229d750(struct UnkStruct_0229d03c *self, unsigned char b);
extern void func_ov002_0220a374(void *ptr, int v);
extern void func_ov105_0229cd9c(struct UnkStruct_0229d03c *self);
extern int func_ov105_0229d530(void *p, unsigned char c);
extern int func_ov105_0229c340(void *p, int val);
extern int func_ov105_0229d4c4(struct UnkStruct_0229cfe4 *self, unsigned char byte);

int func_ov105_0229cff4(unsigned char *p);
int func_ov105_0229cfe4(struct UnkStruct_0229cfe4 *self);

void func_ov105_0229d03c(struct UnkStruct_0229d03c *self)
{
    int a;
    int b;

    a = func_ov105_0229cff4((unsigned char *) self);
    b = func_ov105_0229cfe4((struct UnkStruct_0229cfe4 *) self);
    func_ov002_0220a0b4(&self->field_at_24a4, a, b);
    if (func_ov105_0229d750(self, self->byte_at_2ba) != 0) {
        func_ov002_0220a374(&self->field_at_24a4, 7);
    } else {
        func_ov002_0220a374(&self->field_at_24a4, 1);
    }
    func_ov105_0229cd9c(self);
}

int func_ov105_0229cff4(unsigned char *p)
{
    int r = func_ov105_0229d530(p, p[0x2ba]);
    if (func_ov105_0229c340(p, 0x20) != 0) {
        r += 0x100;
    } else if (func_ov105_0229c340(p, 0x10) != 0) {
        r -= 0x100;
    }
    return r + 8;
}

int func_ov105_0229cfe4(struct UnkStruct_0229cfe4 *self)
{
    return func_ov105_0229d4c4(self, self->byte);
}
