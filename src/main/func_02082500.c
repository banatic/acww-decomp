/* func_02082500 @ 0x02082500, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200363c(void);
extern char data_020cd884[];

int func_02082500(int param)
{
    int result;
    int index;
    int temp;

    result = 0;
    index = 0;

    if (func_0200363c() != 0) {
        temp = param * 0x4e;
        result = (int) &data_020cd884[temp];
    }

    return result;
}
