/* func_ov003_022152f8 @ 0x022152f8, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *, int b, int c, unsigned short d);
extern void func_0205eae0(void *, int, int, int);
extern int func_0200f328(void *, int);

void func_ov003_022152f8(void *self, void *message, int previous)
{
    unsigned int *src;

    func_020109a0(self, 0x58, 3, 0);
    func_0205eae0((char *) self + 0x5a0, 0x1b, 3, 1);
    func_0200f328(self, 0x84c);
    func_0200f328(self, 0x84e);

    src = (unsigned int *) ((char *) self + 0x5d0);
    *(unsigned int *) ((char *) self + 0x8c4) = src[0];
    *(unsigned int *) ((char *) self + 0x8c8) = src[1];
    *(unsigned int *) ((char *) self + 0x8cc) = src[2];
}
