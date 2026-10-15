/* func_020907c4 @ 0x020907c4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020906dc(void *base, void (*callback)(void *));

void func_020907c4(void *base, int index, void (*callback)(void *))
{
    func_020906dc((char *) base + index * 0x530, callback);
}
