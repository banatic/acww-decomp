/* func_020417ac @ 0x020417ac, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020db6e4;
extern unsigned int data_020db6e0;
extern unsigned int data_020db6dc;
extern unsigned char data_021c75a0;

void func_020417ac(void)
{
    unsigned int *p;
    unsigned char *q;

    p = &data_020db6e4;
    *p = 0x63;
    p = &data_020db6e0;
    *p = 0x63;
    p = &data_020db6dc;
    *p = 0x63;

    q = &data_021c75a0;
    *q = 0;
    *(q + 2) = 0;
    *(q + 3) = 0;
}
