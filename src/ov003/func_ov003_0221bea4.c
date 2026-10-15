/* func_ov003_0221bea4 @ 0x0221bea4, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e0a8(void *p, int n);

void func_ov003_0221bea4(void *p)
{
    unsigned int flags = ((unsigned char *) p)[0x235] & 4;
    if (flags != 0) {
        func_0203e0a8(p, 0);
    }
}
