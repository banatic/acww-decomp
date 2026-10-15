/* func_ov045_02260978 @ 0x02260978, 0x2b0 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x744];
    u8 unk_744;
    u8 unk_745;
    char pad1[2];
    int unk_748;
    char pad2[8];
    int unk_754;
} UnkStruct_02260978;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad1[0x21];
    void *unk_40;
    char pad2[0x70];
    UnkStruct_02260978 *unk_B4;
} UnkStruct_02260978_2;

extern char data_021dc7a8[];
extern void *data_020ccf94;
extern int data_ov045_02261380;

extern int func_020984e8(void);
extern void func_020157c8(UnkStruct_02260978_2 *self, int a, int b);
extern int func_02015828(UnkStruct_02260978_2 *self, int a);
extern void func_ov045_022607ac(UnkStruct_02260978_2 *self, int a);
extern void func_ov045_022605a4(UnkStruct_02260978 *h);
extern int func_0201b43c(UnkStruct_02260978 *h, int a);
extern void func_0201b420(UnkStruct_02260978 *h, int a);
extern void func_ov045_02260e50(UnkStruct_02260978 *h, int a);
extern void func_02099768(int a, int b);
extern int func_0202ea80(int a, int b);
extern int func_ov045_02260524(UnkStruct_02260978 *h);
extern int func_02099870(int a);
extern void func_0207acbc(char *p, int a);
extern void func_0207adf4(char *p);
extern void *func_0207cd84(char *p, int a, int b, int c);
extern void *func_020807dc(void *p, int a);
extern void *func_020807c0(void *p, void *q);
extern unsigned int func_0208150c(void *p);
extern int func_02003704(void *argument0);
extern void *func_0207f270(void *p);
extern int func_02073dd4(void *g, void *h);
extern int func_020794c4(void *p);
extern void func_020794a8(void *p, int a);
extern void func_020794a4(void *p, int a);
extern void func_020794c0(void *p, int a);
extern signed char func_02081cec(void *p, int a);
extern int func_02081d20(void *p);
extern void func_020787d4(void *p, void *q, int x);
extern void func_0206844c(void *a, u8 *p, int c);

void func_ov045_02260978(UnkStruct_02260978_2 *self)
{
    void *a;
    void *b;
    void *c;
    int gid;
    u8 buf[4];
    int sess;
    int code;
    int kind;
    char (*q)[];
    void *obj;

    q = &data_021dc7a8;
    sess = func_020984e8();
    code = 0xff;
    switch (self->unk_1E) {
        case 9:
        case 11:
            func_020157c8(self, 0x13, 0);
            func_02015828(self, 2);
            func_ov045_022607ac(self, 1);
            break;
        case 14:
            func_ov045_022605a4(self->unk_B4);
            code = self->unk_B4->unk_744;
            break;
        case 16:
            if (func_0201b43c(self->unk_B4, 0x64) != 0) {
                func_0201b420(self->unk_B4, 0x64);
            }
            code = 0x16;
            break;
        case 19:
            func_ov045_02260e50(self->unk_B4, 3);
            break;
        case 24:
            if (func_0201b43c(self->unk_B4, 0x2710) != 0) {
                func_0201b420(self->unk_B4, 0x2710);
            }
            func_02099768(sess, 0);
            func_0202ea80(6, 1);
            code = 0x16;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
        default:
            break;
    }
    if (self->unk_B4->unk_745 != 0xff) {
        if (self->unk_B4->unk_745 == self->unk_1E) {
            code = 0x10;
            kind = func_ov045_02260524(self->unk_B4);
            gid = func_02099870(func_020984e8());
            switch (self->unk_B4->unk_748) {
                case 0:
                    func_02099768(sess, kind);
                    if (kind == 1) {
                        func_0207acbc((char *) ((int) (*q) + 0x9284), gid);
                    } else if (kind == 2) {
                        func_0207adf4((char *) ((int) (*q) + 0x9284));
                    }
                    break;
                case 1:
                    a = func_0207cd84((char *) ((int) (*q) + 0x9284), self->unk_B4->unk_754, 0xa, func_02099870(sess));
                    if (a != 0) {
                        b = func_020807dc(a, gid);
                        c = func_020807c0(a, b);

                        if (func_02003704((void *) func_0208150c(a)) != 0) {
                            obj = func_0207f270(a);
                        } else {
                            obj = 0;
                        }
                        if (c != 0) {
                            switch (kind) {
                                case 1:
                                    if (func_02073dd4(data_020ccf94, ((void **) data_020ccf94)[0x19]) == 0) {
                                        if (obj != 0) {
                                            if (func_020794c4(obj) == 1) {
                                                func_020794a8(obj, 0xe10);
                                            } else {
                                                func_020794a4(obj, 0xe10);
                                            }
                                            func_020794c0(obj, 1);
                                        }
                                    }
                                    func_02081cec(c, 0xa);
                                    func_020787d4(a, b, func_02081d20(c));
                                    break;
                                case 2:
                                    if (func_02073dd4(data_020ccf94, ((void **) data_020ccf94)[0x19]) == 0) {
                                        if (obj != 0) {
                                            if (func_020794c4(obj) == 4) {
                                                func_020794a8(obj, 0x4b0);
                                            } else {
                                                func_020794a4(obj, 0x4b0);
                                            }
                                            func_020794c0(obj, 4);
                                        }
                                    }
                                    func_02081cec(c, ~2);
                                    func_020787d4(a, b, func_02081d20(c));
                                    break;
                            }
                        }
                    }
                    break;
            }
            self->unk_B4->unk_745 = 0xff;
            self->unk_B4->unk_744 = 0xff;
        }
        if (self->unk_B4->unk_744 == self->unk_1E) {
            code = self->unk_B4->unk_745;
        }
    }
    if (code != 0xff) {
        buf[0] = (u8) code;
        func_0206844c(self->unk_40, buf, data_ov045_02261380);
    }
}
