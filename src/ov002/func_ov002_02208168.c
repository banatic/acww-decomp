/* func_ov002_02208168 @ 0x02208168, 0x30 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f258(void);
extern int func_0206f244(void);
extern void func_0206ef70(void);
extern void func_ov002_022080a0(int, int);

int func_ov002_02208168(int param)
{
    int r4 = param;
    if (func_0206f258() != 0) {
        func_ov002_022080a0(r4, 1);
    }
    if (func_0206f244() != 0) {
        func_0206ef70();
        func_ov002_022080a0(r4, 5);
    }
    return 1;
}
