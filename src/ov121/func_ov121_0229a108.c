/* func_ov121_0229a108 @ 0x0229a108, 0x28 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_02299a3c(void *p, int n);
extern void func_ov002_0220a374(void *p, int n);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov121_0229a108(void *p)
{
    func_ov002_0220a374((char *) p + 0x3a8, 5);
    func_ov121_02299a3c(p, 0x80);
    func_ov002_02208098(p, 0xb);
}
