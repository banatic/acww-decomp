/* func_0207f360 @ 0x0207f360, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f3a0(void *, void *, void *, int);
extern int func_0207ffa0(int a, int b);
extern void func_0207d5dc(int a, int b);

int func_0207f360(int a, void *argument1, void *argument2, int argument3)
{
    int b;
    int c;
    int d;

    b = func_0207f3a0((void *) a, (void *) argument1, (void *) argument2, (int) argument3);
    c = a;
    d = b;
    if (func_0207ffa0(c, d) != 0) {
        *(volatile unsigned short *) ((char *) a + (b << 1) + 0x78c) = 0xfff1;
        func_0207d5dc(a, b);
        return 1;
    }
    return 0;
}
