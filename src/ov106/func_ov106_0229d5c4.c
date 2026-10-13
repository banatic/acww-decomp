/* func_ov106_0229d5c4 @ 0x0229d5c4, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *ptr, int value);
extern void func_ov002_02208098(void *ptr, int value);
extern void func_ov106_0229cd88(void *ptr, int value);
extern void func_ov106_0229ce38(void *ptr);
extern void func_ov094_022999c0(void);

void func_ov106_0229d5c4(void *p, int val)
{
    ((unsigned char *) p)[0xb7] = (unsigned char) val;
    func_ov002_02207d24((char *) p + 0x21b8, 1);
    func_ov106_0229cd88(p, val);
    if (((unsigned char *) p)[0xb4] == 1) {
        func_ov002_02208098(p, 4);
    }
    func_ov106_0229ce38(p);
    func_ov094_022999c0();
}
