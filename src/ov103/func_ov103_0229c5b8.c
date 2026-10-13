/* func_ov103_0229c5b8 @ 0x0229c5b8, 0x4c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int n);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov002_02208098(void *p, int n);

void func_ov103_0229c5b8(void *obj, unsigned char value)
{
    func_ov002_02207d24((char *) obj + 0x218c, 1);
    *((unsigned char *) obj + 0x2da7) = *((unsigned char *) obj + 0x8d);
    *((unsigned char *) obj + 0x2da6) = value;
    func_ov002_0220a374((char *) obj + 0x2274, 6);
    func_ov002_02208098(obj, 0x11);
}
