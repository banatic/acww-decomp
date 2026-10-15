/* func_ov003_0222e538 @ 0x0222e538, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222e538;

extern UnkStruct_0222e538 *data_020ccf94;
extern unsigned char data_ov003_022617bc[];
extern unsigned char data_ov003_02260994[];

extern int func_02073dd4(UnkStruct_0222e538 *p, int val);
extern int func_020a7278(void);
extern void func_ov003_0222e4c0(int v);
extern void func_02073820(UnkStruct_0222e538 *p);
extern void func_020737f0(UnkStruct_0222e538 *p, unsigned char *id, int n);
extern void func_02073770(UnkStruct_0222e538 *p, int a, int b);

extern unsigned char data_ov003_0226053c;

unsigned char func_ov003_0222e538(int v, unsigned char unused)
{
    unsigned char id;
    unsigned char *p;
    int ok;
    unsigned char i;
    UnkStruct_0222e538 *o;

    p = 0;
    ok = 0;
    i = v & 0xf;
    if ((v >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((v >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    } else {
        ok = 1;
    }
    if (p == 0) {
        ok = 1;
    }
    if (ok != 1) {
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0) {
            ok = data_ov003_0226053c;
        }
    }
    if (ok == 1) {
        func_ov003_0222e4c0(v);
        id = v;
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0) {
            o = data_020ccf94;
            func_02073820(o);
            func_020737f0(o, &id, 1);
            func_02073770(o, 0x2f, 4);
        }
    }
    return ok;
}
