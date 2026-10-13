/* func_ov141_0229a3c4 @ 0x0229a3c4, 0x64 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov141_02299f7c(void *p, int a);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern void func_ov141_02299f5c(void *p, int a);
extern void func_ov002_02208098(void *p, int a);

void func_ov141_0229a3c4(void *p1, int p2, int p3)
{
    int arg;
    if (func_ov141_02299f7c(p1, 0x10)) {
        arg = 0;
        func_ov002_0220a05c((char *) p1 + 0x0a38, p2, p3, 3, arg);
        func_ov141_02299f5c(p1, 0x10);
    } else {
        arg = 1;
        func_ov002_0220a05c((char *) p1 + 0x0a38, p2, p3, 3, arg);
    }
    *((unsigned char *) ((char *) p1 + 0x1a7e)) = *((unsigned char *) ((char *) p1 + 0x8d));
    func_ov002_02208098(p1, 2);
}
