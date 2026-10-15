/* func_ov068_02275994 @ 0x02275994, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020044c0(char *p, int a, int b, int c);
extern void func_020b220c(void);
extern int func_ov068_02275c78(char *p, int a);

void func_ov068_02275994(char *self)
{
    if (*(int *) ((char *) *(int *) (self + 0x8dc) + 4) != 0) {
        return;
    }
    func_020044c0(self + 0x514, 0x4cb, 0x7f, 0);
    func_020b220c();
    func_ov068_02275c78(self, 3);
}
