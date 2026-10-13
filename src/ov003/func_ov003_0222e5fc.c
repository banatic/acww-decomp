/* func_ov003_0222e5fc @ 0x0222e5fc, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222e5fc;

extern UnkStruct_0222e5fc *data_020ccf94;
extern unsigned char data_ov003_022617bc[];
extern unsigned char data_ov003_02260994[];

extern int func_02073dd4(UnkStruct_0222e5fc *p, int val);
extern void func_02073820(UnkStruct_0222e5fc *p);
extern void func_020737f0(UnkStruct_0222e5fc *p, unsigned char *id, int n);
extern void func_02073770(UnkStruct_0222e5fc *p, int a, int b);

int func_ov003_0222e5fc(unsigned char id)
{
    unsigned char *p;
    UnkStruct_0222e5fc *o;
    unsigned char i;
    int r;
    i = id & 0xf;
    if ((id >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((id >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    }
    *(unsigned short *) (p + 0x242) = 0;
    p[0x250] = 4;
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        o = data_020ccf94;
        func_02073820(o);
        func_020737f0(o, &id, 1);
        func_02073770(o, 0x30, 4);
    }
    r = *(signed char *) (p + 0x24d);
    switch (r) {
        case 0x3a:
            p[0x251] = 8;
            p[0x250] = 3;
            return 0xb;
        case 0x3b:
            p[0x251] = 8;
            p[0x250] = 3;
            return 0x18;
    }
    return r;
}
