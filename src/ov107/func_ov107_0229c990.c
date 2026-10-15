/* func_ov107_0229c990 @ 0x0229c990, 0x54 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208d30(void *addr, int a);
extern int func_ov002_02207d24(void *addr, int a);
extern int func_ov107_0229d388(void *obj, int val);
extern void func_ov107_0229c9e4(void *obj);
extern void func_ov107_0229ce90(void *obj);
extern void func_ov107_0229cba4(void *obj, int flag);

void func_ov107_0229c990(void *obj, int val, int flag)
{
    *(unsigned char *) ((char *) obj + 0xb9) = val;
    func_ov002_02208d30((char *) obj + 0x2700, 4);
    if (func_ov107_0229d388(obj, val)) {
        func_ov107_0229c9e4(obj);
        func_ov107_0229ce90(obj);
        if (flag == 0) {
            func_ov002_02207d24((char *) obj + 0x21cc, 1);
        }
        func_ov107_0229cba4(obj, flag);
    }
}
