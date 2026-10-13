/* func_ov099_0229d994 @ 0x0229d994, 0xa0 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229af40(void *, int);
extern void func_ov094_0229bbd8(void *, int);
extern void func_ov094_0229a2b0(void *, int);
extern void func_ov002_02209e18(void *);
extern void func_ov002_02209984(void *, int, long long);
extern void func_0209a088(void *, int, int);
void func_ov099_0229d994(unsigned char *self)
{
    unsigned short buf[2];
    *((unsigned int *) (self + 0x27e8)) = 0;
    func_ov094_0229af40(self + 0xcc, 2);
    func_ov094_0229bbd8(self + 0xb2c, 2);
    func_ov094_0229a2b0(self + 0xb54, 6);
    *((unsigned char *) (self + 0x2905)) = 0x1d;
    func_ov002_02209e18(self + 0x225c);
    *((unsigned char *) (self + 0x2903)) = 0;
    *((unsigned char *) (self + 0x2907)) = 0;
    func_ov002_02209984(self + 0x22d8, 3, 1);
    buf[0] = 0x11a9;
    func_0209a088(buf, 1, 0);
    buf[1] = 0x1548;
    func_0209a088(&buf[1], 0, 2);
}
