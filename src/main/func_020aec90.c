/* func_020aec90 @ 0x020aec90, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aef8c(unsigned short *);
extern void func_020b0164(void *buffer, int *index, int a, int b, unsigned int count, int unused, unsigned char flag);

void func_020aec90(char *a, int *b)
{
    func_020b0164(a + 4, b, 4, 0, func_020aef8c((unsigned short *) a), 37, 0);
}
