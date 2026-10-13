/* func_ov105_0229e638 @ 0x0229e638, 0xbc bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov002_02208e28(void *);
extern int func_ov002_02208054(void *, int);
extern int func_ov002_02208b00(void *, int, int);
extern int func_ov105_0229c340(void *, int);
extern void func_ov002_02209114(void *, int, int);
extern void func_ov002_02208098(void *, int);
extern void func_ov105_0229cbb0(void *);
extern void RtcSendPxiCommand(int);

void func_ov105_0229e638(unsigned char *self)
{
    int r;
    unsigned int ok;
    unsigned int flag;
    unsigned char *p;

    if (func_ov002_02208e28(self + 0x2508) == 0) {
        return;
    }

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov105_0229cbb0(self);
        return;
    }

    ok = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (ok != 0) {
        r = func_ov002_02208b00(self + 0x2508, data_021f6c58, data_021f6c54);
        if (r >= 0) {
            if (func_ov105_0229c340(self, 0x800) != 0 && r == 0) {
                return;
            }

            p = self + r;
            self[0x2be] = p[0x28f5];

            flag = 1;
            if (self[0x2be] == 2) {
                flag = 0;
                RtcSendPxiCommand(0x24);
            }

            func_ov002_02209114(self + 0x2508, r, flag);
            func_ov002_02208098(self, 0x17);
        }
    }
}
