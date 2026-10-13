/* func_02058eec @ 0x02058eec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205967c(void *base, void *field);
extern void VEC_Add(void *a, void *b, void *c);

void func_02058eec(char *p)
{
    func_0205967c(p, p + 0x60);
    VEC_Add(p + 0x60, p + 0x84, p + 0x60);
}
