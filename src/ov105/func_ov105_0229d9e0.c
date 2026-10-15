/* func_ov105_0229d9e0 @ 0x0229d9e0, 0x9c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov105_0229d530(void *self, unsigned char b);
extern int func_ov105_0229d4c4(void *self, unsigned char b);
extern void func_ov002_02207cf8(void *p);
extern void func_ov002_02207d00(void *p);
extern int func_ov105_0229d468(void *self, int x);
extern void func_ov105_0229c320(void *self, int x);
extern void func_ov105_0229c330(void *self, int x);
extern void func_ov094_022999cc(void);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov105_0229d9e0(char *self, int a1)
{
    *((unsigned char *) (self + 0x2b5)) = a1;
    func_ov002_02208098(self, 1);
    {
        unsigned char va = data_021f6c58;
        unsigned char vb = data_021f6c54;
        *((int *) (self + 0xa4)) = func_ov105_0229d530(self, *((unsigned char *) (self + 0x2b5))) - va;
        *((int *) (self + 0xa8)) = func_ov105_0229d4c4(self, *((unsigned char *) (self + 0x2b5))) - vb;
    }
    *((unsigned char *) (self + 0x2b6)) = a1;
    func_ov002_02207cf8(self + 0x23bc);
    func_ov002_02207d00(self + 0x23bc);
    *((unsigned char *) (self + 0x2c3)) = 2;
    if (func_ov105_0229d468(self, a1) != 0) {
        func_ov105_0229c320(self, 4);
    } else {
        func_ov105_0229c330(self, 4);
        func_ov094_022999cc();
    }
}
