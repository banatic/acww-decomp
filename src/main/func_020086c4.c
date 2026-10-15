/* func_020086c4 @ 0x020086c4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02008748(void *p, unsigned short v);
extern void func_0200850c(void *dst, void *src, int c);
extern void func_020109a0(void *p, int a, int b, unsigned short c);

void func_020086c4(void *self, void *message, int previous)
{
    unsigned int tmp[4];
    func_02008748((char *) self + 0x8f0, *(unsigned short *) ((char *) self + 0x820));
    func_0200850c(tmp, self, 0);
    *(unsigned int *) ((char *) self + 0x824) = tmp[0];
    *(unsigned int *) ((char *) self + 0x828) = tmp[1];
    *(unsigned int *) ((char *) self + 0x82c) = tmp[2];
    *(unsigned int *) ((char *) self + 0x830) = 0x1000;
    *(unsigned int *) ((char *) self + 0x834) = 0x1000;
    *(unsigned int *) ((char *) self + 0x838) = 0x1000;
    func_020109a0(self, 0x7e, 3, 0);
}
