/* func_ov009_02263658 @ 0x02263658, 0x3c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096168(void *);
extern int func_ov009_02264c90(void *);
extern void func_0203aec4(int);
extern void func_ov009_022639a0(void *, int);

void func_ov009_02263658(void *arg)
{
    if (func_02096168(arg)) {
        int res = func_ov009_02264c90(arg);
        switch (res) {
            case 2:
                func_0203aec4(res);
                func_ov009_022639a0(arg, 6);
                break;
            case 3:
                func_0203aec4(res);
                func_ov009_022639a0(arg, 6);
                break;
        }
    }
}
