/* shops: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ad7e4 @ 0x020ad7e4, 0x10 bytes, Thumb
 * func_020ad7c8 @ 0x020ad7c8, 0x1c bytes, Thumb
 * func_020ad7a4 @ 0x020ad7a4, 0x22 bytes, Thumb
 * func_020ad798 @ 0x020ad798, 0xc bytes, Thumb
 * func_020ad78c @ 0x020ad78c, 0xc bytes, Thumb
 * func_020ad74c @ 0x020ad74c, 0x40 bytes, Thumb
 */

extern int func_020b01dc(void *ptr);
extern unsigned char data_021f49ec[];
extern int func_020644cc(int arg);
extern unsigned short data_020d1e5c[];
extern void func_0209def4(unsigned char *buf);
extern int data_021f4a04;
extern int func_020b6660(void);
extern int func_02073d90(int);
extern int func_020aea84(void);
extern void func_020af3a0(void *, int);
extern int data_020ccf94;
extern int data_021f395c;

int func_020ad7e4(int value)
{
    return func_020b01dc((void *) data_021f49ec);
}

void func_020ad7c8(unsigned short *out)
{
    *out = data_020d1e5c[func_020644cc(0xc)];
}

int func_020ad7a4(void)
{
    unsigned char buf[4];
    func_0209def4(buf);
    if (buf[1] >= 8 && buf[1] < 0x17) {
        return 1;
    } else {
        return 0;
    }
}

int func_020ad798(void)
{
    return data_021f4a04;
}

void func_020ad78c(int value)
{
    data_021f4a04 = value;
}

void func_020ad74c(void)
{
    if (func_020b6660() != 0) {
        if (func_020ad798() == 2) {
            if (func_02073d90(data_020ccf94) == 0) {
                func_020aea84();
                func_020af3a0(&data_021f395c, 0);
            }
        }
        func_020ad78c(0);
    }
}
