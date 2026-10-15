/* func_0207e4fc @ 0x0207e4fc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099734(int);
extern int func_02098cf8(int, int);

int func_0207e4fc(int object)
{
    int value;

    value = func_02098cf8(func_02099734(object), 1);
    if (value >= 0x9c40 && value < 0xea60) {
        return 1;
    } else {
        return 0;
    }
}
