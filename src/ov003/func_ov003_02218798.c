/* func_ov003_02218798 @ 0x02218798, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *);
extern int func_02056f28(void *, int);
extern int func_0200f328(void *, int);

void func_ov003_02218798(void *p)
{
    func_02010f5c(p);
    if (func_02056f28((char *) p + 0x2d0, 8) == 0 && func_02056f28((char *) p + 0x2d0, 0xd) == 0) {
        return;
    }
    func_0200f328(p, 0x7d5);
}
