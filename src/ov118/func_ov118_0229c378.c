/* func_ov118_0229c378 @ 0x0229c378, 0x34 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229be04(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov118_0229a460(void *, unsigned int);
extern void func_ov118_0229c35c(void *);
extern void func_ov118_0229a440(void *, unsigned int);

void func_ov118_0229c378(void *r0)
{
    func_ov118_0229be04(r0);
    func_ov002_02208090(r0, 4);
    if (func_ov118_0229a460(r0, 0x2000) == 0) {
        func_ov118_0229c35c(r0);
        func_ov118_0229a440(r0, 0x2000);
    }
}
