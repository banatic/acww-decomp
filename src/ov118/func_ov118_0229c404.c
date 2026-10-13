/* func_ov118_0229c404 @ 0x0229c404, 0x34 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229bf3c(void *);
extern void func_ov118_0229be8c(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov118_0229a460(void *, int);
extern void func_ov118_0229c3d8(void *);

void func_ov118_0229c404(void *param)
{
    func_ov118_0229bf3c(param);
    func_ov118_0229be8c(param);
    func_ov002_02208090(param, 1);
    if (func_ov118_0229a460(param, 0x2000) == 0) {
        func_ov118_0229c3d8(param);
    }
}
