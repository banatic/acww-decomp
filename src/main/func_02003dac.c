/* func_02003dac @ 0x02003dac, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003dac(void *r0);

void func_02003dac(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    unsigned int *p32 = (unsigned int *) r0;

    p32[0] = 3;
    p32[1] = 0;
    p32[2] = 0;
    p32[3] = 0;
    p32[4] = 0;
    p[0x14] = 0;
    p[0x15] = 0;
}
