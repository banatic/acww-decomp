/* order_catalog_scene: 4 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229b974 @ 0x0229b974, 0x28 bytes, Thumb
 * func_ov142_0229b928 @ 0x0229b928, 0x4c bytes, Thumb
 * func_ov142_0229b874 @ 0x0229b874, 0xb4 bytes, Thumb
 * func_ov142_0229b804 @ 0x0229b804, 0x70 bytes, Thumb
 */

extern void func_ov142_0229967c(void *);
extern void func_ov142_0229a45c(void *);
extern void func_ov142_0229a540(void *);
extern void func_ov002_0220a544(void *);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void *data_021fbe94;
extern const unsigned char data_ov142_0229c520[];
extern const unsigned char data_ov142_0229c538[];
extern const unsigned char data_ov142_0229c550[];
extern const unsigned char data_ov142_0229c564[];
extern const unsigned char data_ov142_0229c57c[];
extern const unsigned char data_ov142_0229c594[];
extern const unsigned char data_ov142_0229c5ac[];
int func_02002c6c(const void *src, void *dst, int size, int a, int b, int c);
int func_02002d14(const void *src, void *dst, int size, int a, int b, int c);
int func_02064af4(const void *src, void *dst, unsigned int size);
extern void func_ov002_0220af94(void *receiver);
extern unsigned char data_ov142_0229c4d8[];
extern unsigned char data_ov142_0229c4f0[];
extern unsigned char data_ov142_0229c508[];

void func_ov142_0229b974(void *self)
{
    func_ov142_0229967c(self);
    func_ov142_0229a45c(self);
    func_ov142_0229a540(self);
    func_ov002_0220a544((char *) self + 0x14c);
}

void func_ov142_0229b928(void)
{
    func_02001c08(0);
    func_020029e8(6, 1);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 2);
    func_020028bc(3, 0, 0, 0);
}

void func_ov142_0229b874(unsigned char *self)
{
    void *base = data_021fbe94;
    func_02002c6c(data_ov142_0229c520, base, 6, 0x11, 0x11, 0x51);
    func_02002c6c(data_ov142_0229c538, base, 6, 0x156, 0x156, 0x174);
    func_02002d14(data_ov142_0229c550, base, 6, 1, 1, 5);
    func_02064af4(data_ov142_0229c564, self + 0x3060, 0x20);
    func_02064af4(data_ov142_0229c57c, self + 0x30a0, 0x20);
    func_02064af4(data_ov142_0229c594, self + 0x1860, 0x800);
    func_02064af4(data_ov142_0229c5ac, self + 0x2860, 0x800);
}

void func_ov142_0229b804(int param)
{
    int *p;
    func_ov002_0220af94((void *) (param + 0x194));
    p = (*(int * *) &data_021fbe94);
    func_02002c6c((const void *) ((unsigned int) data_ov142_0229c4d8), (void *) p, 8, 0xc0, 0xc0, 0x11f);
    func_02002c6c((const void *) ((unsigned int) data_ov142_0229c4f0), (void *) p, 8, 0x120, 0x120, 0x17f);
    func_02002d14((const void *) ((unsigned int) data_ov142_0229c508), (void *) p, 8, 4, 4, 9);
}
