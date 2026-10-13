/* func_ov112_0229f11c @ 0x0229f11c, 0xd8 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *);
extern void func_020708e4(unsigned short *, const unsigned short *, int);
extern void func_ov112_0229f0b4(void *, int, int, int, int);

void func_ov112_0229f11c(void *self)
{
    struct {
        unsigned char pad[3];
        unsigned short arr[5];
    } data;
    unsigned char v0, v1, v2;

    func_0209df64(&data);
    data.arr[0] = 0xff12;
    data.arr[1] = 0xff10;
    v2 = data.pad[2];
    data.arr[2] = v2 / 10 + 0xff10;
    data.arr[3] = v2 % 10 + 0xff10;
    data.arr[4] = 0;
    func_020708e4((unsigned short *) ((unsigned char *) self + 0x3fac), data.arr, 5);
    func_ov112_0229f0b4(self, 0, 0x111, 4, 1);

    v1 = data.pad[1];
    data.arr[0] = v1 / 10 + 0xff10;
    data.arr[1] = v1 % 10 + 0xff10;
    v0 = data.pad[0];
    data.arr[2] = v0 / 10 + 0xff10;
    data.arr[3] = v0 % 10 + 0xff10;
    func_020708e4((unsigned short *) ((unsigned char *) self + 0x4018), data.arr, 5);
    func_ov112_0229f0b4(self, 1, 0x116, 4, 1);
}
