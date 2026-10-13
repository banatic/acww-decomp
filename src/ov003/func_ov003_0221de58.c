/* func_ov003_0221de58 @ 0x0221de58, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221e6a0(void *p);
extern int func_02056f94(void *p);
extern void func_020b2800(void *p, int v);
extern void func_02055124(void *p);
extern void func_02056ffc(void *p);

void func_ov003_0221de58(void *p)
{
    if (func_ov003_0221e6a0(p) != 0 && func_02056f94((char *) p + 0x1d8) != 0) {
        func_020b2800(p, 0);
    } else {
        func_02055124((char *) p + 0x13c);
    }
    func_02056ffc((char *) p + 0x2b8);
    *((int *) (*(int **) ((char *) p + 0x2d0))) = *(int *) ((char *) p + 0x2c0);
}
