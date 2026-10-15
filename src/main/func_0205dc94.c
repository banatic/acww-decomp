/* func_0205dc94 @ 0x0205dc94, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205dce0(const void *ptr, unsigned char c);
extern int func_0205dd60(int a);
extern int func_0205dd58(void);
extern int func_02064af4(int a, int b, int c);

extern unsigned char data_021c9e24[];

int func_0205dc94(unsigned char *p1, int p2)
{
    int a, b, c;
    a = func_0205dce0((void *) data_021c9e24, *p1);
    b = func_0205dd60(p2);
    c = func_0205dd58();
    return func_02064af4(b, a, c);
}
