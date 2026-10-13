/* func_ov106_0229dd64 @ 0x0229dd64, 0x50 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(void *p);
extern void func_ov002_022096d8(char *p, int v);
extern void func_ov002_02207d24(char *p, int v);
extern int func_0208e4bc(void *p);
extern void func_ov106_0229ca5c(void *p);
extern void func_ov002_02208098(void *p, int v);

void func_ov106_0229dd64(void *s)
{
    unsigned int self = (unsigned int) s;

    if (func_ov002_0220909c((void *) (self + 0x2304)) != 0) {
        func_ov002_022096d8((char *) (self + 0x2304), 0);
        func_ov002_02207d24((char *) (self + 0x21b8), 1);
        if (func_0208e4bc((void *) (self + 0x22a0)) != 0) {
            func_ov106_0229ca5c((void *) self);
        }
        func_ov002_02208098((void *) self, 0x18);
    }
}
