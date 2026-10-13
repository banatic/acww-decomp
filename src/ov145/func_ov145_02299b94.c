/* func_ov145_02299b94 @ 0x02299b94, 0x3a bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200284c(int, int, int);
extern void func_ov145_02299b1c(void *);
extern void func_ov145_02299658(void *, int);

void func_ov145_02299b94(void *self, int value)
{
    int *p;
    int *q;
    int tmp;

    p = (int *) ((char *) self + 0x9c);
    *p = value;
    tmp = *p - 0x18;
    func_0200284c(4, 0, tmp);
    *(unsigned short *) ((char *) self + 0xb6) = (short) (value >> 4);
    func_ov145_02299b1c(self);
    func_ov145_02299658(self, 4);
}
