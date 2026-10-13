/* func_02037c48 @ 0x02037c48, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064b2c(void *p1, int val, int count, void *p2);
extern unsigned int data_021fbe94; // at 0x021fbe94
extern unsigned int data_021c590c; // at 0x021c590c
extern unsigned char data_020da4b4[];
extern unsigned char data_021c5910[];

int func_02037c48(void)
{
    data_021c590c = func_02064b2c(data_020da4b4, data_021fbe94, 4, data_021c5910);
    return 1;
}
