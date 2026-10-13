/* func_02097bdc @ 0x02097bdc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(int *p);
extern void func_020edf54(int *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e30b8[];

int *func_02097bdc(int *p)
{
    *p = (unsigned int) data_020e30b8;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
