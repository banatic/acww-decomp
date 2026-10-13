/* func_0207c330 @ 0x0207c330, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02080078(int);
extern void func_020800ec(int);
extern int func_020800fc(int);
extern void func_020642d0(int, int);
extern int func_0208150c(int);
extern int func_02003648(int);
extern void func_0207a1c8(char *, int);
extern void func_02079c30(char *, int);
extern void func_0208164c(int, int);
extern void func_02081660(int);
extern void MI_CpuCopy8(int, char *, int);

extern unsigned char data_021dc7aa[];

void func_0207c330(char *a, int b, int c, int d, int e)
{
    func_02080078(c);
    func_020800ec(c);
    func_020642d0(func_020800fc(c), (unsigned int) data_021dc7aa);
    a[0x4074] = (char) func_02003648(func_0208150c(c));
    func_0207a1c8(&a[0x3f7c], d);
    func_02079c30(&a[0x3f60], d);
    if (b) {
        func_0208164c(b, c);
    }
    func_02081660(c);
    MI_CpuCopy8(e, &a[0x4058], 8);
}
