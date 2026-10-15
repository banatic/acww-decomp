/* func_ov048_02260f00 @ 0x02260f00, 0x30 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov048_02260e28(void *this, int, int);
extern int func_020e8840(int);

int func_ov048_02260f00(void *this)
{
    int result;
    int v1;

    v1 = *(int *) ((char *) this + 0xb8);
    result = func_020e8840(v1 + 0xe6e);
    if (result == 0) {
        func_ov048_02260e28(this, 0x65, 0);
        return 1;
    }
    return 0;
}
