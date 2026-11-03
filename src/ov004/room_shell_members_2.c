/* room_shell_members_2: 9 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022324f0 @ 0x022324f0, 0x18 bytes, Thumb
 * func_ov004_022324d8 @ 0x022324d8, 0x18 bytes, Thumb
 * func_ov004_022324b8 @ 0x022324b8, 0x20 bytes, Thumb
 * func_ov004_022324b4 @ 0x022324b4, 0x4 bytes, Thumb
 * func_ov004_0223248c @ 0x0223248c, 0x28 bytes, Thumb
 * func_ov004_02232470 @ 0x02232470, 0x1c bytes, Thumb
 * func_ov004_02232450 @ 0x02232450, 0x20 bytes, Thumb
 * func_ov004_022323d4 @ 0x022323d4, 0x7c bytes, Thumb
 * func_ov004_022323b0 @ 0x022323b0, 0x22 bytes, Thumb
 */

struct _Obj {
    void *vtbl;
};

typedef struct {
    unsigned char pad_00[24];
    unsigned long unk_18;
} UnkStruct_022324b4;

extern void func_020565ec(void *arg);
extern int data_ov004_02255ab8;
extern void *func_02056578(void *);
extern void func_020edb3c(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_020324c4(void *arg0);
extern void *func_020324fc(void *arg0);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern int func_020b67d4(void);
extern int func_020b67ac(void);
extern int func_020321bc(void *, int, int, int, int *, int, int);
extern int func_02032180(void *p);

void *func_ov004_022324f0(void *arg)
{
    func_020565ec(arg);
    *(void **) arg = &data_ov004_02255ab8;
    return arg;
}

void *func_ov004_022324d8(void *arg)
{
    *((void **) arg) = &data_ov004_02255ab8;
    func_02056578(arg);
    return arg;
}

void *func_ov004_022324b8(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255ab8);
    func_02056578(obj);
    func_020edb3c(obj);
    return obj;
}

unsigned long func_ov004_022324b4(UnkStruct_022324b4 *p)
{
    return p->unk_18;
}

void *func_ov004_0223248c(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_ctor(self, 0x2, 0x9c, ((void (*)(void *)) func_020324fc), ((void (*)(void *)) func_020324c4));
    return self;
}

void *func_ov004_02232470(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self, 0x2, 0x9c, ((void (*)(void *)) func_020324c4));
    return self;
}

int func_ov004_02232450(void)
{
    if (func_020b67d4() != 0 || func_020b67ac() != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov004_022323d4(char *self)
{
    int a[3], b[3];
    int r1, r2;
    if (func_ov004_02232450() != 0) {
        a[0] = 0xd000;
        a[1] = 0;
        a[2] = 0x1c000;
        b[0] = 0x13000;
        b[1] = 0;
        b[2] = 0x1c000;
        r1 = func_020321bc(self, 0x2000, 0, 0x4000, a, 0, 0);
        r2 = func_020321bc(self + 0x9c, 0x2000, 0, 0x4000, b, 0, 0);
        if (r1 != 0) {
            if (r2 != 0) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

int func_ov004_022323b0(char *self)
{
    if (func_ov004_02232450()) {
        func_02032180(self);
        func_02032180(self + 0x9c);
    }
    return 1;
}
