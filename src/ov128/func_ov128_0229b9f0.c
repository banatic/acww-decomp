/* func_ov128_0229b9f0 @ 0x0229b9f0, 0x64 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088df8(int a, char *b, void *c, void *d, int e, int f, int g, int h, int i, int j, int k, int l);
extern int data_ov128_0229ca00[];
extern int data_ov128_0229c890[];

void func_ov128_0229b9f0(unsigned char *self)
{
    unsigned char idx1;
    unsigned char idx2;
    char *b;
    char *d;

    if (self[0x2d6e] == 0) {
        return;
    }

    idx1 = self[0x2d70];
    b = (char *) data_ov128_0229ca00[idx1 - 2];
    idx2 = self[0x2d6d];
    d = (char *) data_ov128_0229c890[idx2] + 0x60;

    func_02088df8(1, b, (void *) 0x80, d, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
}
