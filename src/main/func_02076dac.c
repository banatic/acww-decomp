/* func_02076dac @ 0x02076dac, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern unsigned char data_020e54a8;
extern void func_020736bc(int, void *, int);
extern void func_ov003_0222e4c0(unsigned char);

void func_02076dac(int arg0, int sequence, unsigned char category, unsigned int player)
{
    unsigned char local[4];
    unsigned int flag;

    func_020736bc(data_020ccf94, local, arg0);
    flag = (data_020e54a8 == 0) ? 1 : 0;
    if (flag > 0) {
        func_ov003_0222e4c0(local[0]);
    }
}
