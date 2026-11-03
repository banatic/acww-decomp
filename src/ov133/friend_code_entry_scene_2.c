/* friend_code_entry_scene_2: 14 functions, module ov133
 * mwccarm 1.2/base -O4,s
 * func_ov133_0229c404 @ 0x0229c404, 0x1c bytes, Thumb
 * func_ov133_0229c400 @ 0x0229c400, 0x4 bytes, Thumb
 * func_ov133_0229c3fc @ 0x0229c3fc, 0x4 bytes, Thumb
 * func_ov133_0229c3ec @ 0x0229c3ec, 0x10 bytes, Thumb
 * func_ov133_0229c3d4 @ 0x0229c3d4, 0x18 bytes, Thumb
 * func_ov133_0229c39c @ 0x0229c39c, 0x38 bytes, Thumb
 * func_ov133_0229c340 @ 0x0229c340, 0x5c bytes, Thumb
 * func_ov133_0229c2fc @ 0x0229c2fc, 0x44 bytes, Thumb
 * func_ov133_0229c2b0 @ 0x0229c2b0, 0x4c bytes, Thumb
 * func_ov133_0229c25c @ 0x0229c25c, 0x54 bytes, Thumb
 * func_ov133_0229c210 @ 0x0229c210, 0x4c bytes, Thumb
 * func_ov133_0229c1dc @ 0x0229c1dc, 0x34 bytes, Thumb
 * func_ov133_0229c158 @ 0x0229c158, 0x84 bytes, Thumb
 * func_ov133_0229c150 @ 0x0229c150, 0x8 bytes, Thumb
 */

#include "types.h"

#define TIMER(s) (*(vu8 *) ((s) + 0x9e))

struct Type {
    char pad_00[0x94];
    int unk_94;
};

void func_ov133_0229c134(void *self);
void func_ov133_0229c420(void *self);
void func_ov133_0229c12c(void *self);
extern void func_020ee470(void *parameter0);
extern int func_020ee45c(void *);
extern void func_ov090_022993cc(int, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_0220ab38(void *, int);
extern void func_ov133_0229c050(void *);
extern void func_ov133_0229c0a4(void *);
extern void func_ov133_0229c0f8(void);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int x);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov133_0229ad78(void *p, int x);
extern int func_ov002_02207f60(void *p);
extern int func_ov002_02207f48(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov133_0229bbb4(void *p);
extern int func_ov002_02207f3c(void *p, int x);
extern void func_020027f0(int x);
extern void func_ov133_0229ad68(void *p, int x);
extern int func_020984e8(void);
extern int func_02099870(int object);
extern int func_020950c0(signed char *);
extern void func_0200458c(int x);
extern void func_020b9ccc(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov133_0229bb64(void *);
extern void func_ov133_0229ad9c(u8 *self, u8 v);
extern void func_ov133_0229aed4(void *parameter0);

void func_ov133_0229c340(struct Type *p);

int func_ov133_0229c404(void *self)
{
    func_ov133_0229c134(self);
    func_ov133_0229c420(self);
    func_ov133_0229c12c(self);
    return 1;
}

int func_ov133_0229c400(void)
{
    return 1;
}

int func_ov133_0229c3fc(void)
{
    return 1;
}

int func_ov133_0229c3ec(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

int func_ov133_0229c3d4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov090_022993cc(func_020ee45c(self), (u8) a1);
    return 0x1;
}

void func_ov133_0229c39c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov133_0229c0f8();
    func_ov133_0229c0a4(self);
    func_ov133_0229c050(self);
    func_ov002_02208090(self, 0x1);
    func_ov002_0220ab38(self + 0x180, 0x65);
    func_ov133_0229c340((struct Type *) self);
}

void func_ov133_0229c340(struct Type *p)
{
    func_ov002_02207f20(p, 0xa, 0, 0, 0x30);
    func_02002708(4);
    func_ov002_02207e80(p, 4, 0, 0);
    func_02002708(6);
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov133_0229ad78(p, 1);
    p->unk_94 = func_ov002_02207f60(p);
    func_ov002_02208090(p, 2);
}

void func_ov133_0229c2fc(struct Type *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov133_0229bbb4(p);
    }
    func_ov002_02207e80(p, 4, 0, 0);
    func_ov002_02207e80(p, 6, 0, 0);
    p->unk_94 = func_ov002_02207f60(p);
}

void func_ov133_0229c2b0(void *param)
{
    extern void func_ov133_0229ba10(void *);
    extern void func_ov002_02207f04(void *, int, int, int, int);
    extern void func_ov002_02207e80(void *, int, int, int);
    extern void func_ov002_02208090(void *, int);
    extern int func_ov002_02207f60(void *);

    void *r4 = param;
    int result;

    func_ov133_0229ba10(r4);
    func_ov002_02207f04(r4, 10, 0, 0, 0x30);
    func_ov002_02207e80(r4, 4, 0, 0);
    func_ov002_02207e80(r4, 6, 0, 0);
    func_ov002_02208090(r4, 4);
    result = func_ov002_02207f60(r4);
    r4 = (char *) r4 + 0x94;
    *(int *) r4 = result;
}

void func_ov133_0229c25c(struct Type *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov133_0229ad68(p, 1);
        func_ov002_022080a0(p, 5);
    } else {
        func_ov002_02207e80(p, 4, 0, 0);
        func_ov002_02207e80(p, 6, 0, 0);
        p->unk_94 = func_ov002_02207f60(p);
    }
}

void func_ov133_0229c210(char *self)
{
    int object;
    *(u8 *) (self + 0x9a) = 0;
    *(u16 *) (self + 0x98) = 0;
    *(u8 *) (self + 0x9c) = 0xb;
    *(u8 *) (self + 0x9e) = 0;
    *(u8 *) (self + 0x9d) = 0;
    if ((object = func_020984e8()) != 0) {
        if (func_020950c0((signed char *) func_02099870(object)) == 0) {
            func_0200458c(0);
            return;
        }
    }
    func_0200458c(1);
}

void func_ov133_0229c1dc(char *self)
{
    // DECLS
    // ENDDECLS
    func_020b9ccc(self + 0x34c);
    func_020b9ccc(self + 0x370);
    func_ov133_0229bb64(self);
    func_ov002_0220af74(self + 0x180);
}

void func_ov133_0229c158(u8 *self)
{
    func_020b9ccc((void *) (self + 0x34c));
    func_020b9ccc((void *) (self + 0x370));
    func_ov133_0229bb64((void *) self);
    func_ov002_0220af74((void *) (self + 0x180));
    if (TIMER(self) != 0) {
        TIMER(self) = TIMER(self) - 1;
        if (TIMER(self) == 0) {
            if (self[0x9d] != 0) {
                TIMER(self) = 1;
            } else {
                func_ov133_0229ad9c(self, self[0xa0]);
            }
        }
    }
    self[0xa1] = self[0xa1] + 1;
}

void func_ov133_0229c150(void *arg0)
{
    func_ov133_0229aed4((void *) arg0);
}
