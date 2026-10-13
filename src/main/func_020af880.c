/* func_020af880 @ 0x020af880, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b00c8(void *dst, const void *src, int size);

void func_020af880(void *arg0)
{
    void *dst = (char *) arg0 + 4;
    const void *src = (char *) arg0 + 0x5c;
    func_020b00c8(dst, src, 0x25);
}
