/* func_ov048_02260f30 @ 0x02260f30, 0x34 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_022609d0(void *this);
extern int func_ov048_02260e28(void *this, int arg1, int arg2);
extern int func_020e8840(int arg);

int func_ov048_02260f30(void *this)
{
    int result;
    int offset = 0x0e6e;

    if (func_020e8840(*(int *) ((char *) this + 0xb8) + offset) == 0) {
        result = func_ov048_022609d0(this);
        func_ov048_02260e28(this, result, 0);
        return 1;
    }
    return 0;
}
