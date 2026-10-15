/* func_ov105_0229e804 @ 0x0229e804, 0x5c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov105_0229c340(void *self, int arg);
extern int func_ov105_0229d310(void *receiver);
extern void func_ov105_0229d970(void *self, unsigned char arg);
extern void func_ov002_022096d8(char *ptr, int arg);
extern int func_ov002_02207d24(char *ptr, int arg);

void func_ov105_0229e804(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 6);
        return;
    }
    if (func_ov105_0229c340(self, 4) != 0) {
        if (func_ov105_0229d310(self) != 0) {
            func_ov105_0229d970(self, ((unsigned char *) self)[0x2b5]);
            func_ov002_022096d8((char *) self + 0x2508, 0);
            func_ov002_02207d24((char *) self + 0x23bc, 1);
        }
    }
}
