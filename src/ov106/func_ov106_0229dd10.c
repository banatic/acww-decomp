/* func_ov106_0229dd10 @ 0x0229dd10, 0x34 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *p, int x);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0208e5cc(void *p);

typedef struct {
    char pad_00[0xbb];
    unsigned char byte_at_bb;
    char pad_BC[0x21e4];
    char field_at_22a0;
    char pad_22A1[0x457];
    char field_at_26f8;
} St;

void func_ov106_0229dd10(St *self)
{
    if (func_ov002_0220b8ac(&self->field_at_26f8, 1)) {
        func_ov002_02208098((void *) (self), self->byte_at_bb);
        func_0208e5cc(&self->field_at_22a0);
    }
}
