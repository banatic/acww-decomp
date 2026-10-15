/* func_ov130_0229a32c @ 0x0229a32c, 0x4c bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_022999e4(void *unused0);
extern void func_020b9ccc(void *);
extern void func_ov130_0229a168(void *, unsigned char);

void func_ov130_0229a32c(void *self)
{
    unsigned char *p = (unsigned char *) self;
    func_ov130_022999e4(self);
    func_020b9ccc((void *) ((char *) self + 0x248));
    func_020b9ccc((void *) ((char *) self + 0x26c));
    if (p[3] != 0) {
        p[3] = p[3] - 1;
        if (p[3] == 0) {
            if (p[2] != 0) {
                p[3] = 1;
            } else {
                func_ov130_0229a168(self, p[4]);
            }
        }
    }
}
