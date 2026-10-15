/* func_0205f240 @ 0x0205f240, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f2e0(void *p, int);
extern int func_0205f2bc(void *p, int a);
extern int func_0205f60c(int a);
extern int func_02064af4(int a, int b, int c);

extern unsigned char data_021ca16c[];

int func_0205f240(int a0, int a1, int a2)
{
    int v0 = func_0205f2e0((void *) data_021ca16c, a1);
    int v1 = func_0205f2bc((void *) data_021ca16c, a1);
    int v2 = func_0205f60c(a2);
    int v3 = func_02064af4(v2, v0, v1);
    return v1 - v3;
}
