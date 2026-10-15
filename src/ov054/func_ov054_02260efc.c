/* func_ov054_02260efc @ 0x02260efc, 0x3c8 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x14];
    int unk_14;
} MessageController;

typedef struct {
    u8 pad_00[0x808];
    unsigned int unk_808;
} UnkStruct_02260efc;

typedef struct {
    u8 pad_00[0x1e];
    u8 unk_1E;
    u8 pad_1F[0x21];
    MessageController *unk_40;
    u8 pad_44[0x6c];
    UnkStruct_02260efc *unk_B0;
    u8 pad_B4[0xc0 - 0xb4];
    int unk_C0;
    u8 pad_C4[0xc8 - 0xc4];
    u16 unk_C8;
} Obj_ov054_02263004;

typedef struct {
    void *a;
    int b;
    int c;
} E12;
extern E12 data_ov054_02262fac[];

typedef struct {
    u8 code;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

typedef struct {
    u8 pad_00[8];
    int unk_08;
} P46784;

extern void *func_020984e8(void);
extern void *func_020992fc(void *a);
extern void func_02068440(MessageController *p);
extern void func_ov054_02260a88(Obj_ov054_02263004 *self, int a);
extern void func_ov054_02261d54(Obj_ov054_02263004 *self);
extern int func_0206f87c(void);
extern int func_ov054_02261ddc(Obj_ov054_02263004 *self);
extern int func_ov054_02261da4(Obj_ov054_02263004 *self);
extern int func_ov054_02261d8c(Obj_ov054_02263004 *self);
extern void func_020157c8(Obj_ov054_02263004 *self, int a, int b);
extern int func_02015828(Obj_ov054_02263004 *self, int a);
extern void func_ov054_02261cc4(Obj_ov054_02263004 *self, int a);
extern int func_020983f0(void *p);
extern void func_02068364(MessageController *p, int a);
extern void func_ov054_02260710(Obj_ov054_02263004 *self, int a);
extern void func_020a01b4(void);
extern void func_02074b44(int a, int b, int c);
extern int func_0204678c(void);
extern int func_02099020(void *a, int b);
extern int func_0204cae8(void);
extern int func_0202e9fc(void);
extern int func_0209a000(u16 *p, int a);
extern P46784 *func_02046784(void);
extern int func_020154b4(Obj_ov054_02263004 *self, u16 *p, int a, int b, int c);
extern void func_02098ff8(void *a, int b);
extern void func_ov054_02262528(UnkStruct_02260efc *p, int a);
extern void func_0206844c(MessageController *p, Msg *m, void *messageText);

void func_ov054_02260efc(Obj_ov054_02263004 *self, int arg)
{
    MessageController *controller;
    void *player;
    void *itemContext;
    void *messageText;
    int code;
    Msg msg;

    controller = self->unk_40;
    player = func_020984e8();
    // Keep this return alive through dispatch for case22.
    itemContext = func_020992fc(player);
    messageText = data_ov054_02262fac[self->unk_B0->unk_808].a;
    code = 0;

    switch (self->unk_1E) {
        case 2:
            func_02068440(controller);
            break;

        case 0:
        case 0x52:
        case 0x53:
        case 0x56:
            func_ov054_02260a88(self, arg);
            break;

        case 14:
        case 0x5c:
        case 0x62:
            func_ov054_02261d54(self);
            if (func_0206f87c() != 0) {
                code = 9;
                break;
            }
            code = func_ov054_02261ddc(self);
            if (code == 9) {
                code = 5;
            }
            break;

        case 7:
            code = func_ov054_02261ddc(self);
            break;

        case 0x61:
            func_ov054_02261d54(self);
            break;

        case 0x58:
            func_ov054_02261d54(self);
            code = func_ov054_02261da4(self);
            if (code == 9) {
                code = func_ov054_02261d8c(self);
            }
            break;

        case 0x59:
        case 0x5a:
        case 0x5b:
            func_ov054_02261d54(self);
            code = func_ov054_02261d8c(self);
            break;

        case 11:
        case 13:
        case 17:
            func_020157c8(self, 0x33, 0);
            func_02015828(self, 2);
            func_ov054_02261cc4(self, 5);
            break;

        case 18:
            func_020157c8(self, 0x34, 1);
            func_02015828(self, 2);
            func_ov054_02261cc4(self, 6);
            break;

        case 22:
            self->unk_C0 = func_020983f0(itemContext);
            func_020157c8(self, 0x3b, 1);
            func_02015828(self, 2);
            func_ov054_02261cc4(self, 7);
            break;

        case 19:
        case 20:
        case 21:
        case 23:
        case 24:
            code = 0x52;
            break;

        case 0x55:
            func_02068440(controller);
            func_02068364(controller, code);
            func_ov054_02261cc4(self, 8);
            break;

        case 25:
        case 27:
            func_020157c8(self, 0x37, 1);
            func_02015828(self, 2);
            func_ov054_02261cc4(self, 3);
            break;

        case 0x49:
            func_020157c8(self, 0x3f, code);
            func_02015828(self, 2);
            func_ov054_02261cc4(self, 4);
            break;

        case 29:
        case 30:
            func_ov054_02260710(self, arg);
            break;

        case 0x36:
            func_02068440(controller);
            func_02068364(controller, 1);
            func_020a01b4();
            func_02074b44(2, 2, code);
            self->unk_C8 = 0x258;
            func_ov054_02261cc4(self, 0xc);
            break;

        case 0x3d:
            switch (func_0204678c()) {
                case 0:
                    code = 0x42;
                    break;
                case 1:
                    code = 0x41;
                    break;
                case 2:
                    code = 0x40;
                    break;
                case 3:
                    code = 0x3f;
                    break;
                case 4:
                    code = 0x3e;
                    break;
                default:
                    code = 0x40;
                    break;
            }
            break;

        case 0x3e:
            if (func_02099020(player, 0x20) != 0) {
                code = 0x4b;
                break;
            }
            if (func_0204cae8() != 0 && func_0202e9fc() != 0) {
                msg.unk_02 = 0x1379;
                if (func_0209a000(&msg.unk_02, code) != 0) {
                    code = 0x4d;
                    break;
                }
            }
            code = 0x4c;
            break;

        case 0x40:
        case 0x41:
        case 0x42:
            switch (func_02046784()->unk_08) {
                case 0:
                    code = 0x43;
                    break;
                case 1:
                    code = 0x44;
                    break;
                case 2:
                    code = 0x45;
                    break;
                case 3:
                    code = 0x46;
                    break;
                case 4:
                    code = 0x47;
                    break;
                case 5:
                    code = 0x48;
                    break;
                default:
                    code = 0x43;
                    break;
            }
            break;

        case 0x4e:
            msg.unk_04 = 0x1379;
            func_020154b4(self, &msg.unk_04, code, 5, 1);
            func_02098ff8(player, 0x20);
            break;

        case 0x3b:
            func_02068440(controller);
            func_02068364(controller, 0);
            func_ov054_02261cc4(self, 0xe);
            break;

        case 0x3c:
            controller->unk_14 = 0;
            func_ov054_02262528(self->unk_B0, 8);
            break;
    }

    if (code != 0) {
        msg.code = (u8) code;
        func_0206844c(controller, &msg, messageText);
    }
}
