/* func_ov137_0229cd5c @ 0x0229cd5c, 0x98 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(int self, int a);
extern void func_ov137_0229c854(int self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov134_0229a1f0(int ptr, int b1, int b2);
extern void func_ov137_0229c8d4(int self);
extern void func_ov137_0229c8a8(int self);
extern unsigned char *func_ov002_02208098(int self, unsigned char value);

void func_ov137_0229cd5c(int self)
{
    unsigned int ok;
    int r;
    if (func_ov002_02208054(self, 1)) {
        func_ov137_0229c854(self);
        return;
    }
    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }
    r = func_ov134_0229a1f0(self + 0x2c4, data_021f6c58, data_021f6c54);
    switch (r) {
        case 0:
            func_ov137_0229c8d4(self);
            break;
        case 1:
            func_ov137_0229c8a8(self);
            break;
        case 3:
            func_ov002_02208098(self, 2);
            break;
        case 2:
            func_ov002_02208098(self, 3);
            break;
    }
}
