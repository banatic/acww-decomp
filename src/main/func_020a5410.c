/* func_020a5410 @ 0x020a5410, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffd3e8(unsigned char *object);
extern int func_020a5410(unsigned char *object);

int func_020a5410(unsigned char *object)
{
    int result;
    if (func_01ffd3e8(object) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
