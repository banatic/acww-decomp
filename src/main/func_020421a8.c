/* func_020421a8 @ 0x020421a8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8[];

void func_020421a8(void)
{
    unsigned char b;
    int i;

    b = data_021c75b8[1];
    if (b == 0) {
        i = *(int *) (data_021c75b8 + 4);
        i = i << 4;
        i = -i;
        i = i >> 12;
        *(int *) (data_021c75b8 + 12) = i;
    } else {
        i = *(int *) (data_021c75b8 + 4);
        i = i << 4;
        i = i >> 12;
        *(int *) (data_021c75b8 + 12) = i;
    }
}
