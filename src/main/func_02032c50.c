/* func_02032c50 @ 0x02032c50, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02032d34(void *ptr);

void *func_02032c50(void *obj)
{
    func_02032d34((void *) ((char *) obj + 0xC));
    return obj;
}
