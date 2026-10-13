/* func_02021e68 @ 0x02021e68, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081e10(int a);
extern void func_0209e474(unsigned int *);
extern int func_0209e3ac(int, unsigned int *, int);
extern int func_0209e380(int, unsigned int *);

int func_02021e68(int a)
{
    unsigned int data[3];
    int ret;
    int r5;

    data[0] = 0;
    data[1] = 0;
    ret = func_02081e10(a);
    r5 = 0;
    func_0209e474(data);
    if (func_0209e3ac(ret, data, 0x3f) == -1) {
        r5 = func_0209e380(ret, data);
    }
    return r5;
}