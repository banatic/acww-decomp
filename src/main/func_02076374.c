/* func_02076374 @ 0x02076374, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736bc(unsigned int, unsigned char *, int);
extern void func_020a7380(int, unsigned char);
extern unsigned int data_020ccf94;

void func_02076374(int a, int b, int c, int d)
{
    unsigned char local;

    func_020736bc(data_020ccf94, &local, 1);
    func_020a7380(d, local);
}
