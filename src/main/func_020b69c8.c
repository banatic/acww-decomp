/* func_020b69c8 @ 0x020b69c8, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_020b68b0(void *a, void *b);
extern void func_020b698c(void *a);
extern unsigned char data_020e5518;
extern unsigned char data_020e54a8;
extern unsigned char data_021f6a0c[];
extern unsigned short data_021f69ec[];

void func_020b69c8(void *arg0)
{
    int flag;

    func_020b68b0(arg0, &data_020e5518);
    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag != 0) {
        data_021f6a0c[0] = 0;
    } else {
        data_021f6a0c[0] = 1;
    }
    data_021f6a0c[1] = 8;
    data_021f69ec[0x11] = 0xd2;
    data_021f69ec[0x12] = 0x7fff;
    data_021f6a0c[6] = 0;
    func_020b698c(arg0);
}
