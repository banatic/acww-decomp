/* func_ov121_0229b2a4 @ 0x0229b2a4, 0x78 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov121_02299a3c(void *p, int n);
extern int func_ov121_02299a5c(void *p, int n);
extern void func_ov121_0229a450(void *p);
extern int func_ov121_0229ac00(void *p);
extern void func_0200467c(int cmd);

void func_ov121_0229b2a4(char *p)
{
    if (func_ov002_02209f9c(p + 0x3a8) != 0) {
        return;
    }
    func_ov121_02299a3c(p, 4);
    if (func_ov121_02299a5c(p, 0x80) != 0) {
        func_ov121_0229a450(p);
        func_ov002_02208098(p, 4);
        func_ov121_02299a3c(p, 0x80);
        func_0200467c(0xe);
    } else {
        unsigned char *src = (unsigned char *) p + 0xb1;
        unsigned char *dst = (unsigned char *) p + 0xaf;
        *dst = *src;
        func_ov121_02299a3c(p, 4);
        if (func_ov121_0229ac00(p) == 0) {
            func_ov121_0229a450(p);
            func_ov002_02208098(p, 4);
        }
    }
}
