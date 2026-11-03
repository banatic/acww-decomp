/* session_record_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207762c @ 0x0207762c, 0xc bytes, Thumb
 * func_02077620 @ 0x02077620, 0xc bytes, Thumb
 * func_02077614 @ 0x02077614, 0xc bytes, Thumb
 * func_02077608 @ 0x02077608, 0xc bytes, Thumb
 * func_020775fc @ 0x020775fc, 0xc bytes, Thumb
 * func_020775f0 @ 0x020775f0, 0xc bytes, Thumb
 * func_020775e4 @ 0x020775e4, 0xc bytes, Thumb
 * func_020775d8 @ 0x020775d8, 0xc bytes, Thumb
 * func_020775cc @ 0x020775cc, 0xc bytes, Thumb
 * func_020775c0 @ 0x020775c0, 0xc bytes, Thumb
 */

extern unsigned char data_020ccfa8[];
extern unsigned short data_020cd050[];
extern void func_02085350(void *buffer, int index);

unsigned char func_0207762c(unsigned int r0)
{
    return data_020ccfa8[r0];
}

unsigned short func_02077620(unsigned short param)
{
    return data_020cd050[param];
}

void func_02077614(void *buffer)
{
    func_02085350(buffer, 0xc);
}

void func_02077608(void *buffer)
{
    func_02085350(buffer, 13);
}

void func_020775fc(void *buffer)
{
    func_02085350(buffer, 14);
}

void func_020775f0(void *buffer)
{
    func_02085350(buffer, 0xf);
}

void func_020775e4(void *buffer)
{
    func_02085350(buffer, 0x10);
}

void func_020775d8(void *buffer)
{
    func_02085350(buffer, 0x11);
}

void func_020775cc(void *buffer)
{
    func_02085350(buffer, 0x12);
}

void func_020775c0(void *buffer)
{
    func_02085350(buffer, 0x13);
}
