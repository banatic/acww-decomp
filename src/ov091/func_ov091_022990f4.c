/* func_ov091_022990f4 @ 0x022990f4, 0x58 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_02036468(char *);
extern void func_ov002_02207ecc(void *, int, int, int, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern char *data_021c526c;

void func_ov091_022990f4(void *self)
{
    int zero = 0;
    RtcSendPxiCommand(2);
    func_02036468(data_021c526c + 0x1c4);
    func_ov002_02207ecc(self, 10, zero, zero, 0x30);
    func_ov002_02207e80(self, zero, zero, zero);
    func_ov002_02207e80(self, 2, zero, zero);
    func_ov002_02208090(self, 5);
}
