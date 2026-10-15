/* func_ov003_0221df08 @ 0x0221df08, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221e6a0(void *obj);
extern int func_02056f94(void *ptr);
extern int func_ov003_0221e6ac(void *obj);
extern int func_020b2800(void *obj, int arg);
extern void func_02055124(void *ptr);
extern void func_02056ffc(void *ptr);

void func_ov003_0221df08(void *obj)
{
    if (func_ov003_0221e6a0(obj) && func_02056f94((char *) obj + 0x1d8)) {
        if (!func_ov003_0221e6ac(obj)) {
            func_020b2800(obj, 6);
        } else {
            func_020b2800(obj, 2);
        }
    } else {
        func_02055124((char *) obj + 0x13c);
    }
    func_02056ffc((char *) obj + 0x2b8);
    *((int *) *(int **) ((char *) obj + 0x2d0)) = *(int *) ((char *) obj + 0x2c0);
}
