/* letter_store_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209e5f0 @ 0x0209e5f0, 0x14 bytes, Thumb
 * func_0209e5e4 @ 0x0209e5e4, 0xc bytes, Thumb
 * func_0209e5d8 @ 0x0209e5d8, 0xc bytes, Thumb
 */

int func_0209e5f0(unsigned char *param0)
{
    if (param0[0x0000c800] == 2) {
        return 1;
    }
    return 0;
}

// placeholder, not used
void func_0209e5e4(unsigned char *base)
{
    base[0x0000c800] = 0x1c;
}

// placeholder for r0
void func_0209e5d8(unsigned char *r0)
{
    extern unsigned char *global_0x0000c800; // address 0x0000c800
    r0[0x0000c800] = 2;
}
