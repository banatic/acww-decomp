/* town_insect_4: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222ed90 @ 0x0222ed90, 0x80 bytes, Thumb
 * func_ov003_0222ec74 @ 0x0222ec74, 0x11c bytes, Thumb
 * func_ov003_0222eb94 @ 0x0222eb94, 0xe0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222ec74;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222eb94;

extern char data_ov003_02260994[];
extern void func_ov003_0222fa20(void *a, void *b, int c);
extern void func_ov003_0222f6b0(void *a, void *b, int c, int d);
extern void func_ov003_0222fe18(void *a, void *b, int c);
extern UnkStruct_0222ec74 *data_020ccf94;
extern char data_ov003_02260e4c[];
extern char data_ov003_0223c144[];
extern int func_020960d8(int i);
extern void func_0209129c(int a);
extern int func_ov003_0222ffdc(void *a0, void *e);
extern void func_02031288(void *a, int *b, int *c, int d, int e, int f, int g);
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);

void func_ov003_0222ed90(void *ctx)
{
    char *o = data_ov003_02260994;
    unsigned char i = 0;
    do {
        switch (*(unsigned char *) (o + 0x250)) {
            case 2:
                func_ov003_0222fa20(ctx, o, 1);
                break;
            case 3:
                if (*(int *) (o + 0x204) > 0x1000) {
                    func_ov003_0222f6b0(ctx, o, i, 2);
                }
                break;
            case 4:
                *(char *) (o + 0x251) = 0xa;
                func_ov003_0222fe18(ctx, o, 2);
                break;
        }
        o += 0x25c;
        i = (unsigned char) (i + 1);
    } while (i < 2);
}

void func_ov003_0222ec74(void *a0)
{
    int n;
    char *e;
    u8 i;
    int neg1;
    int zero;
    int r;

    n = data_020ccf94->unk_64;
    if (n == 4) {
        n = 0;
    }
    e = data_ov003_02260e4c;
    i = 0;
    neg1 = ~i;
    zero = i;
    for (; i < 4; i++) {
        r = func_020960d8(i);
        if (n != i && *(u8 *) (e + 0x251) != 0xb && r != 0x57 && r != 0x58 && r != 0x76 && r != 6) {
            if (*(s8 *) (e + 0x24d) == 0x39) {
                func_0209129c(*(int *) (e + 0x22c));
                *(int *) (e + 0x22c) = neg1;
            }
            func_ov003_0222fe18(a0, e, 3);
        } else {
            switch (*(u8 *) (e + 0x250)) {
                case 1:
                    func_ov003_0222ffdc(a0, e);
                    break;
                case 2:
                    func_ov003_0222fa20(a0, e, 2);
                    func_02031288(e + 0x20, (int *) (e + 0x204), (int *) (e + 0x204), *(short *) (e + 0x23a),
                                  *(u16 *) (data_ov003_0223c144 + *(s8 *) (e + 0x24d) * 6 + 2), zero, 0xa);
                    break;
                case 3:
                    func_ov003_0222f6b0(a0, e, i, 3);
                    break;
                case 4:
                    *(u8 *) (e + 0x251) = 0xa;
                    func_ov003_0222fe18(a0, e, 3);
                    break;
            }
        }
        e += 0x25c;
    }
}

int func_ov003_0222eb94(int a, char *self)
{
    u8 s;
    s8 k;

    s = *(u8 *) (self + 0x251);
    k = *(s8 *) (self + 0x24d);
    if (s != 9 && s != 0xb) {
        if (k == 0x3a || k == 0x3b ||
            (func_02073dd4((*(UnkStruct_0222eb94 **) &data_020ccf94), (*(UnkStruct_0222eb94 **) &data_020ccf94)->unk_64) !=
                 0 &&
             func_020a7278() == 0)) {
            return 0;
        }
        if (s != 7) {
            switch (k) {
                case 9:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 31:
                case 33:
                case 34:
                case 36:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 50:
                case 52:
                case 53:
                    return 0;
                case 0x33:
                    if (*(int *) (self + 0x220) != *(int *) (self + 0x228)) {
                        return 0;
                    }
                    break;
                case 0x31:
                    if (s == 6) {
                        return 0;
                    }
                    break;
            }
        }
    }
    return 1;
}
