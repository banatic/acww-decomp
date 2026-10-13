/* func_ov105_0229d970 @ 0x0229d970, 0x70 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229c330(void *, int);
extern void func_ov002_02207d24(void *, int);
extern void func_ov105_0229d0f8(void *, unsigned char);
extern void func_ov002_02208098(void *, int);
extern void func_ov105_0229d1c4(void *);
extern void func_ov094_022999c0(void);

void func_ov105_0229d970(unsigned char *self, unsigned char arg1)
{
    func_ov105_0229c330(self, 0x1000);
    self[0x2b7] = arg1;
    self[0x2b9] = arg1;
    self[0x2b8] = self[0x2c0];
    func_ov002_02207d24(self + 0x23bc, 1);
    func_ov105_0229d0f8(self, arg1);
    if (self[0x2b4] == 1) {
        func_ov002_02208098(self, 4);
    }
    func_ov105_0229d1c4(self);
    func_ov094_022999c0();
}
