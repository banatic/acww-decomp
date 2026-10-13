/* func_ov054_022621bc @ 0x022621bc, 0x4c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov054_02260474(void *);
extern int func_ov054_02262494(void *);
extern void func_ov054_02262528(void *, int);
extern int func_02019e00(void *);
extern int func_02019de8(void *);

int func_ov054_022621bc(void *p)
{
    func_ov054_02260474(p);
    if (func_ov054_02262494(p) != 0) {
        func_ov054_02262528(p, 3);
        return 1;
    }
    if (func_02019e00((char *) p + 0x564) == 3) {
        if (func_02019de8((char *) p + 0x564) != 0) {
            func_ov054_02262528(p, 2);
        }
    }
    return 1;
}
