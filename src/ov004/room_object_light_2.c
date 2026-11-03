/* room_object_light_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02211444 @ 0x02211444, 0xc bytes, Thumb
 * func_ov004_02211414 @ 0x02211414, 0x30 bytes, Thumb
 */

extern void func_02064db8(int a, int b, int c);
extern int func_020b65c4(void);
extern void func_02052038(int a, int b);

int func_ov004_02211444(int x)
{
    if (x == 1) {
        return 1;
    }
    return 0;
}

void func_ov004_02211414(int a)
{
    int t = func_ov004_02211444(a);
    if (a == 2) {
        func_02064db8(0, 8, t);
    } else {
        func_02064db8(0, 0xc, t);
    }
    func_02052038(func_020b65c4(), 1);
}
