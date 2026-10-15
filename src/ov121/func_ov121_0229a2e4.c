/* func_ov121_0229a2e4 @ 0x0229a2e4, 0x74 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov121_02299a5c(void *p, int arg);
extern int func_ov121_0229a3a8(void *p);
extern int func_ov121_0229a37c(void *p);
extern void func_ov121_02299a3c(void *p, int arg);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov121_0229a2e4(void *p)
{
    if (func_ov121_02299a5c(p, 0x10)) {
        int a = func_ov121_0229a3a8(p);
        int b = func_ov121_0229a37c(p);
        func_ov002_0220a0b4((char *) p + 0x3a8, a, b);
        func_ov121_02299a3c(p, 0x10);
    } else {
        int a = func_ov121_0229a3a8(p);
        int b = func_ov121_0229a37c(p);
        func_ov002_0220a05c((char *) p + 0x3a8, a, b, 3, 1);
        *((unsigned char *) p + 0xb4) = *((unsigned char *) p + 0x8d);
        func_ov002_02208098(p, 6);
    }
}
