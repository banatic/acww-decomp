/* func_ov105_0229f064 @ 0x0229f064, 0x3c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229c3ac(void *arg);
extern int func_ov105_0229c340(void *arg, int size);
extern int func_020ee45c(void *arg);
extern void func_ov092_02299324(int arg1, int arg2, int arg3);
extern void func_ov105_0229c490(void *arg);
extern void func_ov002_02208090(void *arg, int val);

void func_ov105_0229f064(void *p)
{
    func_ov105_0229c3ac(p);
    if (func_ov105_0229c340(p, 256) == 0) {
        int r = func_020ee45c(p);
        func_ov092_02299324(r, 0x44, 1);
    }
    func_ov105_0229c490(p);
    func_ov002_02208090(p, 5);
}
