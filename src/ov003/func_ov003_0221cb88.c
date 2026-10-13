/* func_ov003_0221cb88 @ 0x0221cb88, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_02264cf8(void *this, int param2);
extern void func_02056478(void *ptr, int a, int b, int c, int d);

int func_ov003_0221cb88(void *this)
{
    int ret;

    ret = func_ov009_02264cf8(this, 1);
    func_02056478((char *) this + 0x2b4, ret, 0, 0x1000, 0);
    *((char *) this + 0x2d5) = 1;
    return 1;
}
