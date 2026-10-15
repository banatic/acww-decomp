/* func_ov048_02260e78 @ 0x02260e78, 0x30 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov048_02260e28(void *receiver, int code, int flag);
extern int func_020e8840(int a);

int func_ov048_02260e78(void *this)
{
    int result;
    int offset = 0x0e6e;
    int value = *(int *) ((char *) this + 0xb8);
    if (func_020e8840(value + offset) == 0) {
        func_ov048_02260e28(this, 0x56, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
