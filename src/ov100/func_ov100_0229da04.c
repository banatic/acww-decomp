/* func_ov100_0229da04 @ 0x0229da04, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern int func_ov100_0229cad0(void *);
extern int func_ov002_02208e28(void *);
extern void func_ov002_02208098(void *, int);

void func_ov100_0229da04(void *param)
{
    if (func_ov002_02208e28((char *) param + 0x22d8) != 0) {
        if (func_0206fe54() != 0) {
            func_ov100_0229cad0(param);
            func_ov002_02208098(param, 6);
        } else {
            func_ov002_02208098(param, 2);
        }
    }
}
