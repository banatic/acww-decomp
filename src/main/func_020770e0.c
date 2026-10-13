/* func_020770e0 @ 0x020770e0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_020736bc(int, char *, int, int);
extern int func_0203f4ec(char *, int);

int func_020770e0(int a, int b, int c, int d)
{
    char buf[8];
    func_020736bc(data_020ccf94, buf, a, d);
    return func_0203f4ec(buf, d);
}
