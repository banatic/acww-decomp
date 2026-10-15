/* func_0200db88 @ 0x0200db88, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200dbac(void *a, void *b);

void func_0200db88(void *a, void *b, int previous)
{
    void *r4 = a;
    func_0200dbac((char *) r4 + 0x7d4, *(void **) ((char *) b + 0xc));
    *(int *) ((char *) r4 + 0x7f8) = 0;
}
