/* func_02007ce4 @ 0x02007ce4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c773c[];
extern void func_02011098(int a, int b);

void func_02007ce4(int a, int b)
{
    if (data_020c773c[b] != 0) {
        func_02011098(a, 0);
    }
}
