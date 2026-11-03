/* start_menu_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a01ec @ 0x020a01ec, 0xc bytes, Thumb
 * func_020a01e0 @ 0x020a01e0, 0xc bytes, Thumb
 */

extern unsigned char data_021f3c0c;

unsigned char func_020a01ec(void)
{
    return data_021f3c0c;
}

void func_020a01e0(unsigned char value)
{
    data_021f3c0c = value;
}
