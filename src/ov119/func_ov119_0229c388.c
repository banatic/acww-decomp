/* func_ov119_0229c388 @ 0x0229c388, 0xac bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229ae68(void *self);
extern int func_ov119_0229ad84(void *self);
extern void func_ov119_0229ad5c(void *self);
extern int func_ov119_0229acb4(void *self);
extern void func_020ee45c(void *self);
extern void func_ov090_02298fa4(void);
extern void func_ov119_0229a5d8(void *self);
extern void func_ov002_02209984(void *p, int a, int b, const char *data);
extern void func_ov119_0229adc4(void *self);
extern const char data_ov119_0229cfe0[];

void func_ov119_0229c388(char *self)
{
    if (func_ov119_0229ae68(self) == 0) {
        if (func_ov119_0229ad84(self) != 0) {
            func_ov119_0229ad5c(self);
            func_020ee45c(self);
            func_ov090_02298fa4();
        }
    } else {
        if (func_ov119_0229acb4(self) != 0) {
            func_020ee45c(self);
            func_ov090_02298fa4();
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
