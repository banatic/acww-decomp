/* activity_fields_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a245c @ 0x020a245c, 0xc bytes, Thumb
 * func_020a2450 @ 0x020a2450, 0xc bytes, Thumb
 * func_020a2444 @ 0x020a2444, 0xc bytes, Thumb
 * func_020a2438 @ 0x020a2438, 0xc bytes, Thumb
 * func_020a242c @ 0x020a242c, 0xc bytes, Thumb
 */

unsigned char func_020a245c(unsigned char *param0)
{
    return param0[0x102];
}

unsigned char func_020a2450(const unsigned char *base, int offset)
{
    return *(base + offset + 0x103);
}

void func_020a2444(unsigned char *p, int offset, unsigned char c)
{
    (p + offset)[0x103] = c;
}

unsigned char func_020a2438(int a, int b)
{
    return *(unsigned char *) (a + b + 0x107);
}

void func_020a242c(char *ptr, int offset, char value)
{
    *(ptr + offset + 0x107) = value;
}
