/* func_ov102_0229c9b0 @ 0x0229c9b0, 0x4c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *p, int x);
extern void func_ov002_0220a374(void *p, int x);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov102_0229c9b0(int arg0, int arg1)
{
    unsigned char *p;

    p = (unsigned char *) arg0;
    func_ov002_02207d24(p + 0x218c, 1);
    p[0x25a7] = p[0x8d];
    p[0x25a6] = (unsigned char) arg1;
    func_ov002_0220a374(p + 0x2274, 6);
    func_ov002_02208098(p, 0xb);
}
