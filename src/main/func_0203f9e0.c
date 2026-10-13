/* func_0203f9e0 @ 0x0203f9e0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_020992f0(void);
extern int func_0203fa98(int, int);

int func_0203f9e0(int arg0)
{
    int i;
    int result;
    int local_1;

    func_020984e8();
    local_1 = func_020992f0();
    i = 0;
    while (i < 4) {
        result = func_0203fa98(local_1, i);
        if (arg0 == result) {
            return i;
        }
        i++;
    }
    return -1;
}
