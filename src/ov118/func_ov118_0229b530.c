/* func_ov118_0229b530 @ 0x0229b530, 0x34 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229a460(void *p, int flag);
extern void func_ov118_0229b4d8(void *p, void *q);

void func_ov118_0229b530(void *p)
{
    if (func_ov118_0229a460(p, 1)) {
        func_ov118_0229b4d8(p, (char *) p + 0x4797);
    } else {
        func_ov118_0229b4d8(p, (char *) p + 0x478a);
    }
}
