/* func_ov003_022152b4 @ 0x022152b4, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_02060474(void *);
extern void func_ov003_02215240(void *, int, int, int);

void func_ov003_022152b4(void *obj)
{
    if (func_02056f94((char *) obj + 0x2d0)) {
        if (func_02060474((char *) obj + 0x5c8)) {
            func_ov003_02215240(obj, 0, 6, -1);
        }
    }
}
