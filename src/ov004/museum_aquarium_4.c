/* museum_aquarium_4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02234c64 @ 0x02234c64, 0x248 bytes, Thumb
 * func_ov004_02234be0 @ 0x02234be0, 0x84 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 tag, count, rest[15];
} Entry;

struct UnkStruct_02234be0 {
    u8 pad_00[0x54];
    int arr[1];
};

extern u8 data_ov004_022593a4;
extern u8 data_ov004_02255c30;
extern int data_ov004_022593dc[3];
extern void *data_021fbe94;
extern char *data_ov004_022594d4[];
extern Entry data_ov004_02247924[];
extern void *func_020e9948(void *, int);
extern void func_ov004_02235374(void *, int);
extern void func_ov004_02234418(void *);
extern void *func_ov004_0223a31c(void *);
extern void *func_ov004_0223a2c0(void *);
extern void *func_ov004_0223a25c(void *);
extern void *func_ov004_0223a114(void *);
extern void *func_ov004_0223a09c(void *);
extern void *func_ov004_02239fd4(void *);
extern void *func_ov004_02239e9c(void *);
extern void *func_ov004_02239e40(void *);
extern void *func_ov004_02239df0(void *);
extern void *func_ov004_0223a3c4(void *);
extern int _s32_div_f(int n, int k);
extern int func_02064328(char *buf, const char *fmt, int a, int b, int c);
extern int func_02064b2c(char *buf, int h, int k, int m);
extern const char data_ov004_02255f38[];
extern const char data_ov004_02255f54[];

int func_ov004_02234be0(void *unused, struct UnkStruct_02234be0 **rp, int n, int count);

int func_ov004_02234c64(void *self)
{
    int i;
    void *heap;
    char **slot;
    data_ov004_022593a4 = 35;
    data_ov004_02255c30 = 56;
    data_ov004_022593dc[0] = 0x11000;
    data_ov004_022593dc[1] = 0;
    data_ov004_022593dc[2] = 0x136e1;
    heap = data_021fbe94;
    for (i = 35; i < data_ov004_02255c30; i++) {
        switch (i) {
            case 36:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x28c);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a31c(data_ov004_022594d4[i]);
                }
                break;
            case 50:
            case 51:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x258);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a2c0(data_ov004_022594d4[i]);
                }
                break;
            case 52:
            case 53:
            case 54:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x258);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a25c(data_ov004_022594d4[i]);
                }
                break;
            case 35:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x278);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a114(data_ov004_022594d4[i]);
                }
                break;
            case 37:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x26c);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a09c(data_ov004_022594d4[i]);
                }
                break;
            case 40:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x25c);
                if (data_ov004_022594d4[i]) {
                    func_ov004_02239fd4(data_ov004_022594d4[i]);
                }
                break;
            case 38:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x27c);
                if (data_ov004_022594d4[i]) {
                    func_ov004_02239e9c(data_ov004_022594d4[i]);
                }
                break;
            case 47:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x258);
                if (data_ov004_022594d4[i]) {
                    func_ov004_02239e40(data_ov004_022594d4[i]);
                }
                break;
            case 48:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x1fc);
                if (data_ov004_022594d4[i]) {
                    func_ov004_02239df0(data_ov004_022594d4[i]);
                }
                break;
            default:
                data_ov004_022594d4[i] = (char *) func_020e9948(heap, 0x258);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a3c4(data_ov004_022594d4[i]);
                }
                break;
        }
        slot = &data_ov004_022594d4[i];
        if (!*slot) {
            return 0;
        }
        if (data_ov004_02247924[i].count == 3) {
            (*slot)[0x1c6] = 1;
        }
        if (!func_ov004_02234be0(self, (struct UnkStruct_02234be0 **) slot, i, data_ov004_02247924[i].count)) {
            func_ov004_02235374(self, i);
            (*slot)[0x1c6] = 0;
            return 0;
        }
    }
    func_ov004_02234418(self);
    return 1;
}

int func_ov004_02234be0(void *unused, struct UnkStruct_02234be0 **rp, int n, int count)
{
    char buf[28];
    volatile int t;
    volatile int j;
    int i;
    int r;

    r = _s32_div_f(n, 0xa);
    t = r;
    t = r + 0xa;
    i = 0;
    j = 0;
    while (i < count) {
        if (n < 0xa) {
            func_02064328(buf, data_ov004_02255f38, t, n, i);
        } else {
            func_02064328(buf, data_ov004_02255f54, t, n, i);
        }
        (*rp)->arr[i] = func_02064b2c(buf, (*(int *) &data_021fbe94), 4, j);
        if ((*rp)->arr[i] == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}
