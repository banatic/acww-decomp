/* func_ov113_02299e98 @ 0x02299e98, 0x78 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void func_020708e4(int, short *, int);
extern void func_ov113_02299db8(int, int, int, int, int, int);

void func_ov113_02299e98(int arg0, int arg1)
{
    short local[3];

    if (arg1 + 1 >= 10) {
        local[0] = (arg1 + 1) / 10 + 0xff10;
        local[1] = (arg1 + 1) % 10 + 0xff10;
        local[2] = 0;
    } else {
        local[0] = arg1 + 0xff11;
        local[1] = 0;
    }

    func_020708e4(arg0 + 0x27c0, local, 3);
    func_ov113_02299db8(arg0, 2, 0x11a, 2, 1, 0);
}
