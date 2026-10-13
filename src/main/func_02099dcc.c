/* func_02099dcc @ 0x02099dcc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642d0(unsigned int a, unsigned int b, unsigned int c);
extern void func_02003728(void *a, void *b);

void func_02099dcc(char *a, void *b, char c, int d, unsigned short *e)
{
    func_020642d0((unsigned int) a, (unsigned int) d, (unsigned int) c);
    func_02003728(a + 0xe, b);
    *(unsigned short *) (a + 0x1e) = *e;
    a[0x20] = c;
}
