/* func_ov003_022145b0 @ 0x022145b0, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *ptr);
extern void func_02010f5c(void *ptr);
extern void func_0200f328(void *ptr, int off);

void func_ov003_022145b0(char *p)
{
    int r5;

    r5 = (func_02056f94((char *) p + 0x2d0) != 0);
    func_02010f5c(p);
    if (r5 == 0) {
        if (func_02056f94((char *) p + 0x2d0) != 0) {
            func_0200f328(p, 0x848);
        }
    }
}
