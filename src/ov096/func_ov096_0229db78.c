/* func_ov096_0229db78 @ 0x0229db78, 0x48 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229c2dc(void *p0, int p1);
extern int func_ov002_02207d24(void *p0, int p1);
extern void func_ov002_0220a374(void *p0, int p1);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov096_0229db78(void *p0, int p1)
{
    func_ov002_02207d24((char *) p0 + 0x2418, 1);
    *((char *) p0 + 0xb7) = (char) p1;
    func_ov002_0220a374((char *) p0 + 0x2500, 5);
    func_ov002_02208098((void *) (p0), 0x14);
    func_ov096_0229c2dc(p0, 0x2000);
}
