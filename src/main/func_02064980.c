/* func_02064980 @ 0x02064980, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064300(void *dst, unsigned int size, const void *src, int param);
extern void *func_02064b2c(void *dst, const void *a, const void *b, const void *c);

void *func_02064980(void *a, void *b, void *c, void *d, int e)
{
    unsigned char buffer[0x80];

    func_02064300(buffer, 0x80, d, e);
    return func_02064b2c(buffer, a, b, c);
}
