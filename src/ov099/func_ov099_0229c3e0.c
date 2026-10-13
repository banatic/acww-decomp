/* func_ov099_0229c3e0 @ 0x0229c3e0, 0x54 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208d30(void *ptr, int flag);
extern void func_ov002_02207d24(void *ptr, int flag);
extern int func_ov099_0229cf30(unsigned char *ptr, unsigned char val);
extern void func_ov099_0229c434(unsigned char *ptr);
extern void func_ov099_0229c754(unsigned char *ptr);
extern void func_ov099_0229c4a0(unsigned char *ptr);

void func_ov099_0229c3e0(unsigned char *ptr, unsigned char val)
{
    ptr[0x2908] = val;
    func_ov002_02208d30(ptr + 0x26c0, 1);
    if (func_ov099_0229cf30(ptr, val)) {
        func_ov099_0229c434(ptr);
        func_ov099_0229c754(ptr);
        func_ov002_02207d24(ptr + 0x218c, 1);
        func_ov099_0229c4a0(ptr);
    }
}
