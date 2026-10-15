/* func_020aec40 @ 0x020aec40, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aef5c(unsigned short *);
extern void func_020b0164(void *buffer, int *index, int a, int b, unsigned int count, int unused, unsigned char flag);

void func_020aec40(char *a, int *b)
{
    func_020b0164(a + 4, b, 1, 0, func_020aef5c((unsigned short *) a), 0x25, 0);
}
