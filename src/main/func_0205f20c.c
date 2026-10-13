/* func_0205f20c @ 0x0205f20c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f2b0(char *a, int b, int c);
extern int func_0205f28c(char *a, int b);
extern int func_0205f5ec(int a);
extern int func_02064af4(int a, int b, int c);
extern char data_021ca16c[];

int func_0205f20c(int unused, int b, int c)
{
    int t1 = func_0205f2b0(data_021ca16c, b, c);
    int t2 = func_0205f28c(data_021ca16c, b);
    int t3 = func_0205f5ec(c);
    int t4 = func_02064af4(t3, t1, t2);
    return t2 - t4;
}
