/* func_02045d44 @ 0x02045d44, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_02045bac(int arg);
extern void func_020461e0(char *ptr);
extern int data_021c7880;

void func_02045d44(void)
{
    char *p;
    int i;
    p = func_02045bac(0);
    for (i = 0; i < 20; i++) {
        func_020461e0(p);
        p += 16;
    }
    data_021c7880 = 0;
}
