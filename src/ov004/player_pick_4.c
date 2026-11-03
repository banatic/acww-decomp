/* player_pick_4: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02245fd8 @ 0x02245fd8, 0x1c bytes, Thumb
 * func_ov004_02245f70 @ 0x02245f70, 0x68 bytes, Thumb
 * func_ov004_02245f28 @ 0x02245f28, 0x48 bytes, Thumb
 * func_ov004_02245ed8 @ 0x02245ed8, 0x50 bytes, Thumb
 * func_ov004_02245e18 @ 0x02245e18, 0xc0 bytes, Thumb
 * func_ov004_02245db0 @ 0x02245db0, 0x68 bytes, Thumb
 */

extern int func_020edf70(unsigned int size);
extern void *func_0208e878(void *, int);
extern void *func_02094fd4(void *);
extern void *func_020ee660(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_0208e408(void *arg0);
extern void *func_0208e438(void *arg0);
extern void *data_020da13c;
extern void *data_ov004_0225684c;
extern void *func_0208e84c(void *);
extern void *func_02094fbc(void *);
extern void func_020ee62c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void func_020edf54(void *);
extern void func_0203e334(void);
extern char data_021dc7a8[];
extern void *func_02098844(void *, int);
extern int func_02099a28(void *);
extern void func_0208e2ac(void *, int);
extern int func_020b4980(void *, void *, int);
extern int func_0209f150(void *, unsigned int);
extern int func_0208ffac(void);
extern void func_ov004_02245cf4(void *, int);
extern void func_0209e474(void *);
extern void func_0203e328(void);
extern void func_0208e2a4(void *a);
extern int func_0206f78c(void);
extern void func_0206f74c(void);
extern int func_0209e3ac(void *a, void *b, int c);
extern void func_0206f774(void);
extern void func_0206f780(void);

void *func_ov004_02245f70(char *self);

void func_ov004_02245fd8(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x358)))) {
        func_ov004_02245f70((char *) conditionInput0);
    }
}

void *func_ov004_02245f70(char *self)
{
    // DECLS
    // ENDDECLS
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_0225684c;
    func_0208e878(self + 0x50, 0x1);
    __cxa_vec_ctor(self + 0x9c, 0x5, 0x80, ((void (*)(void *)) func_0208e438), ((void (*)(void *)) func_0208e408));
    *(void **) (self + 0x328) = 0x0;
    *(void **) (self + 0x32c) = 0x0;
    func_02094fd4(self + 0x338);
    return self;
}

void *func_ov004_02245f28(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0225684c;
    func_02094fbc(self + 0x338);
    __cxa_vec_cleanup(self + 0x9c, 0x5, 0x80, ((void (*)(void *)) func_0208e408));
    func_0208e84c(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_ov004_02245ed8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0225684c;
    func_02094fbc(self + 0x338);
    __cxa_vec_cleanup(self + 0x9c, 0x5, 0x80, ((void (*)(void *)) func_0208e408));
    func_0208e84c(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

int func_ov004_02245e18(char *self)
{
    unsigned char i;
    unsigned char flag;
    char *g;
    void *entry;
    func_0203e334();
    g = data_021dc7a8;
    for (i = 0; i < 4; ++i) {
        entry = func_02098844(g + 0x14, i);
        if (entry && func_02099a28(entry)) {
            self[0x31c] = i;
            break;
        }
    }
    for (i = 0; i < 5; ++i) {
        func_0208e2ac(self + 0x9c + i * 0x80, i);
    }
    flag = 0x81;
    func_020b4980(self + 0x338, &flag, 0);
    if (!func_0209f150(g, 0)) {
        func_ov004_02245cf4(self, 0);
    } else if (func_0208ffac()) {
        func_ov004_02245cf4(self, 2);
    } else {
        func_ov004_02245cf4(self, 1);
    }
    self[0x31d] = 0;
    func_0209e474(self + 0x328);
    return 1;
}

int func_ov004_02245db0(void *self)
{
    unsigned char i;
    int b[2];
    char *p;

    func_0203e328();
    i = 0;
    p = (char *) self + 0x9c;
    do {
        func_0208e2a4(p + (i << 7));
        i++;
    } while (i < 5);
    if (func_0206f78c() != 0) {
        func_0206f74c();
        b[0] = 0;
        b[1] = 0;
        func_0209e474(b);
        if (func_0209e3ac((char *) self + 0x328, b, 0x3f) == -1) {
            func_0206f774();
        } else {
            func_0206f780();
        }
    }
    return 1;
}
