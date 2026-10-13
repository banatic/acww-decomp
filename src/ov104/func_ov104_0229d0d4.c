/* func_ov104_0229d0d4 @ 0x0229d0d4, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *ptr, int arg);
extern void func_ov002_0220a374(void *ptr, int arg);
extern void func_ov002_02208098(void *ptr, int arg);

void func_ov104_0229d0d4(void *p, unsigned char val)
{
    func_ov002_02207d24((char *) p + 0x23b8, 1);
    *((unsigned char *) ((char *) p + 0xbb)) = *((unsigned char *) ((char *) p + 0x8d));
    *((unsigned char *) ((char *) p + 0xba)) = val;
    func_ov002_0220a374((char *) p + 0x24a0, 6);
    func_ov002_02208098(p, 0x13);
}
