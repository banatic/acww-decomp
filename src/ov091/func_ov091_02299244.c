/* func_ov091_02299244 @ 0x02299244, 0x9c bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern unsigned int data_021c526c;
extern void func_02036470(unsigned int, int);
extern int func_02001c30(int);
extern int func_0206fcbc(int);
extern void func_0206e230(unsigned char *, int, int, int, int);
extern void AOSS_Disconnect(unsigned char *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(unsigned char *, int, int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov002_02208090(unsigned char *, int);

void func_ov091_02299244(unsigned char *param)
{
    int t;

    RtcSendPxiCommand(1);
    func_02036470(data_021c526c + 0x1c4, 0);
    t = func_0206fcbc(func_02001c30(0));
    func_0206e230(param + 0x94, t, 0, 2, 1);
    AOSS_Disconnect(param, 10, 0, 0, 0x30);
    func_02002708(0);
    func_ov002_02207e80(param, 0, 0, 0);
    func_020028bc(0, 0, 0, 0);
    func_02002708(2);
    func_ov002_02207e80(param, 2, 0, 0);
    func_020028bc(2, 0, 0, 0);
    func_ov002_02208090(param, 1);
}
