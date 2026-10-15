/* func_ov104_0229e0cc @ 0x0229e0cc, 0x28 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229e0cc {
    char pad_00[0x24a0];
    char sub[1];
};

extern int func_0208e484(void *ptr);
extern void func_ov104_0229d198(struct UnkStruct_0229e0cc *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov104_0229e0cc(struct UnkStruct_0229e0cc *self)
{
    if (func_0208e484(self->sub)) {
        func_ov104_0229d198(self);
        func_ov002_02208098((void *) (self), 7);
    }
}
