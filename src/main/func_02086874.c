/* func_02086874 @ 0x02086874, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02095238(void *);
extern void func_02003738(void *);

void func_02086874(void *param)
{
    void *r4 = param;
    func_02095238(r4);
    func_02003738((char *) r4 + 0x1e);
    func_02003738((char *) r4 + 0x2e);
    *(unsigned short *) ((char *) r4 + 0x3e) = 0xfff1;
    *(unsigned int *) ((char *) r4 + 0x40) = 0;
}
