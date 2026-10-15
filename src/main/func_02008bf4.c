/* func_02008bf4 @ 0x02008bf4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(int, int, int, unsigned short);
extern int func_02073908(int, int);
extern void func_02035684(int, int, int);
extern int func_0200f328(int, int);
extern int data_020ccf94;

void func_02008bf4(int param, void *message, int previous)
{
    int local;
    int *ptr;

    func_020109a0(param, 0x76, 3, 0);
    local = 0;
    *(char *) (param + 0x7d4) = local;
    ptr = &data_020ccf94;
    if (func_02073908(*ptr, *(int *) (param + 0x800)) != 0) {
        func_02035684(0xc, 0xf, 0);
    }
    func_0200f328(param, 0x83a);
}
