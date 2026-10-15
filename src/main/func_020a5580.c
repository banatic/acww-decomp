/* func_020a5580 @ 0x020a5580, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee550(void *);

int func_020a5580(void *argument0)
{
    int result;
    if (func_020ee550((void *) argument0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
