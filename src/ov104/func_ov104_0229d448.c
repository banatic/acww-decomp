/* func_ov104_0229d448 @ 0x0229d448, 0x3c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_02066830(void *dst, void *src);
extern void func_ov104_0229d4a8(void *self, void *arg);
extern void func_ov104_0229d938(void *self, void *arg, void *dst);

void func_ov104_0229d448(void *self, void *arg)
{
    if (*(unsigned char *) ((char *) self + 0xb4) == 1) {
        func_02066830((char *) self + 0x1c0, (char *) self + 0xc0);
        func_ov104_0229d4a8(self, arg);
        func_ov104_0229d938(self, arg, (char *) self + 0x1c0);
    }
}
