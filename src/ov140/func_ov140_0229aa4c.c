/* func_ov140_0229aa4c @ 0x0229aa4c, 0xdc bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov140_0229ab28(void *);
extern int func_ov002_02208054(void *, int);
extern void func_ov140_0229a7cc(void *);
extern void func_ov140_0229a3fc(void *, int _x);
extern void func_ov140_0229a73c(void *);
extern void func_ov140_0229a774(void *);
extern void func_ov140_0229a6dc(void *);
extern void RtcSendPxiCommand(unsigned int);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;

void func_ov140_0229aa4c(unsigned char *self)
{
    unsigned int flag;
    int y, x;
    int idx;
    unsigned char *base;

    func_ov140_0229ab28(self);
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov140_0229a7cc(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (flag != 0) {
        y = data_021f6c58;
        x = (int) data_021f6c54 - 0x10;
        if (y >= 0x28 && y < 0xd0 && x >= 0x30 && x < 0x90) {
            idx = (x - 0x30) >> 4;
            base = self + idx;
            if (base[0x8af] != 0 && base[0x8e0] != 4) {
                func_ov140_0229a3fc(self, idx);
                RtcSendPxiCommand(0x29);
            }
        } else if (x >= 0x96 && x < 0xa7) {
            if (y >= 0x5e && y < 0x9a) {
                func_ov140_0229a73c(self);
            } else if (y >= 0x9f && y < 0xdb) {
                if (*(int *) (self + 0xa0) == 8) {
                    func_ov140_0229a774(self);
                }
            } else if (y >= 0x1d && y < 0x59) {
                if (*(int *) (self + 0xa8) == 8) {
                    func_ov140_0229a6dc(self);
                }
            }
        }
    }
}