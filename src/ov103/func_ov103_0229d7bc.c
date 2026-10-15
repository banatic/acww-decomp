/* func_ov103_0229d7bc @ 0x0229d7bc, 0x70 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;

extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov002_02207ce4(void *p, int n);
extern void func_ov002_02207d00(void *p);
extern int func_ov103_0229c2f4(void *p, int n);
extern int func_ov103_0229cb1c(void *receiver);
extern int func_ov103_0229cb08(void *p, int n);
extern void func_ov103_0229ced0(void *p, unsigned char c);
extern void func_ov103_0229c444(void *p, unsigned char c);

void func_ov103_0229d7bc(void *arg)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(arg, 0);
        func_ov002_02207ce4((char *) arg + 0x218c, 0x3c);
    } else {
        if (func_ov103_0229c2f4(arg, 4) != 0) {
            if (func_ov103_0229cb1c(arg) != 0) {
                func_ov103_0229ced0(arg, ((unsigned char *) arg)[0x2da1]);
                return;
            }
            if (func_ov103_0229cb08(arg, 9) != 0) {
                func_ov103_0229c444(arg, ((unsigned char *) arg)[0x2da1]);
                return;
            }
        }
        func_ov002_02207d00((char *) arg + 0x218c);
    }
}
