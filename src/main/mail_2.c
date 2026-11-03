/* mail_2: 23 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02097c90 @ 0x02097c90, 0x2c bytes, Thumb
 * func_02097c74 @ 0x02097c74, 0x1a bytes, Thumb
 * func_02097c48 @ 0x02097c48, 0x2c bytes, Thumb
 * func_02097c44 @ 0x02097c44, 0x4 bytes, Thumb
 * func_02097c40 @ 0x02097c40, 0x4 bytes, Thumb
 * func_02097c38 @ 0x02097c38, 0x8 bytes, Thumb
 * func_02097c24 @ 0x02097c24, 0x12 bytes, Thumb
 * func_02097c14 @ 0x02097c14, 0xe bytes, Thumb
 * func_02097c04 @ 0x02097c04, 0xe bytes, Thumb
 * func_02097bdc @ 0x02097bdc, 0x28 bytes, Thumb
 * func_02097bbc @ 0x02097bbc, 0x20 bytes, Thumb
 * func_02097b24 @ 0x02097b24, 0x98 bytes, Thumb
 * func_02097ad0 @ 0x02097ad0, 0x54 bytes, Thumb
 * func_02097a74 @ 0x02097a74, 0x5c bytes, Thumb
 * func_02097a54 @ 0x02097a54, 0x20 bytes, Thumb
 * func_02097a44 @ 0x02097a44, 0x10 bytes, Thumb
 * func_020979f0 @ 0x020979f0, 0x54 bytes, Thumb
 * func_020979ac @ 0x020979ac, 0x42 bytes, Thumb
 * func_02097958 @ 0x02097958, 0x54 bytes, Thumb
 * func_02097900 @ 0x02097900, 0x58 bytes, Thumb
 * func_020978bc @ 0x020978bc, 0x42 bytes, Thumb
 * func_02097890 @ 0x02097890, 0x2c bytes, Thumb
 * func_0209788c @ 0x0209788c, 0x2 bytes, Thumb
 */

struct UnkStruct_02097c74 {
    unsigned char pad_00[0x50];
    unsigned short unk_50;
};

struct UnkStruct_02097bbc {
    volatile unsigned int unk_00;
};

typedef struct {
    char pad_00[0x0a04];
} BigStruct;

typedef struct Entry Entry;

struct Entry {
    char pad_00[0x100];
};

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *obj);
extern int func_020b65d0(void);
extern void func_020976a4(void);
extern void func_020ee62c(int *p);
extern void func_020edf54(int *p);
extern unsigned char data_020da13c[];
extern unsigned char data_020e30b8[];
extern void *func_02097ff0(void *addr, int flag);
extern int func_02065ec0(void *ptr);
extern void func_02066650(void *ptr);
extern unsigned char data_021f20fc[];
extern int func_020984e8(void);
extern int func_0209985c(int);
extern void *func_02098090(void *, int);
extern BigStruct data_021ef8ec[];
extern int func_02066830(unsigned char *p, int a);
extern void func_020664e0(unsigned char *p);
extern int func_0207a51c(void *arg1, void *arg2);
extern unsigned char data_021e5a2c[];
extern char data_021dc7bc;
extern void *func_02065f70(void *);
extern void *func_0209529c(char *buf);
extern void func_02095208(char *buf, void *p);
extern int func_0209871c(char *global, char *buf);
extern int func_020988d8(unsigned int);
extern int func_0209526c(char *buf);
int func_02065f64(void *);
int func_02003780(char *p);
void func_020037ac(char *p, int v);
int func_0207cf14(int base, char *p);
int func_0207cf74(unsigned int);
int func_02003750(char *p);

void func_02097c38(int receiver);
int func_02097c24(unsigned short *param0, unsigned int param1);
void func_02097c14(unsigned char *ptr, unsigned int val);
void func_02097c04(unsigned short *ptr, unsigned short mask);
int func_02097a74(int a0, int a1, int a2);
void func_02097a44(void *arg0);
int func_02097958(void *object);
int func_02097900(void *argument0);
int func_020978bc(unsigned char *base, int n);

void *func_02097c90(void)
{
    void *p = func_020edf70(0x54);
    if (p) {
        func_020ee660(p);
        ((volatile unsigned int *) p)[0] = (unsigned int) ((unsigned int *) data_020da13c);
        ((volatile unsigned int *) p)[0] = (unsigned int) ((unsigned int *) data_020e30b8);
    }
    return p;
}

int func_02097c74(struct UnkStruct_02097c74 *s)
{
    s->unk_50 = 0;
    func_02097c14((unsigned char *) s, 1);
    return 1;
}

int func_02097c48(int arg0)
{
    int res1;
    res1 = func_02097c24((unsigned short *) arg0, 1);
    if (res1 != 0) {
        int res2;
        res2 = func_020b65d0();
        if (res2 != 0) {
            func_02097c38(arg0);
        }
        func_02097c04((unsigned short *) arg0, 1);
    }
    return 1;
}

int func_02097c44(void)
{
    return 1;
}

int func_02097c40(void)
{
    return 1;
}

void func_02097c38(int receiver)
{
    func_020976a4();
}

int func_02097c24(unsigned short *param0, unsigned int param1)
{
    return (param0[0x28] & param1) ? 1 : 0;
}

