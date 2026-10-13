/* func_ov106_0229ef30 @ 0x0229ef30, 0x5c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f58c(unsigned char *);
extern int func_0206f56c(int);
extern void func_ov106_0229cc50(unsigned char *);
extern void func_ov106_0229c378(unsigned char *);
extern void func_ov002_02207d24(unsigned char *, int);
extern void func_ov106_0229e9a4(unsigned char *);
extern void func_ov106_0229ef8c(unsigned char *);
extern void func_ov106_0229e99c(unsigned char *);

int func_ov106_0229ef30(unsigned char *self)
{
    if (func_0206f56c(func_0206f58c(self)) != 0) {
        if (self[0x8d] == 0 || self[0x8d] == 1 || self[0x8d] == 7) {
            func_ov106_0229cc50(self);
            func_ov106_0229c378(self);
            func_ov002_02207d24(self + 0x21b8, 0);
            return 1;
        }
    }
    func_ov106_0229e9a4(self);
    func_ov106_0229ef8c(self);
    func_ov106_0229e99c(self);
    return 1;
}
