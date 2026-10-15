/* func_02003518 @ 0x02003518, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003518(void *object);
extern int func_020ee550(void *object);

int func_02003518(void *object)
{
    int result;
    if (func_020ee550(object) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
