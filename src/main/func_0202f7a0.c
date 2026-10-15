/* func_0202f7a0 @ 0x0202f7a0, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f898(void *dst, void *src, void *src2);
extern int func_0202f7f4(void *ptr);

void func_0202f7a0(void *out, void *a, void *b)
{
    int tmp[2];
    func_0202f898(tmp, b, a);
    *(int *) out = -tmp[1];
    *(int *) ((char *) out + 4) = tmp[0];
    func_0202f7f4(out);
}
