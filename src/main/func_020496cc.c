/* func_020496cc @ 0x020496cc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02049944(int, int *, int *, void (*)(void));
extern void func_02049f74(void);

int func_020496cc(int unused, int param1, int *param2, int *param3)
{
    int local1[2];
    int local2[2];

    local2[0] = param3[0];
    local2[1] = param3[1];
    local1[0] = param2[0];
    local1[1] = param2[1];

    return func_02049944(param1, local1, local2, func_02049f74);
}
