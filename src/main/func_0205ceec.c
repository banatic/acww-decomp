/* func_0205ceec @ 0x0205ceec, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205cf10(void);
extern unsigned char data_020dd414[];

unsigned char func_0205ceec(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    func_0205cf10();
    {
        unsigned char *r1 = *(unsigned char **) (data_020dd414 + (r5 << 2));
        return r1[r4 << 1];
    }
}
