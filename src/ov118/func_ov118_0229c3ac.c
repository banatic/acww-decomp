/* func_ov118_0229c3ac @ 0x0229c3ac, 0x2c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229be54(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov118_0229a460(void *, int);
extern void func_ov118_0229c378(void *);

void func_ov118_0229c3ac(void *arg)
{
    func_ov118_0229be54(arg);
    func_ov002_02208090(arg, 3);
    if (func_ov118_0229a460(arg, 0x2000) == 0) {
        func_ov118_0229c378(arg);
    }
}
