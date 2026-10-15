/* func_ov004_02225240 @ 0x02225240, 0x188 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
#define P(p, o) (*(u8 **) ((p) + (o)))
extern void *data_ov004_02254794;
extern u8 *data_020ccf94;
extern void *func_0206837c(void *), *func_020984fc(int), *func_02099870(void *);
extern int func_02073d90(void *), func_0203a71c(void), func_020ab504(void *), func_02073dd4(void *, int), func_0209fbd0(void),
    func_0203a744(void);
extern void func_02015e40(void *, void *, int);
extern void func_02085c2c(u16 *);
extern void func_02015fb0(void *, int, int, int, int, int);
extern void func_020157c8(void *, int, int);
extern int func_02015828(void *, int);
extern void func_ov004_022251a4(void *, int);
extern void func_0206844c(void *, u8 *, void *);
void func_ov004_02225240(u8 *self)
{
    u16 code;
    u8 message;
    u8 *dialogue = P(self, 0x40);
    int choice = func_020ab504(func_0206837c(dialogue));
    void *text = data_ov004_02254794;
    u8 response = 255;
    switch (self[0x1e]) {
        case 15:
            if (choice == 0) {
                u8 *state = data_020ccf94;
                if (func_02073dd4(state, W(state, 0x64))) {
                    if (func_02073d90(state)) {
                        void *player = func_020984fc(func_0209fbd0());
                        if (player) {
                            func_02015e40(self, func_02099870(player), 1);
                        }
                        response = 0x30;
                    } else {
                        response = 0x2f;
                    }
                } else {
                    func_02085c2c(&code);
                    switch (code) {
                        case 0xd00a:
                            response = 0x22;
                            break;
                        case 0xd00e:
                            response = 0x23;
                            break;
                        case 0xd003:
                            response = 0x24;
                            break;
                        case 0xd013:
                            response = 0x25;
                            break;
                        case 0xd00b:
                            response = 0x26;
                            break;
                        case 0xd002:
                            response = 0x27;
                            break;
                        case 0xd00d:
                            response = 0x28;
                            break;
                        case 0xd021:
                            response = 0x29;
                            break;
                        case 0xd020:
                            response = 0x2a;
                            break;
                        case 0xd022:
                            response = 0x2b;
                            break;
                        case 0xd023:
                            response = 0x2c;
                            break;
                        default:
                            response = 0x2e;
                            break;
                    }
                }
            } else if (choice == 1) {
                if (func_0203a744()) {
                    func_02015fb0(self, func_0203a71c(), 0, 2, 0, 0);
                    response = 0x1a;
                } else {
                    response = 0x1b;
                }
            }
            break;
        case 22:
            if (choice == 0) {
                func_020157c8(self, 6, 0);
                func_02015828(self, 2);
                func_ov004_022251a4(self, 1);
            }
            break;
    }
    if (response != 255) {
        message = response;
        func_0206844c(dialogue, &message, text);
    }
}
