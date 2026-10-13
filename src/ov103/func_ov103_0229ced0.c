/* func_ov103_0229ced0 @ 0x0229ced0, 0x48 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(char *addr, int arg);
extern void func_ov002_02208098(void *p, int arg);
extern void func_ov103_0229c910(void *p, int val);
extern void func_ov103_0229c9c8(void *p);

void func_ov103_0229ced0(void *p, int val)
{
    ((unsigned char *) p)[0x2da3] = val;
    func_ov002_02207d24((char *) p + 0x218c, 1);
    func_ov103_0229c910(p, val);
    if (((unsigned char *) p)[0x2da0] == 1) {
        func_ov002_02208098(p, 2);
    }
    func_ov103_0229c9c8(p);
}
