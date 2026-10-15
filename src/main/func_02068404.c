/* func_02068404 @ 0x02068404, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8bb8(void *p, int n);

void func_02068404(void *base, int index, int n)
{
    func_020a8bb8((void *) ((char *) base + 0x14b8 + index * 92), n);
}
