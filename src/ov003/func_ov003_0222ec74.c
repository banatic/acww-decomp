/* func_ov003_0222ec74 @ 0x0222ec74, 0x11c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222ec74;
extern UnkStruct_0222ec74 *data_020ccf94;

extern char data_ov003_02260e4c[];
extern char data_ov003_0223c144[];

extern int func_020960d8(int i);
extern void func_0209129c(int a);
extern void func_ov003_0222fe18(void *a0, void *e, int n);
extern void func_ov003_0222ffdc(void *a0, void *e);
extern void func_ov003_0222fa20(void *a0, void *e, int n);
extern void func_02031288(void *a, int *b, int *c, int d, int e, int f, int g);
extern void func_ov003_0222f6b0(void *a0, void *e, int i, int n);

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
