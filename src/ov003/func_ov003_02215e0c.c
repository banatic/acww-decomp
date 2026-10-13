/* func_ov003_02215e0c @ 0x02215e0c, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *);
extern int func_02056f28(void *, int);
extern void func_0200f328(void *, int);

void func_ov003_02215e0c(void *p)
{
    func_02010f5c(p);
    if (func_02056f28((char *) p + 0x2d0, 0x11) != 0) {
        func_0200f328(p, 0x849);
    }
}
