/* func_02087ec0 @ 0x02087ec0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_0209e3ac(void *, void *, int);

int func_02087ec0(void *param)
{
    int result;
    int local[2];
    int i;

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    result = func_0209e3ac(param, local, 0x3f);
    i = 0;
    if (result == -1) {
        i = 1;
    }
    return i;
}
