/* func_02052078 @ 0x02052078, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060bf8(int *p, int a, int b);
extern void func_020520a0(int a, int b, int c);
extern int data_021ebcd4;

void func_02052078(int a, int b)
{
    func_02060bf8(&data_021ebcd4, a, b);
    func_020520a0(a, b, 4);
}
