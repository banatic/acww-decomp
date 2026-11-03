/* tailor_sister: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02222d08 @ 0x02222d08, 0x2 bytes, Thumb
 * func_ov004_02222d04 @ 0x02222d04, 0x2 bytes, Thumb
 * func_ov004_02222cd8 @ 0x02222cd8, 0x2c bytes, Thumb
 * func_ov004_02222b54 @ 0x02222b54, 0x184 bytes, Thumb
 * func_ov004_02222b3c @ 0x02222b3c, 0x16 bytes, Thumb
 * func_ov004_02222b24 @ 0x02222b24, 0x18 bytes, Thumb
 * func_ov004_02222af8 @ 0x02222af8, 0x2c bytes, Thumb
 * func_ov004_02222ad0 @ 0x02222ad0, 0x28 bytes, Thumb
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))

typedef struct UnkStruct_02222b54 UnkStruct_02222b54;

struct UnkStruct_02222b54 {
    void (**vt)(UnkStruct_02222b54 *);
};

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_02222ad0;

extern int func_02014868(void *);
extern int func_0201c014(void *);
extern u8 *data_020ccf94;
extern void func_0201c054(void *self, int mode, int first, int second);
extern void func_ov004_02223388(void *self, int state);
extern void func_02016108(void *self, void *target);
extern void func_0201b6e4(void *self, int event, int participant);
extern void *func_0201c2a4(void *self, int participant);
extern int func_0201c0e0(void *self);
extern int func_020a7278(void);
extern int func_0201c040(void *self, int *first, int *second);
extern int func_02088bdc(int);
extern int func_020984e8(void);
extern int func_02099670(int);
extern void func_02088bd8(int, int);
extern void *func_ov004_02222efc(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov004_0225445c[];

void func_ov004_02222d08(void) {}

void func_ov004_02222d04(void) {}

int func_ov004_02222cd8(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

void func_ov004_02222b54(u8 *self, int event, int who)
{
    switch (event) {
        case 3:
            self[0x560] = who;
            if (who != 4) {
                func_0201c054(self, 1, W(data_020ccf94, 0x64), who);
                func_ov004_02223388(self, 6);
            } else if (func_0201c0e0(self)) {
                int player = W(data_020ccf94, 0x64);
                func_0201c054(self, 1, player, player);
                func_ov004_02223388(self, 6);
            }
            break;
        case 0:
            self[0x560] = who;
            if (who != 4 && who != W(data_020ccf94, 0x64)) {
                func_0201c054(self, 1, who, who);
                func_ov004_02223388(self, 5);
            } else if (func_0201c0e0(self)) {
                int player = W(data_020ccf94, 0x64);
                func_0201c054(self, 1, player, player);
                ((UnkStruct_02222b54 *) (self + 0x658))->vt[2]((UnkStruct_02222b54 *) (self + 0x658));
                func_02016108(self + 0x658, func_0201c2a4(self, 4));
                func_ov004_02223388(self, 1);
            }
            break;
        case 8:
            if (who == 4) {
                if (func_020a7278()) {
                    func_0201c054(self, 1, W(data_020ccf94, 0x64), 4);
                    func_ov004_02223388(self, 3);
                } else {
                    func_0201c054(self, 1, 4, W(data_020ccf94, 0x64));
                    func_ov004_02223388(self, 4);
                }
            }
            break;
        case 4:
            if (func_0201c014(self) && func_0201c0e0(self)) {
                int first = 4, second = 4;
                if (func_0201c040(self, &first, &second)) {
                    if ((who != 4 && who == second) || who == 4) {
                        func_0201c054(self, 1, W(data_020ccf94, 0x64), 4);
                        func_ov004_02223388(self, 0);
                    }
                }
            }
            break;
    }
    func_0201b6e4(self, event, who);
}

int func_ov004_02222b3c(void *receiver)
{
    // DECLS
    // ENDDECLS
    return func_02088bdc(func_02099670(func_020984e8()));
}

void func_ov004_02222b24(int a, int b)
{
    func_02088bd8(func_02099670(func_020984e8()), b);
}

void *func_ov004_02222af8(void *s)
{
    *(void **) s = &data_ov004_0225445c;
    func_ov004_02222efc((char *) s + 0x658);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}

void *func_ov004_02222ad0(UnkStruct_02222ad0 *param)
{
    param->unk_00 = ((char *) data_ov004_0225445c);
    func_ov004_02222efc(&param->sub);
    func_0202ee5c(param);
    return param;
}
