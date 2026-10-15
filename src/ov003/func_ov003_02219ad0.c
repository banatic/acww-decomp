/* func_ov003_02219ad0 @ 0x02219ad0, 0x66 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_0200fc90(void *argument0);
extern int func_ov003_02217c5c(int, int, int, int, int, int, int, int);
extern unsigned int *func_0200f27c(int, int);
extern int func_ov003_022188d0(int, int, int, int, int, int);

int func_ov003_02219ad0(int *a1, int *a2, short *a3)
{
    int r = func_02096718(4);
    if (r != 0) {
        if (func_0200fc90((void *) r)) {
            return func_ov003_02217c5c(r, 0x38, 0, *a1, *a2, *a3, 6, -1);
        } else {
            func_0200f27c(r, 1);
            return func_ov003_022188d0(r, *a1, *a2, *a3, 6, -1);
        }
    } else {
        return 0;
    }
}
