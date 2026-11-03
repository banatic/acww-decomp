/* friend_roster_4: 4 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229c388 @ 0x0229c388, 0xac bytes, Thumb
 * func_ov119_0229c34c @ 0x0229c34c, 0x3c bytes, Thumb
 * func_ov119_0229c318 @ 0x0229c318, 0x34 bytes, Thumb
 * func_ov119_0229c300 @ 0x0229c300, 0x16 bytes, Thumb
 */

extern int func_ov119_0229ae68(void *receiver);
extern int func_ov119_0229ad84(void *receiver);
extern void func_ov119_0229ad5c(void *self);
extern int func_ov119_0229acb4(void *self);
extern int func_020ee45c(void *self);
extern void func_ov090_02298fa4(int);
extern void func_ov119_0229a5d8(void *self);
extern void func_ov002_02209984(void *p, int a, int b, const char *data);
extern void func_ov119_0229adc4(void *self);
extern const char data_ov119_0229cfe0[];
extern void func_ov002_02209178(void *p);
extern void func_ov119_0229bb7c(void *p);
extern void func_020b9ccc(void *p);
extern void func_ov119_0229b00c(void *p);
extern void func_ov002_022091cc(void *p);

void func_ov119_0229c388(char *self)
{
    if (func_ov119_0229ae68(self) == 0) {
        if (func_ov119_0229ad84(self) != 0) {
            func_ov119_0229ad5c(self);
            func_ov090_02298fa4((int) func_020ee45c(self));
        }
    } else {
        if (func_ov119_0229acb4(self) != 0) {
            func_ov090_02298fa4((int) func_020ee45c(self));
        }
    }
    *((unsigned char *) self + 0x9e) = 0;
    *(unsigned short *) (self + 0x98) = 0;
    *((unsigned char *) self + 0xa0) = 8;
    *((void **) (self + 0x1e0c)) = self + 0xe0c;
    *((short *) (self + 0x9a)) = -1;
    *((unsigned char *) self + 0x9c) = 0xff;
    *((unsigned char *) self + 0xaf) = 0;
    *((unsigned char *) self + 0xb0) = 7;
    *((int *) (self + 0xb8)) = 5;
    func_ov119_0229a5d8(self);
    func_ov002_02209984(self + 0xdc, 3, 1, data_ov119_0229cfe0);
    func_ov119_0229adc4(self);
}

void func_ov119_0229c34c(void *self)
{
    func_ov002_02209178((char *) self + 0xdc);
    func_ov119_0229bb7c(self);
    func_020b9ccc((char *) self + 0x1e90);
    func_020b9ccc((char *) self + 0x1eb4);
    func_020b9ccc((char *) self + 0x1ed8);
}

void func_ov119_0229c318(void *self)
{
    func_ov119_0229bb7c((void *) self);
    func_020b9ccc((char *) self + 0x1e90);
    func_020b9ccc((char *) self + 0x1eb4);
    func_020b9ccc((char *) self + 0x1ed8);
}

void func_ov119_0229c300(void *p)
{
    func_ov119_0229b00c(p);
    func_ov002_022091cc((char *) p + 0xdc);
}
