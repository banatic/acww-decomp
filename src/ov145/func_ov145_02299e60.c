/* func_ov145_02299e60 @ 0x02299e60, 0x30 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(void *a, int b, int c, int d, int e);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov145_02299e60(void *self, int p1, int p2)
{
    func_ov002_0220a05c((unsigned char *) self + 0xc8, p1, p2, 3, 1);
    *((unsigned char *) self + 0xc3) = *((unsigned char *) self + 0x8d);
    func_ov002_02208098((void *) (self), 6);
}
