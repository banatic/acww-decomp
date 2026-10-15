/* func_020af950 @ 0x020af950, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_020af974(void *, void *);

int func_020af950(void *param)
{
    int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    return func_020af974(param, local);
}
