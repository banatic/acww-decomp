/* func_020b4e70 @ 0x020b4e70, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050c18(void);
extern int func_020a9334(int, int);

int func_020b4e70(int r0)
{
    int r4 = r0;
    int r1 = func_02050c18();
    return func_020a9334(r4, r1);
}
