/* func_02042120 @ 0x02042120, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned short *data_021c75b4;

void func_02042120(void)
{
    *((volatile unsigned short *) 0x04000040) = *data_021c75b4;
    *((volatile unsigned short *) 0x04001040) = *data_021c75b4;
    *((volatile unsigned short *) 0x04000044) = 0xC0;
    *((volatile unsigned short *) 0x04001044) = 0xC0;
}
