/* func_ov003_0222e3a4 @ 0x0222e3a4, 0x11c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222e3a4;

extern UnkStruct_0222e3a4 *data_020ccf94;
extern unsigned char data_ov003_022617bc[];
extern unsigned char data_ov003_02260994[];

extern void *func_0209d088(void *p);
extern int NNS_G3dMdlGetMdlAlpha(void *p, int a);
extern void NNS_G3dMdlSetMdlAlpha(void *p, int a, int b);
extern int func_02073dd4(UnkStruct_0222e3a4 *p, int val);
extern int func_020a7278(void);
extern void func_02073820(UnkStruct_0222e3a4 *p);
extern void func_020737f0(UnkStruct_0222e3a4 *p, unsigned char *id, int n);
extern void func_02073770(UnkStruct_0222e3a4 *p, int a, int b);

extern unsigned char data_ov003_0226053c;

int func_ov003_0222e3a4(unsigned char id)
{
    unsigned char *p;
    unsigned char st;
    unsigned char ty;
    unsigned char i;
    UnkStruct_0222e3a4 *o;

    i = id & 0xf;
    if ((id >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((id >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    } else {
        return 0;
    }

    st = p[0x251];
    ty = p[0x24d];
    if (ty == -1 || p[0x250] != 3 || st == 0xb || st == 9 || st == 0x10) {
        return 0;
    }
    if (ty == 0x31 || ty == 0x1e || ty == 0x35) {
        if (NNS_G3dMdlGetMdlAlpha(func_0209d088(p + 0x130), 0) < 0x1f) {
            return 0;
        }
    }
    if (ty == 0x35 && st == 0x13) {
        return 0;
    }
    if (*(signed char *) (p + 0x24d) != 0x3a && *(signed char *) (p + 0x24d) != 0x3b) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(p + 0x130), 0, 0);
        p[0x251] = 0x10;
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0) {
        data_ov003_0226053c = 2;
        o = data_020ccf94;
        func_02073820(o);
        func_020737f0(o, &id, 1);
        func_02073770(o, 0x28, 6);
    }
    return 1;
}
