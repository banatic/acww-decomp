/* func_0209a6fc @ 0x0209a6fc, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void *func_0209a6fc(void *base, unsigned int idx)
{
    if (idx < 5) {
        return (char *) base + 0x1c + idx * 0x1e;
    } else {
        return 0;
    }
}
