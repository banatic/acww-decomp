/* wfc_stats: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02088274 @ 0x02088274, 0x10 bytes, Thumb
 * func_02088264 @ 0x02088264, 0x10 bytes, Thumb
 * func_02088250 @ 0x02088250, 0x14 bytes, Thumb
 * func_02088248 @ 0x02088248, 0x8 bytes, Thumb
 * func_02088224 @ 0x02088224, 0x24 bytes, Thumb
 * func_02088220 @ 0x02088220, 0x2 bytes, Thumb
 * func_02088214 @ 0x02088214, 0xc bytes, Thumb
 * func_02088208 @ 0x02088208, 0xc bytes, Thumb
 * func_020881fc @ 0x020881fc, 0xc bytes, Thumb
 * func_020881f0 @ 0x020881f0, 0xc bytes, Thumb
 * func_020881c4 @ 0x020881c4, 0x2c bytes, Thumb
 * func_020881b8 @ 0x020881b8, 0xc bytes, Thumb
 * func_020881ac @ 0x020881ac, 0xc bytes, Thumb
 */

extern char *func_02072dbc(int arg);
extern void *func_02072da4(int a);
extern void func_02072d58(int, int);
extern int func_02072d4c(int);
extern void func_02072f54(int, int);
extern int func_0209f150(const void *, int);
extern unsigned char data_021dc7a8[];

void func_02088224(int param);
void *func_02088220(void *record);

int func_02088274(int arg)
{
    func_02072dbc(arg);
    return arg;
}

int func_02088264(int a)
{
    func_02072da4(a);
    return a;
}

void func_02088250(void *r0)
{
    unsigned char *base = (unsigned char *) r0;
    base[0x236] = 0;
    func_02088224((int) r0);
}

void func_02088248(void *argument0)
{
    func_02088250((void *) argument0);
}

void func_02088224(int param)
{
    func_02072d58((int) func_02088220((void *) param), 0xf);
    func_02072f54(func_02072d4c((int) func_02088220((void *) param)), 0);
}

void *func_02088220(void *record)
{
    return record;
}

void func_02088214(unsigned char *r0, unsigned char r1)
{
    r0[0x236] = r1;
}

unsigned char func_02088208(unsigned char *r0)
{
    return r0[0x236];
}

void func_020881fc(unsigned char *r0, unsigned char r1)
{
    r0[0x237] = r1;
}

unsigned char func_020881f0(unsigned char *param0)
{
    return param0[0x237];
}

int func_020881c4(unsigned char *param)
{
    if (func_0209f150((const void *) data_021dc7a8, 0x13) == 0 && param[0x236] == 2) {
        return 1;
    }
    return 0;
}

void func_020881b8(unsigned short *ptr, unsigned short value)
{
    ptr[0x11A] = value;
}

unsigned short func_020881ac(void *this)
{
    return *(unsigned short *) ((char *) this + 0x234);
}
