/* room_manager_3: 10 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223d5ec @ 0x0223d5ec, 0x1c bytes, Thumb
 * func_ov004_0223d5b0 @ 0x0223d5b0, 0x3c bytes, Thumb
 * func_ov004_0223d570 @ 0x0223d570, 0x40 bytes, Thumb
 * func_ov004_0223d52c @ 0x0223d52c, 0x44 bytes, Thumb
 * func_ov004_0223d434 @ 0x0223d434, 0xf8 bytes, Thumb
 * func_ov004_0223d3b4 @ 0x0223d3b4, 0x80 bytes, Thumb
 * func_ov004_0223d3b0 @ 0x0223d3b0, 0x4 bytes, Thumb
 * func_ov004_0223d354 @ 0x0223d354, 0x5c bytes, Thumb
 * func_ov004_0223d348 @ 0x0223d348, 0xc bytes, Thumb
 * func_ov004_0223d33c @ 0x0223d33c, 0xc bytes, Thumb
 */

extern int func_020edf70(unsigned int size);
extern void *func_020ee660(void *);
extern void *func_ov004_0223ab98(void *);
extern void *func_ov004_0223b18c(void *);
extern void func_ov004_0223d020(void *);
extern void *data_020da13c;
extern void *data_ov004_02256018;
extern void func_020ee62c(void *);
extern void *func_ov004_0223ab7c(void *);
extern void *func_ov004_0223b174(void *);
extern int func_ov004_0223d010(void *);
extern void func_020edf54(void *);
extern int func_020b67d4(void);
extern int func_020b6680(void);
extern int func_ov004_0223c10c(void);
extern unsigned int func_ov004_0223c130(void);
extern int func_ov004_0223cec4(void *, int);
extern void *func_ov004_0223cd50(void);
extern void func_ov004_0223cd04(void *);
extern void *func_ov004_0223cb10(void);
extern void func_ov004_0223c7b8(void *);
extern int func_020b66d8(void);
extern int func_0209d180(void *object, unsigned int count, int a, int b, int c, int (*allocate)(int, int),
                         void (*cleanup)(void), void *context);
extern void func_ov004_0223c108(void *receiver);
extern void func_ov004_0223aad4(void *);
extern void func_ov004_0223b158(void *);
extern void *func_ov004_0223d03c(void);
extern void func_ov004_0223d248(void *);
extern void func_ov004_0223c080(void *receiver);
extern int func_0205ca98(int size, int heapword);
extern void func_0205ca7c(void);
extern char data_ov004_022595b8;
extern void *data_ov004_022595c0;
extern char data_ov004_02256188;
extern void func_ov004_0223cfec(void *);
extern void func_ov004_0223cfd4(void *);
extern int func_02050974(void *);
extern int func_020b67ac(void);
extern int func_020b6788(void);
extern void func_ov004_0223a9e0(void *);
extern void func_ov004_0223bdac(void *);
extern void func_ov004_0223a9b8(void *);
extern void func_ov004_0223bf40(void *receiver);
extern void func_ov004_0223bfe0(void *receiver);
extern unsigned short data_ov004_022595bc;
extern char data_021c8188;
extern void func_ov004_0223cfcc(void *);
extern void func_ov004_0223b13c(void *);
extern void func_ov004_0223a818(void *);
extern void func_ov004_0223d200(char *);
extern int func_0209d138(void *);
extern void func_ov004_0223cea8(void *);
extern char data_ov004_02259698[];
extern char data_ov004_022595c4[];
extern unsigned char data_ov004_022595b4;

void *func_ov004_0223d5b0(char *self);

void func_ov004_0223d5ec(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x2b4)))) {
        func_ov004_0223d5b0((char *) conditionInput0);
    }
}

void *func_ov004_0223d5b0(char *self)
{
    // DECLS
    // ENDDECLS
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_02256018;
    func_ov004_0223d020(self + 0x50);
    func_ov004_0223ab98(self + 0x64);
    func_ov004_0223b18c(self + 0x1c4);
    return self;
}

void *func_ov004_0223d570(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02256018;
    func_ov004_0223b174(self + 0x1c4);
    func_ov004_0223ab7c(self + 0x64);
    func_ov004_0223d010(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_ov004_0223d52c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02256018;
    func_ov004_0223b174(self + 0x1c4);
    func_ov004_0223ab7c(self + 0x64);
    func_ov004_0223d010(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

int func_ov004_0223d434(char *self)
{
    int sz;
    register unsigned int count;
    if (func_020b67d4() != 0 || func_020b6680() != 0) {
        data_ov004_022595b8 = 1;
    }
    self[0x2a9] = 1;
    self[0x2a8] = 0;
    *(int *) (self + 0x2ac) = 0;
    self[0x2b0] = 0;
    (*(char *) &data_ov004_022595b4) = func_ov004_0223c10c();
    func_ov004_0223cec4(((char *) data_ov004_022595c4), func_ov004_0223c130());
    data_ov004_022595c0 = self;
    func_ov004_0223cd04(func_ov004_0223cd50());
    func_ov004_0223c7b8(func_ov004_0223cb10());
    sz = 0x1cc4;
    if (func_020b66d8() != 0) {
        sz = 0x1c00;
    }
    count = func_ov004_0223c130();
    func_0209d180(((char *) data_ov004_02259698), count, 0x2000, 0x80, sz, func_0205ca98, func_0205ca7c, &data_ov004_02256188);
    func_ov004_0223c108(self);
    if (func_ov004_0223c130() > 1) {
        func_ov004_0223aad4(self + 0x64);
    }
    func_ov004_0223b158(self + 0x1c4);
    func_ov004_0223d248(func_ov004_0223d03c());
    func_ov004_0223c080(self);
    return 1;
}

int func_ov004_0223d3b4(char *self)
{
    func_ov004_0223cfec(self + 0x50);
    func_ov004_0223cfd4(self + 0x50);
    data_ov004_022595bc = (data_ov004_022595bc + 1) % 0x28;
    if (func_ov004_0223c130() > 1 && func_02050974(&data_021c8188) == 4 && func_020b67ac() == 0 && func_020b6788() == 0) {
        func_ov004_0223a9e0(self + 0x64);
        func_ov004_0223bdac(self);
        func_ov004_0223a9b8(self + 0x64);
    }
    func_ov004_0223bf40(self);
    func_ov004_0223bfe0(self);
    func_ov004_0223c7b8(func_ov004_0223cb10());
    return 1;
}

int func_ov004_0223d3b0(void)
{
    return 1;
}

int func_ov004_0223d354(char *self)
{
    func_ov004_0223cfcc(self + 0x50);
    func_ov004_0223b13c(self + 0x1c4);
    if (func_ov004_0223c130() > 1) {
        func_ov004_0223a818(self + 0x64);
    }
    func_ov004_0223d200((char *) func_ov004_0223d03c());
    func_0209d138(data_ov004_02259698);
    data_ov004_022595c0 = 0;
    func_ov004_0223c7b8((void *) ((char *) func_ov004_0223cb10()));
    func_ov004_0223cea8(data_ov004_022595c4);
    return 1;
}

unsigned char func_ov004_0223d348(void)
{
    return data_ov004_022595b4;
}

void func_ov004_0223d33c(void)
{
    data_ov004_022595b4 = 1;
}
