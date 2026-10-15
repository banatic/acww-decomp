/* func_ov109_0229d5e0 @ 0x0229d5e0, 0x80 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *ptr, int a);
extern void func_ov109_0229c828(void *ptr);
extern int func_020ee45c(void *ptr);
extern int func_ov109_0229c2ac(void *ptr, int a);
extern void func_ov092_02299324(void *ptr, int a, int b);
extern void func_ov002_02207f04(void *ptr, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *ptr, int a, int b, int c);
extern void func_ov002_02208090(void *ptr, int a);
extern int func_ov002_02207f60(void *ptr);

void func_ov109_0229d5e0(char *this_)
{
    int ret;

    func_ov002_02207d24(this_ + 0x218c, 1);
    func_ov109_0229c828(this_);
    ret = func_020ee45c(this_);
    if (func_ov109_0229c2ac(this_, 0x40)) {
        func_ov092_02299324((void *) ret, 0x44, 1);
    } else {
        func_ov092_02299324((void *) ret, 0x40, 1);
    }
    func_ov002_02207f04(this_, 8, 0, 0, 48);
    func_ov002_02207e80(this_, 6, 0, -16);
    func_ov002_02208090(this_, 4);
    *(int *) (this_ + 0x29b8) = func_ov002_02207f60(this_);
}
