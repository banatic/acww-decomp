/* func_ov146_0229a534 @ 0x0229a534, 0x44 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a314(void *);
extern int func_ov146_0229a5e8(void *);
extern int func_ov146_0229a59c(void *);
extern void func_ov146_0229a4d0(void *, int, int);

void func_ov146_0229a534(void *self)
{
    if (*(unsigned char *) ((char *) self + 0xb2) == 2) {
        func_ov002_0220a2b4((char *) self + 0x15cc);
    } else {
        func_ov002_0220a314((char *) self + 0x15cc);
    }
    func_ov146_0229a4d0(self, func_ov146_0229a5e8(self), func_ov146_0229a59c(self));
}
