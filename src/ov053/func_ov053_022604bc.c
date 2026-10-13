/* func_ov053_022604bc @ 0x022604bc, 0x48 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095794(int);
extern int func_02030818(void *);
extern void func_ov053_02260bb0(void *, int);
extern void func_0203e0a8(void *, int);

int func_ov053_022604bc(void *arg)
{
    int *p;
    int local[3];
    int result;

    p = (int *) func_02095794(4);
    local[0] = p[0];
    local[1] = p[1];
    local[2] = p[2];

    if (func_02030818(local)) {
        func_ov053_02260bb0((char *) arg + 0x658, 10);
        func_0203e0a8(arg, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
