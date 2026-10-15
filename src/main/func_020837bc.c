/* func_020837bc @ 0x020837bc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d4f0(void *, int);

void func_020837bc(unsigned char *r4, int argument1)
{
    func_0205d4f0(r4 + 1, (int) argument1);
    *r4 = 1;
}
