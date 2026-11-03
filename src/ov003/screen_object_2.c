/* screen_object_2: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221b838 @ 0x0221b838, 0x4 bytes, Thumb
 * func_ov003_0221b834 @ 0x0221b834, 0x2 bytes, Thumb
 * func_ov003_0221b818 @ 0x0221b818, 0x1a bytes, Thumb
 */

extern int func_0206fbf8(int);

int func_ov003_0221b838(void *object)
{
    return 1;
}

void func_ov003_0221b834(void) {}

int func_ov003_0221b818(void *receiver)
{
    int result;

    if (func_0206fbf8(0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
