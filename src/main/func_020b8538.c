/* func_020b8538 @ 0x020b8538, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d2254[];

unsigned char func_020b8538(int r0)
{
    if (r0 < 0) {
        goto out;
    }
    if (r0 >= 23) {
        goto out;
    }
    return data_020d2254[r0];
out:
    return 0;
}
