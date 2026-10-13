/* func_0200f748 @ 0x0200f748, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02073908(int a, int b);
int func_0202f188(void);
int func_02008934(int *a, int b, int c, int d);
int func_02008a54(int *a, int b, int c);
extern int data_020ccf94;

int func_0200f748(int *arg)
{
    if (func_02073908(data_020ccf94, arg[0x200]) != 0) {
        if (func_0202f188() != 0) {
            func_02008934(arg, 0, 6, -1);
            return 1;
        } else if (((*(unsigned short *) 0x027fffa8) & 0x8000) >> 15) {
            func_02008a54(arg, 1, -1);
            return 1;
        }
    }
    return 0;
}