void func_02097c14(unsigned char *ptr, unsigned int val)
{
    *(unsigned short *) (ptr + 0x50) |= val;
}

void func_02097c04(unsigned short *ptr, unsigned short mask)
{
    ptr[0x28] &= ~mask;
}

int *func_02097bdc(int *p)
{
    *p = (unsigned int) data_020e30b8;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

void *func_02097bbc(struct UnkStruct_02097bbc *self)
{
    self->unk_00 = (unsigned int) data_020e30b8;
    self->unk_00 = (unsigned int) data_020da13c;
    func_020ee62c((int *) self);
    return self;
}

int func_02097b24(void)
{
    void *base;
    int count;
    int i;
    int local1 = 0;
    int local2 = 0;

    base = func_02097ff0((void *) data_021f20fc, 0);
    count = func_020978bc((unsigned char *) base, 0xa);

    for (i = 0; i < count; i++) {
        void *ptr = (char *) base + (i << 8);
        if (func_02065ec0(ptr) != 0) {
            int val = func_02097958(ptr);
            if (val == -2) {
                func_02066650(ptr);
            } else {
                if (val == ~local2) {
                    goto then_block;
                }
                // else block
                if (func_02097a74((int) ptr, val, local1) != 0) {
                    func_02066650(ptr);
                }
                goto end_block;
            then_block:
                // then block
                if (func_02097900(ptr) < 0) {
                    func_02066650(ptr);
                } else {
                    func_02097a44(ptr);
                    func_02066650(ptr);
                }
            end_block:;
            }
        }
    }

    return func_020978bc((unsigned char *) base, 0xa);
}

int func_02097ad0(int a)
{
    BigStruct *p;
    int i;

    if (a == -1) {
        a = func_0209985c((int) func_020984e8());
    }

    p = func_02098090(&data_021ef8ec[a], 0);

    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p) == 0) {
            return 0;
        }
        p = (BigStruct *) ((char *) p + 0x100);
    }

    return 1;
}

int func_02097a74(int a0, int a1, int a2)
{
    unsigned char *p;
    int i;

    p = (unsigned char *) func_02098090((void *) (&((unsigned char *) data_021ef8ec)[a1 * 0xa04]), 0);
    for (i = 0; i < 10; i++) {
        if (func_02065ec0((void *) p) == 0) {
            func_02066830(p, a0);
            if (a2 != 0) {
                func_020664e0(p);
            }
            return 1;
        }
        p += 0x100;
    }
    return 0;
}

int func_02097a54(int arg0)
{
    int val;
    int val2;

    val = func_02097958((void *) arg0);
    if (val < 0) {
        val2 = 0;
    } else {
        val2 = func_02097a74(arg0, val, 0);
    }
    return val2;
}

void func_02097a44(void *arg0)
{
    func_0207a51c((void *) data_021e5a2c, arg0);
}

int func_020979f0(int a, int b)
{
    int i;
    Entry *p;

    p = (Entry *) func_02097ff0((void *) (((Entry *) data_021f20fc)), 0);
    for (i = 0; i < 10; p++, i++) {
        if (func_02065ec0((void *) p) != 0) {
            continue;
        }
        func_02066830((unsigned char *) p, a);
        if (b != 0) {
            func_020664e0((unsigned char *) p);
        }
        return 1;
    }
    return 0;
}

int func_020979ac(int param)
{
    int ret1 = func_02097958((void *) param);
    if (ret1 == -2) {
        return 0;
    }
    if (ret1 == -1) {
        int ret2 = func_02097900((void *) param);
        if (ret2 == -2) {
            return 0;
        }
        if (ret2 == -1) {
            return 0;
        }
    }
    return 1;
}

int func_02097958(void *object)
{
    char buf[0x20];
    void *p;
    int result;

    p = func_02065f70(object);
    if (p == 0) {
        return -1;
    }

    func_0209529c(buf);
    func_02095208(buf, p);
    result = func_0209871c(&data_021dc7bc, buf);
    if (func_020988d8(result) != 0) {
        func_0209526c(buf);
        return result;
    } else {
        func_0209526c(buf);
        return -2;
    }
}

int func_02097900(void *argument0)
{
    int result;
    int base;
    char local[20];

    base = (int) ((int *) data_021e5a2c);
    result = func_02065f64((void *) argument0);
    if (result == 0) {
        return -1;
    }

    func_02003780(local);
    func_020037ac(local, result);

    result = func_0207cf14(base, local);
    if (func_0207cf74(result) != 0) {
        func_02003750(local);
        return result;
    } else {
        func_02003750(local);
        return -2;
    }
}

int func_020978bc(unsigned char *base, int n)
{
    int i;
    int cnt;
    unsigned char *p;

    i = 0;
    cnt = i;
    for (; i < n; i++) {
        p = base + (i << 8);
        if (func_02065ec0((void *) p)) {
            if (i != cnt) {
                func_02066830(base + (cnt << 8), (int) p);
                func_02066650((void *) p);
            }
            cnt++;
        }
    }
    return cnt;
}

int func_02097890(char *base, int n)
{
    int i;
    int count;
    count = 0;
    i = count;
    while (i < n) {
        if (func_02065ec0((void *) (base + (i << 8))) != 0) {
            count++;
        }
        i++;
    }
    return count;
}

void func_0209788c(void) {}
