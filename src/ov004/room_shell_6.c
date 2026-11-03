/* room_shell_6: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02233318 @ 0x02233318, 0x1c bytes, Thumb
 * func_ov004_02233264 @ 0x02233264, 0xb4 bytes, Thumb
 * func_ov004_022331e8 @ 0x022331e8, 0x7c bytes, Thumb
 * func_ov004_02233164 @ 0x02233164, 0x84 bytes, Thumb
 * func_ov004_02233084 @ 0x02233084, 0xe0 bytes, Thumb
 * func_ov004_02232fdc @ 0x02232fdc, 0xa8 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec;

extern int func_020edf70(unsigned int size);
extern void *func_020ee660(void *argument0);
extern void *func_02055210(void *argument0);
extern void __cxa_vec_ctor();
extern void *func_ov004_022329e0(char *argument0);
extern void *func_ov004_02232754(char *argument0);
extern void *func_ov004_0223248c(char *argument0);
extern void *func_020324fc(void *argument0);
extern void *func_ov004_022322fc(char *argument0);
extern void *func_ov004_022324d8(void *arg0);
extern void *func_ov004_022324f0(void *arg0);
extern void *data_020da13c;
extern void *data_ov004_02255ac8;
extern void *data_0213efe8;
extern void *func_020324c4(void *);
extern void *func_020551e0(void *);
extern void func_020ee62c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern int func_ov004_022322ec(void *);
extern void *func_ov004_02232470(void *);
extern void *func_ov004_0223273c(void *);
extern void *func_ov004_022329c8(void *);
extern void func_020edf54(void *);
extern int func_ov004_022323d4(void *);
extern void func_ov004_0223232c(void *);
extern void func_ov004_0223228c(void *);
extern void func_ov004_02232edc(void *);
extern void func_ov004_02232a94(void *);
extern void func_ov004_02232a20(void *, void *);
extern void func_ov004_02232a68(void *);
extern void func_ov004_02232b48(void *);
extern int func_0205790c(void *, void *);
extern int func_02057a50(void *, const char *name);
extern void func_02055dc8(void *, int, int);
extern void func_ov004_02231c7c(void *);
extern int func_0200430c(void *);
extern void func_ov004_02231b38(void *);
extern void *data_ov004_022589fc;
extern char data_ov004_02255b50;
extern char data_ov004_02255b58;
extern char data_ov004_02255b60;
extern char data_ov004_02255b68;
extern int func_02054ec4(void *);
extern void func_02055124(void *);
extern int func_ov004_022324b4(void *);
extern void func_02056ffc(void *);
extern int func_ov004_0223c1e0(void);
extern void func_020042a0(void *, int);
extern void func_020042c0(void *, Vec *);
extern int func_ov004_02232270(void *);
extern int data_021d3124;

void *func_ov004_02233264(char *self);

void func_ov004_02233318(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x3544)))) {
        func_ov004_02233264((char *) conditionInput0);
    }
}

void *func_ov004_02233264(char *self)
{
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_02255ac8;
    func_02055210(self + 0x50);
    __cxa_vec_ctor(self + 0x108, 0x1, 0x20, (void *) func_ov004_022324f0, (void *) func_ov004_022324d8);
    func_ov004_022329e0(self + 0x128);
    func_ov004_02232754(self + 0x1228);
    func_ov004_0223248c(self + 0x3328);
    func_020324fc(self + 0x3460);
    func_ov004_022322fc(self + 0x34fc);
    *(void **) (self + 0x3534) = &data_0213efe8;
    *(char *) (self + 0x3520) = *(char *) (self + 0x3521) = *(char *) (self + 0x3540) = -1;
    return self;
}

void *func_ov004_022331e8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255ac8;
    func_ov004_022322ec(self + 0x34fc);
    func_020324c4(self + 0x3460);
    func_ov004_02232470(self + 0x3328);
    func_ov004_0223273c(self + 0x1228);
    func_ov004_022329c8(self + 0x128);
    __cxa_vec_cleanup(self + 0x108, 0x1, 0x20, ((void (*)(void *)) func_ov004_022324d8));
    func_020551e0(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_ov004_02233164(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255ac8;
    func_ov004_022322ec(self + 0x34fc);
    func_020324c4(self + 0x3460);
    func_ov004_02232470(self + 0x3328);
    func_ov004_0223273c(self + 0x1228);
    func_ov004_022329c8(self + 0x128);
    __cxa_vec_cleanup(self + 0x108, 0x1, 0x20, ((void (*)(void *)) func_ov004_022324d8));
    func_020551e0(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

int func_ov004_02233084(char *self)
{
    data_ov004_022589fc = self;
    func_ov004_022323d4(self + 0x3328);
    func_ov004_0223232c(self + 0x3460);
    func_ov004_0223228c(self + 0x34fc);
    func_ov004_02232edc(self);
    func_ov004_02232a94(self);
    func_ov004_02232a20(self, *(void **) (self + 0xac));
    func_ov004_02232a68(self);
    func_ov004_02232b48(self);
    self[0x3520] = func_0205790c(*(void **) (self + 0xac), &data_ov004_02255b50);
    self[0x3521] = func_0205790c(*(void **) (self + 0xac), &data_ov004_02255b58);
    self[0x3523] = func_0205790c(*(void **) (self + 0xac), &data_ov004_02255b60);
    self[0x3540] = func_02057a50(*(void **) (self + 0xac), (const char *) (&data_ov004_02255b68));
    func_02055dc8(self + 0x50, (int) func_ov004_02231b38, (int) self);
    func_ov004_02231c7c(self);
    func_0200430c(self + 0x3534);
    return 1;
}

int func_ov004_02232fdc(char *self)
{
    Vec v;
    char *p;
    if (func_02054ec4(self + 0x50) != 0) {
        func_02055124(self + 0x50);
    }
    p = self + 0x108;
    if (func_ov004_022324b4(p) != 0) {
        func_02056ffc(p);
        **(int **) (self + 0x120) = *(int *) (self + 0x110);
    }
    if (*(int *) (self + 0x3528) != 0) {
        int r = func_ov004_0223c1e0();
        if (r == 9 || r == 0x1d) {
            func_020042a0(self + 0x3534, 0x4d1);
        }
    }
    v = *(Vec *) (self + 0x3528);
    func_020042c0(self + 0x3534, &v);
    func_ov004_02232270(self + 0x34fc);
    data_021d3124 = 0;
    return 1;
}
