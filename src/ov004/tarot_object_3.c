/* tarot_object_3: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02230c7c @ 0x02230c7c, 0x1c bytes, Thumb
 * func_ov004_02230bf8 @ 0x02230bf8, 0x84 bytes, Thumb
 * func_ov004_02230b90 @ 0x02230b90, 0x68 bytes, Thumb
 * func_ov004_02230b20 @ 0x02230b20, 0x70 bytes, Thumb
 * func_ov004_022309f8 @ 0x022309f8, 0x128 bytes, Thumb
 */

extern int func_020edf70(unsigned int size);
extern void func_020565c8(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov004_0222c87c(void *);
extern void *func_020551e0(void *arg0);
extern void *func_02055210(void *arg0);
extern void func_ov004_0222c394(void *element);
extern void func_ov004_0222c398(void *arg0);
extern int func_ov004_0222c538(int arg0);
extern int func_ov004_0222c548(int arg0);
extern void *data_ov004_02255674;
extern void *func_020565b0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);
extern void func_02055050(void *);
extern void func_02055060(void *, int, int, int, int, int);
extern int func_02055140(void *, int);
extern int func_02055e00(void *);
extern void func_020563dc(void *, int);
extern void func_02056478(void *, int, int, int, int);
extern int func_0205650c(void *, int, int);
extern int func_ov004_0222c3a4(void *, int);
extern int func_ov004_0222c3c4(void *, int);
extern int func_ov004_0222c600(void *, void *, void *);
extern void func_ov004_02230438(void *, int, void *, void *);
extern int func_ov004_0223080c(void *, int);
extern void *data_021c9b24;
extern void *data_ov004_022556dc;
extern void *data_ov004_022556f4;
extern void *data_ov004_02255710;
extern void *data_ov004_02255728;
extern void *data_ov004_02255744;
extern void *data_ov004_0225575c;
extern void *data_ov004_02255778;
extern void *data_ov004_02255790;
extern void *data_ov004_02258870;

void *func_ov004_02230bf8(char *self);

void func_ov004_02230c7c(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x6dc)))) {
        func_ov004_02230bf8((char *) conditionInput0);
    }
}

void *func_ov004_02230bf8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    *(void **) (self) = &data_ov004_02255674;
    __cxa_vec_ctor(self + 0x290, 0x3, 0xb8, ((void (*)(void *)) func_02055210), ((void (*)(void *)) func_020551e0));
    __cxa_vec_ctor(self + 0x4b8, 0x3, 0xa4, ((void (*)(void *)) func_ov004_0222c548),
                   ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_ctor(self + 0x6a4, 0x3, 0x4, ((void (*)(void *)) func_ov004_0222c398), ((void (*)(void *)) func_ov004_0222c394));
    func_020565c8(self + 0x6b4);
    return self;
}

void *func_ov004_02230b90(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255674;
    func_020565b0(self + 0x6b4);
    __cxa_vec_cleanup(self + 0x6a4, 0x3, 0x4, ((void (*)(void *)) func_ov004_0222c394));
    __cxa_vec_cleanup(self + 0x4b8, 0x3, 0xa4, ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_cleanup(self + 0x290, 0x3, 0xb8, ((void (*)(void *)) func_020551e0));
    func_ov004_0222c7a0(self);
    return self;
}

void *func_ov004_02230b20(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255674;
    func_020565b0(self + 0x6b4);
    __cxa_vec_cleanup(self + 0x6a4, 0x3, 0x4, ((void (*)(void *)) func_ov004_0222c394));
    __cxa_vec_cleanup(self + 0x4b8, 0x3, 0xa4, ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_cleanup(self + 0x290, 0x3, 0xb8, ((void (*)(void *)) func_020551e0));
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}

int func_ov004_022309f8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) ((char *) &data_ov004_02258870) = self;
    func_ov004_0222c600(self, &data_ov004_022556dc, &data_ov004_022556f4);
    func_ov004_02230438(self, 0x0, &data_ov004_02255710, &data_ov004_02255728);
    func_ov004_02230438(self, 0x1, &data_ov004_02255744, &data_ov004_0225575c);
    func_ov004_02230438(self, 0x2, &data_ov004_02255778, &data_ov004_02255790);
    if (func_ov004_0222c3c4(self + 0x600, 0x0) != 0x0 &&
        func_02055140(self + 0x400, *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02055060(self + 0x400, func_ov004_0222c3c4(self + 0x600, 0x0), 0x1, 0x1000, 0x0, 0x0);
        func_02055050(self + 0x400);
        *(void **) (self + 0x4ac) = 0x0;
    }
    if (func_0205650c(self + 0x6b4, *(int *) (self + 0x3a4), *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02056478(self + 0x6b4, func_ov004_0222c3a4(self + 0x55c, 0x0), 0x1, 0x1000, 0x0);
        func_020563dc(self + 0x6b4, func_02055e00(self + 0x348));
        *(void **) (self + 0x6c4) = 0x0;
    }
    func_ov004_0223080c(self, 0x0);
    return 0x1;
}
