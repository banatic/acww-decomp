/* func_ov141_0229a774 @ 0x0229a774, 0xc0 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int flag);
extern void func_ov141_0229a580(void *self);
extern void func_ov141_0229a174(void *self);
extern int func_ov141_02299f94(void *self, int _x);
extern void func_ov141_0229a4e8(void *self);
extern void func_ov141_0229a524(void *self);
extern void func_0200467c(int cmd);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;

void func_ov141_0229a774(void *self)
{
    unsigned int cond;
    int x;
    int y;

    if (func_ov002_02208054(self, 1)) {
        func_ov141_0229a580(self);
        return;
    }

    cond = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (cond) {
        y = (int) data_021f6c58;
        x = (int) data_021f6c54 - 0x10;
        if (y >= 0x28 && y < 0xd0 && x >= 0x30 && x < 0x90) {
            int idx;
            idx = (x - 0x30) >> 4;
            if (((unsigned char *) self + idx)[0x1a7f] == 0) {
                return;
            }
            if (!func_ov141_02299f94(self, idx)) {
                return;
            }
            func_0200467c(0x29);
        } else if (x >= 0x96 && x < 0xa7) {
            if (y >= 0x37 && y < 0x7b) {
                func_ov141_0229a4e8(self);
            } else if (y >= 0x89 && y < 0xc5) {
                if (*(int *) ((char *) self + 0x1274) == 8) {
                    func_ov141_0229a524(self);
                }
            }
        }
    } else {
        func_ov141_0229a174(self);
    }
}