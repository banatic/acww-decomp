/* func_ov123_0229bc70 @ 0x0229bc70, 0xb0 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov123_02299650(void *, int);
extern void func_ov123_02299630(void *, int);
extern void func_ov123_02299640(void *, int);
extern void func_ov123_022996dc(void *);
extern void func_ov123_02299ea8(void *);
extern void func_02004644(int, int);
extern void func_02004658(int);

void func_ov123_0229bc70(unsigned char *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov123_02299650(self, 0x80000)) {
            func_ov123_02299630(self, 0x80000);
            func_02004644(0x862, 1);
        }
        func_ov123_02299ea8(self);
    } else {
        func_ov123_02299630(self, 0x100000);
        func_ov123_022996dc(self);
        self[0xb4] = data_021f6c58;
        self[0xb5] = data_021f6c54;

        if (func_ov123_02299650(self, 0x100000)) {
            if (func_ov123_02299650(self, 0x80000) == 0) {
                func_ov123_02299640(self, 0x80000);
                func_02004658(0x862);
            }
        } else {
            if (func_ov123_02299650(self, 0x80000)) {
                func_ov123_02299630(self, 0x80000);
                func_02004644(0x862, 1);
            }
        }
    }
}
