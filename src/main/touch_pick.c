/* touch_pick: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b74e4 @ 0x020b74e4, 0x8 bytes, Thumb
 * func_020b74dc @ 0x020b74dc, 0x8 bytes, Thumb
 * func_020b74d4 @ 0x020b74d4, 0x8 bytes, Thumb
 * func_020b74ac @ 0x020b74ac, 0x28 bytes, Thumb
 * func_020b74a4 @ 0x020b74a4, 0x8 bytes, Thumb
 */

extern int func_02096190(int);
extern int func_02082654(int);
extern int func_02082644(int);
extern unsigned char data_020e54a8;
extern int func_ov003_022201e4(int arg);

void func_020b74e4(int argument0)
{
    func_02096190((int) argument0);
}

void func_020b74dc(int argument0)
{
    func_02082654((int) argument0);
}

void func_020b74d4(int argument0)
{
    func_02082644((int) argument0);
}

int func_020b74ac(int p)
{
    unsigned int flag = (data_020e54a8 == 0) ? 1 : 0;
    if (flag > 0) {
        return func_ov003_022201e4(p);
    } else {
        return 0;
    }
}

void func_020b74a4(int argument0)
{
    func_020b74ac((int) argument0);
}
