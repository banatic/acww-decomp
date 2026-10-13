/* func_020b6098 @ 0x020b6098, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6140(void *self, int arg1, void *p1, void *p2, void *p3, void *p4, void *p5, void *p6, void *p7, void *p8);
extern void func_020b64f0(void *table, unsigned char b0, void *rest, unsigned int w8, int s4, unsigned int w12,
                          unsigned int w16);
extern int func_020b63f4(void *self, unsigned char b0, void *rest, unsigned int w8, int s4, unsigned char b1,
                         unsigned char b2);

extern unsigned char data_021f69a0[];
extern unsigned char data_021f69b8[];

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    short unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned char rest[12];
} UnkStruct_020b6098;

int func_020b6098(void *self, int arg1)
{
    UnkStruct_020b6098 data;
    int r;

    r = func_020b6140(self, arg1, &data.unk_00, &data.rest, &data.unk_08, &data.unk_04, &data.unk_01, &data.unk_02,
                      &data.unk_0C, &data.unk_10);
    if (r == 0) {
        goto fail;
    }
    switch (r) {
        case 2:
            func_020b64f0(data_021f69a0, data.unk_00, &data.rest, data.unk_08, (int) data.unk_04, data.unk_0C, data.unk_10);
            break;
        case 3:
            func_020b64f0(data_021f69b8, data.unk_00, &data.rest, data.unk_08, (int) data.unk_04, data.unk_0C, data.unk_10);
            break;
    }
    r = func_020b63f4(self, data.unk_00, &data.rest, data.unk_08, (int) data.unk_04, data.unk_01, data.unk_02);
    if (r == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
