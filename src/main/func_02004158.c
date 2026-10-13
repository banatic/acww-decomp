/* func_02004158 @ 0x02004158, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern int data_021c67b8[3];
extern void func_020f660c(int a, int *b, int c);

void func_02004158(int a, int *src, int c)
{
    int diff[3];
    if (data_021c67a4 == 0) {
        return;
    }
    diff[0] = src[0] - data_021c67b8[0];
    diff[1] = src[1] - data_021c67b8[1];
    diff[2] = src[2] - data_021c67b8[2];
    func_020f660c(a, diff, c);
}
