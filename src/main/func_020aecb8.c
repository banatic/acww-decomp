/* func_020aecb8 @ 0x020aecb8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aefa4(unsigned short *);
extern void func_020b00fc(void *buffer, int *index, int a, int b, unsigned int count, int unused, unsigned char flag);

void func_020aecb8(int *arg0, int *arg1)
{
    int tmp;

    tmp = func_020aefa4((unsigned short *) arg0);
    func_020b00fc(arg0 + 1, arg1, 0x151d, 2, tmp, 0x25, 0);
}
