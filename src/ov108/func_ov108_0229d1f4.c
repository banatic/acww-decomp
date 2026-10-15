/* func_ov108_0229d1f4 @ 0x0229d1f4, 0x54 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov108_0229c940(void *p);
extern int func_ov108_0229ccc0(void *p, void *argument1);
extern void func_ov108_0229c9d8(void *p);
extern void func_ov108_0229ce00(void *p, int a, int b);

void func_ov108_0229d1f4(void *self)
{
    unsigned char b1;
    unsigned char b0;

    if (func_ov002_02209f9c((char *) self + 0x2498) == 0) {
        b1 = ((unsigned char *) self)[0x2b2];
        b0 = ((unsigned char *) self)[0x2b0];

        if (b0 == b1) {
            func_ov108_0229ccc0(self, (void *) b1);
            func_ov108_0229c9d8(self);
            func_ov002_02208098((void *) (self), 6);
        } else {
            func_ov108_0229ce00(self, b1, 4);
        }
    } else {
        func_ov108_0229c940(self);
        return;
    }
}
