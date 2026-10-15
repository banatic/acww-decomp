/* func_02072e50 @ 0x02072e50, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02062da4(void *dst, const void *src, unsigned int size);

void func_02072e50(void *a, void *b)
{
    func_02062da4(b, (char *) a + 0x1e, 0xa);
}
