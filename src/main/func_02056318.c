/* func_02056318 @ 0x02056318, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c8ca4;
extern unsigned int data_021c8ca8;
extern unsigned char data_020e54a8;
extern void func_0205cb34(int arg1, int arg2);

typedef struct {
    unsigned int a;
    unsigned int b;
} Entry;

extern Entry data_021c8cac[60];
extern Entry data_021c8e8c[150];

void func_02056318(void)
{
    int i;
    unsigned int flag;
    int param;

    for (i = 0; i < 150; i++) {
        data_021c8e8c[i].a = 0;
        data_021c8e8c[i].b = 0x4e554c4c;
    }
    for (i = 0; i < 60; i++) {
        data_021c8cac[i].a = 0;
        data_021c8cac[i].b = 0x4e554c4c;
    }
    data_021c8ca8 = 0;
    data_021c8ca4 = 0;
    flag = (data_020e54a8 == 0);
    if (flag > 0) {
        param = 0x7800;
    } else {
        param = 0x10400;
    }
    func_0205cb34(param, 0);
}
