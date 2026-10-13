/* func_02082618 @ 0x02082618, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082654(int arg);
extern int func_02082644(int arg);

int func_02082618(int arg1, int arg2)
{
    int result = 0;
    switch (arg1) {
        case 2:
            result = func_02082654(arg2);
            break;
        case 3:
            result = func_02082644(arg2);
            break;
    }
    return result;
}
