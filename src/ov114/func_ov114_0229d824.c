/* func_ov114_0229d824 @ 0x0229d824, 0x58 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov114_0229d168(void *arg0);
extern void func_ov002_0220a544(void *);
extern void func_ov114_0229c720(void *);
extern int func_ov114_0229c1a0(void *, int);
extern int func_020b9b6c(void *, void *, unsigned char, int);
extern void func_ov114_0229c180(void *, int);

void func_ov114_0229d824(void *self)
{
    func_ov114_0229d168((void *) self);
    func_ov002_0220a544((char *) self + 0x121c);
    func_ov114_0229c720(self);
    if (func_ov114_0229c1a0(self, 1) != 0) {
        if (func_020b9b6c((char *) self + 0x924, (char *) self + 0x968, *(unsigned char *) ((char *) self + 0x12b1), 4) != 0) {
            func_ov114_0229c180(self, 1);
        }
    }
}
