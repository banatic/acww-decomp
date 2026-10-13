/* func_02027170 @ 0x02027170, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c120(int a, int b, int c);

void func_02027170(unsigned short *param1, int param2)
{
    *param1 = 0xFFF1;
    *param1 = func_0204c120(param2, 0, 0);
    if (*param1 == 0xFFF1) {
        *param1 = 0x1492;
    }
}
