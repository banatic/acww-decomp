/* func_020112f8 @ 0x020112f8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011368(int);
extern int func_020996f8(int);

void func_020112f8(int param1, int param2)
{
    int result;
    int temp;

    result = func_02011368(param2);
    *(unsigned short *) param1 = 0xfff1;
    if (result != 0) {
        temp = func_020996f8(result);
        *(unsigned short *) param1 = *(unsigned short *) temp;
    }
}
