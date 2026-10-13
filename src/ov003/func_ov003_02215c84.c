/* func_ov003_02215c84 @ 0x02215c84, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void);
extern int func_02056f28(void *ptr, int size);
extern void func_0200f328(void *ptr, int value);

void func_ov003_02215c84(void *self)
{
    void *r4 = self;
    func_02010f5c();
    if (func_02056f28((char *) r4 + 0x2d0, 0xc) != 0) {
        func_0200f328(r4, 0x84a);
    }
}
