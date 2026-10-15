/* func_ov107_0229d634 @ 0x0229d634, 0x50 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(void *p);
extern void func_ov002_022096d8(void *p, int x);
extern int func_ov002_02207d24(void *p, int x);
extern int func_0208e4bc(void *p);
extern void func_ov107_0229cce8(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov107_0229d634(char *param)
{
    if (func_ov002_0220909c(param + 0x2318) == 0) {
        return;
    }
    func_ov002_022096d8(param + 0x2318, 0);
    func_ov002_02207d24(param + 0x21cc, 1);
    if (func_0208e4bc(param + 0x22b4)) {
        func_ov107_0229cce8(param);
    }
    func_ov002_02208098((void *) (param), 0xd);
}
