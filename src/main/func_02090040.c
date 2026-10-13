/* func_02090040 @ 0x02090040, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02090078(int);

extern unsigned char data_021ee418[];

int func_02090040(int param)
{
    switch (param) {
        case 1:
            return func_02090078(0);
        case 2:
            return func_02090078(1);
        case 3:
            return func_02090078(2);
        default:
            return (unsigned int) data_021ee418;
    }
}
