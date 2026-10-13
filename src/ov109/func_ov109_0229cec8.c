/* func_ov109_0229cec8 @ 0x0229cec8, 0x50 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(char *a);
extern void func_ov002_022096d8(char *a, int b);
extern void func_ov002_02207d24(char *a, int b);
extern int func_0208e4bc(char *a);
extern void func_ov109_0229c678(char *a);
extern void func_ov002_02208098(char *a, int b);

void func_ov109_0229cec8(char *obj)
{
    if (func_ov002_0220909c(obj + 0x22d8)) {
        func_ov002_022096d8(obj + 0x22d8, 0);
        func_ov002_02207d24(obj + 0x218c, 1);
        if (func_0208e4bc(obj + 0x2274)) {
            func_ov109_0229c678(obj);
        }
        func_ov002_02208098(obj, 0xd);
    }
}
