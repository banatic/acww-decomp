/* func_ov106_0229c958 @ 0x0229c958, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int a);
extern void func_ov002_0220a374(void *p, int a);
extern void func_ov002_02208098(void *p, int a);

void func_ov106_0229c958(void *self, unsigned char val)
{
    unsigned char tmp;

    func_ov002_02207d24((char *) self + 0x21b8, 1);
    tmp = *(unsigned char *) ((char *) self + 0x8d);
    *(unsigned char *) ((char *) self + 0xbb) = tmp;
    *(unsigned char *) ((char *) self + 0xba) = val;
    func_ov002_0220a374((char *) self + 0x22a0, 6);
    func_ov002_02208098(self, 0x13);
}
