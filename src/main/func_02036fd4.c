/* func_02036fd4 @ 0x02036fd4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02036f94(void *arg0);

void func_02036fd4(void *arg0)
{
    unsigned char val;
    void *r4;

    r4 = arg0;
    val = *(unsigned char *) ((int) r4 + 0xa);
    if (val == 0) {
        func_02036f94(r4);
    }
    *(unsigned char *) ((int) r4 + 0xb) = 0;
}
