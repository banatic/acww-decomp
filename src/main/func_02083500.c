/* func_02083500 @ 0x02083500, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d8c4(unsigned char *, int);

void func_02083500(unsigned char *r4, int argument1)
{
    unsigned char *r0;

    r0 = r4 + 1;
    func_0205d8c4(r0, (int) argument1);
    *r4 = 1;
}
