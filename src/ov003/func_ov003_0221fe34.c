/* func_ov003_0221fe34 @ 0x0221fe34, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_022203dc(void);
extern int func_02064960(int, int, int *, int);
extern int func_021077e8(void *resource);
extern int func_02056084(int, int);
extern int func_020561cc(int, int);
extern void func_020e9898(int);

extern int data_021fbe94;
extern int data_021c9b1c;
extern int data_ov003_02239b74;

int func_ov003_0221fe34(int *param)
{
    int a = data_021fbe94;
    int t = func_ov003_022203dc();
    int ret = func_02064960(a, ~3, &data_ov003_02239b74, t);

    if (ret != 0) {
        *param = func_021077e8((void *) ret);
        func_02056084(*param, 0);
        *param = func_020561cc(*param, data_021c9b1c);
        func_020e9898(ret);
        return 1;
    } else {
        return 0;
    }
}
