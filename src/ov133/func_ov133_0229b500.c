/* func_ov133_0229b500 @ 0x0229b500, 0x160 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229b500 {
    char pad_00[0x64];
    int unk_64;
};

extern void *func_020984e8(void);
extern void func_02077ec0(void *buf);
extern void func_02077e68(void *buf);
extern void *func_02099664(void *a);
extern void *func_02077bcc(void *record);
extern int func_02077dd4(void *p, char *q, void *r);
extern void func_ov133_0229bb78(char *self, int a, int b);
extern void RtcSendPxiCommand(int cmd);
extern void func_02077ebc(void *buf);
extern int func_ov133_0229b660(char *self);
extern int func_ov133_0229b6b8(char *self, void *buf);
extern int func_ov133_0229b714(void *receiver);
extern void *func_02077c3c(void *e);
extern void func_0206fc4c(int v);
extern void *func_ov002_0220a720(char *p, int v);
extern void func_ov002_02208090(char *self, int v);
extern unsigned char *func_ov002_02208098(char *self, unsigned char value);
extern int func_0206fca4(void);
extern int func_ov133_0229c3d4(char *self, int v);
extern int func_020ee45c(char *self);
extern void func_ov090_02298fa4(int);
extern void func_0206f51c(void);
extern int func_02073dd4(struct UnkStruct_0229b500 *p, int v);
extern int func_020ec1e8(void);
extern int func_0206fc8c(void);
extern void *func_02077d68(void *t);
extern int func_020eaf48(u8 a, void *b);
extern struct UnkStruct_0229b500 *data_020ccf94;

void func_ov133_0229b500(char *self)
{
    char buf[0xc];
    void *a;
    void *e;
    void *t;
    struct UnkStruct_0229b500 *p;
    int m;
    int b;

    a = func_020984e8();
    func_02077ec0(buf);
    func_02077e68(buf);
    if (func_02077dd4(buf, self + 0xa4, func_02077bcc(func_02099664(a))) == 0) {
        func_ov133_0229bb78(self, 0x19, 0);
        RtcSendPxiCommand(0x73);
        func_02077ebc(buf);
        return;
    }
    if (func_ov133_0229b660(self)) {
        func_ov133_0229bb78(self, 0x1d, 0);
        RtcSendPxiCommand(0x73);
        func_02077ebc(buf);
        return;
    }
    if (func_ov133_0229b6b8(self, buf)) {
        func_ov133_0229bb78(self, 0x14, 0);
        RtcSendPxiCommand(0x73);
        func_02077ebc(buf);
        return;
    }
    e = (void *) func_ov133_0229b714(self);
    t = func_02077c3c(e);
    func_02077dd4(t, self + 0xa4, func_02077bcc(func_02099664(a)));
    func_0206fc4c(1);
    func_ov002_0220a720(self + 0x180, 6);
    func_ov002_02208090(self, 3);
    func_ov002_02208098(self, 0xa);
    RtcSendPxiCommand(0x29);
    if (func_0206fca4() == 0xe) {
        func_ov133_0229c3d4(self, 0xc);
    } else {
        func_ov090_02298fa4((int) func_020ee45c(self));
        func_ov133_0229c3d4(self, 6);
        func_0206f51c();
        p = data_020ccf94;
        if (func_02073dd4(p, p->unk_64)) {
            m = func_020ec1e8();
            switch (m) {
                case 3:
                case 4:
                    b = func_0206fc8c();
                    if (func_020eaf48(b, func_02077d68(func_02077c3c(e))) == 0) {
                        func_ov002_02208098(self, 0xc);
                        func_02077ebc(buf);
                        return;
                    }
                    break;
            }
        }
    }
    func_02077ebc(buf);
}
