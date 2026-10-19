/* func_ov050_02264018 @ 0x02264018, 0xbc bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern const int *func_02095794(int);
extern void func_0204f818(int *a, int *b, const int *c);
extern int func_02014868(void *ptr);
extern int func_0203b144(void);
extern int func_02095ab0(void *dst, int val, int size);
extern void *func_0209615c(unsigned int size);
extern int func_0203e020(unsigned char *self);
extern void func_ov050_02264834(unsigned char *self, int param);

extern const int data_ov050_0226509c[3];

int func_ov050_02264018(unsigned char *self)
{
    int z[4];
    int data[3];
    int gdata[3];
    int tmp[3];
    int a, b, c;

    func_020984e8();
    {
        const int *p = func_02095794(4);
        data[0] = p[0];
        data[1] = p[1];
        data[2] = p[2];
    }
    z[0] = 0;
    z[1] = 0;
    z[2] = 0;
    z[3] = 0;

    a = data_ov050_0226509c[0];
    gdata[0] = a;
    b = data_ov050_0226509c[1];
    gdata[1] = b;
    c = data_ov050_0226509c[2];
    gdata[2] = c;

    func_0204f818(&z[2], &z[3], gdata);
    func_0204f818(&z[0], &z[1], data);

    switch (self[0x651]) {
        case 0:
            if (func_02014868(self + 0x618) == 0) {
                func_0203b144();
                self[0x651] = 1;
            }
            break;
        case 1:
            tmp[0] = a;
            tmp[1] = b;
            tmp[2] = c;
            func_02095ab0(tmp, 0x266, 4);
            self[0x651] = 2;
            break;
        case 2:
            if (func_0209615c(4) == 0) {
                func_0203e020(self);
                func_ov050_02264834(self, 2);
            }
            break;
        default:
            break;
    }
    return 1;
}
