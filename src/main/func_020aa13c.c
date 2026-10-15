/* func_020aa13c @ 0x020aa13c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aa09c(void *);

void func_020aa13c(unsigned char *r0)
{
    if (r0[4] != 0) {
        r0[4] = 0;
        func_020aa09c(r0);
    }
}
