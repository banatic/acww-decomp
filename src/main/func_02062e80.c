/* func_02062e80 @ 0x02062e80, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02062280(int param1);
extern int func_02062e78(int param1, int param2);

int func_02062e80(int param1, int param2)
{
    int result;
    int temp;

    if (param2 < 0x4a) {
        temp = func_02062280(param2);
        result = func_02062e78(param1, temp);
        return 1;
    }
    return 0;
}
