/* func_ov096_0229f874 @ 0x0229f874, 0x58 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x2c];
    unsigned char unk_BA;
} Ov096Struct;

extern volatile unsigned char data_021f43ec;
extern void func_ov002_0220b9b8(void *, unsigned char *, unsigned int, int);
extern void func_ov002_02208098(void *, unsigned int);
extern void func_0208e5c4(void *);

void func_ov096_0229f874(Ov096Struct *self, int a, int b, unsigned int size)
{
    volatile unsigned char data;

    if (b == 0xff) {
        self->unk_BA = self->unk_8D;
    } else {
        self->unk_BA = b;
    }

    data = data_021f43ec;
    data = a;

    func_ov002_0220b9b8((char *) self + 0x2958, (unsigned char *) &data, size, 0);
    func_ov002_02208098(self, 0x20);
    func_0208e5c4((char *) self + 0x2500);
}
