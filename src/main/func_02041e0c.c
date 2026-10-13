/* func_02041e0c @ 0x02041e0c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75ac;
extern unsigned int data_021c75b4;

extern unsigned char data_021c75e8[];
extern unsigned char data_021c76a8[];

void func_02041e0c(void)
{
    unsigned char tmp;

    tmp = data_021c75ac;
    if (tmp & 2) {
        data_021c75b4 = (unsigned int) data_021c75e8;
        tmp &= ~2;
        data_021c75ac = tmp;
    } else {
        data_021c75b4 = (unsigned int) data_021c76a8;
        tmp |= 2;
        data_021c75ac = tmp;
    }
}
