/* func_02038998 @ 0x02038998, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b4980(void *p0, void *p1, int p2);

extern unsigned char data_021c59d0[];
extern unsigned char data_021c5a24[];
extern unsigned char data_021c5b38[];

void func_02038998(void)
{
    unsigned char arr[3];
    arr[0] = 0xe3;
    arr[1] = 0xe4;
    arr[2] = 0xe5;
    func_020b4980((void *) data_021c5a24, arr, 0);
    func_020b4980((void *) data_021c59d0, arr + 1, 0);
    func_020b4980((void *) data_021c5b38, arr + 2, 0);
}
