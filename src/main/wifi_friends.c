/* wifi_friends: 35 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02077ec0 @ 0x02077ec0, 0x2 bytes, Thumb
 * func_02077ebc @ 0x02077ebc, 0x2 bytes, Thumb
 * func_02077ea4 @ 0x02077ea4, 0x16 bytes, Thumb
 * func_02077e74 @ 0x02077e74, 0x2e bytes, Thumb
 * func_02077e68 @ 0x02077e68, 0xc bytes, Thumb
 * func_02077e50 @ 0x02077e50, 0x18 bytes, Thumb
 * func_02077e38 @ 0x02077e38, 0x18 bytes, Thumb
 * func_02077dd4 @ 0x02077dd4, 0x64 bytes, Thumb
 * func_02077d84 @ 0x02077d84, 0x4e bytes, Thumb
 * func_02077d6c @ 0x02077d6c, 0x18 bytes, Thumb
 * func_02077d68 @ 0x02077d68, 0x2 bytes, Thumb
 * func_02077d40 @ 0x02077d40, 0x28 bytes, Thumb
 * func_02077d24 @ 0x02077d24, 0x1c bytes, Thumb
 * func_02077d04 @ 0x02077d04, 0x1e bytes, Thumb
 * func_02077d00 @ 0x02077d00, 0x2 bytes, Thumb
 * func_02077cb4 @ 0x02077cb4, 0x4c bytes, Thumb
 * func_02077ca8 @ 0x02077ca8, 0xc bytes, Thumb
 * func_02077c9c @ 0x02077c9c, 0xc bytes, Thumb
 * func_02077c8c @ 0x02077c8c, 0x10 bytes, Thumb
 * func_02077c7c @ 0x02077c7c, 0x10 bytes, Thumb
 * func_02077c64 @ 0x02077c64, 0x16 bytes, Thumb
 * func_02077c40 @ 0x02077c40, 0x22 bytes, Thumb
 * func_02077c3c @ 0x02077c3c, 0x2 bytes, Thumb
 * func_02077c38 @ 0x02077c38, 0x4 bytes, Thumb
 * func_02077c34 @ 0x02077c34, 0x4 bytes, Thumb
 * func_02077c20 @ 0x02077c20, 0x12 bytes, Thumb
 * func_02077c0c @ 0x02077c0c, 0x12 bytes, Thumb
 * func_02077be8 @ 0x02077be8, 0x24 bytes, Thumb
 * func_02077be0 @ 0x02077be0, 0x8 bytes, Thumb
 * func_02077bd8 @ 0x02077bd8, 0x8 bytes, Thumb
 * func_02077bd0 @ 0x02077bd0, 0x8 bytes, Thumb
 * func_02077bcc @ 0x02077bcc, 0x2 bytes, Thumb
 * func_02077bc8 @ 0x02077bc8, 0x4 bytes, Thumb
 * func_02077bc0 @ 0x02077bc0, 0x6 bytes, Thumb
 * func_02077bb8 @ 0x02077bb8, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned int a, b, c;
} Triple;

typedef struct {
    char data[0x24];
} UnkStruct_02077cb4;

typedef struct {
    unsigned char pad_00[76];
    unsigned short unk_4C;
} UnkStruct_02077bc0;

typedef struct {
    unsigned char pad_00[76];
    unsigned short unk_4C;
} UnkStruct_02077bb8;

extern void MI_CpuCopy8(void *a, void *b, int c);
extern unsigned int func_020eb058(void *p1, Triple *p2);
extern void MI_CpuFill8(void *dest, int val, unsigned int count);
extern int func_020eb04c(void *friend_data);
extern int func_020eb628(int, void *, int, int);
extern long long func_020eb61c(int a);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020eb6e8(void *, unsigned int);
extern void func_020eb6a0(void *, int);
extern unsigned long long func_020eb694(const void *data);
extern int func_020eb6ac(int data);
extern int func_020eb064(void *data);

void *func_02077c8c(void *arg);
int func_02077c7c(int a);
void *func_02077c64(void *a, void *b);
void func_02077c40(void *param);
void *func_02077c3c(void *object);

void func_02077ec0(void *buffer) {}

void func_02077ebc(void *buffer) {}

void *func_02077ea4(void *a, void *b)
{
    MI_CpuCopy8(b, a, 12);
    return a;
}

unsigned int func_02077e74(void *p1, Triple *p2)
{
    Triple local;
    unsigned int ret;

    local = *p2;
    ret = func_020eb058(p1, &local);
    func_02077ebc(&local);

    return ret;
}

void func_02077e68(void *ptr)
{
    MI_CpuFill8(ptr, 0, 12);
}

int func_02077e50(void *friend_data)
{
    int result;
    if (func_020eb04c(friend_data) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_02077e38(void *friend_data)
{
    int result;
    if (func_020eb04c(friend_data) == 2) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_02077dd4(void *out, const unsigned char *s, int a2)
{
    unsigned long long v;
    unsigned long long i;
    unsigned char buf[0xc];
    v = 0;
    for (i = 0; i < 12; i++) {
        v = v * 10 + (unsigned int) s[i];
    }
    if (func_020eb628(a2, buf, (int) v, (int) (v >> 32)) == 0) {
        return 0;
    }
    MI_CpuCopy8((void *) buf, out, 0xc);
    return 1;
}

int func_02077d84(int p0, char *p1)
{
    if (func_020eb04c((void *) p0) != 2) {
        return 0;
    }
    {
        unsigned long long v = func_020eb61c(p0);
        int i;
        for (i = 11; i >= 0; i--) {
            p1[i] = v % 10;
            v /= 10;
        }
    }
    return 1;
}

int func_02077d6c(void *friend_data)
{
    if (func_02077e38(friend_data) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void *func_02077d68(void *object)
{
    return object;
}

void *func_02077d40(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 0x20, 0x24, (((void (*)(void *)) func_02077c8c)),
                   (((void (*)(void *))(int (*)(void *)) func_02077c7c)));
    return arg;
}

int func_02077d24(int a)
{
    __cxa_vec_cleanup((void *) (a), 0x20, 0x24, (((void (*)(void *))(int (*)(void *)) func_02077c7c)));
    return a;
}

void func_02077d04(void *param)
{
    int i;
    for (i = 0; i < 0x20; i++) {
        func_02077c40((char *) param + i * 0x24);
    }
}

void *func_02077d00(void *entries)
{
    return entries;
}

void func_02077cb4(void *entries)
{
    int i;
    int k;
    UnkStruct_02077cb4 *base;

    base = func_02077d00(entries);

    for (i = k = 0; i < 32; i++) {
        UnkStruct_02077cb4 *cur = base + i;

        if (func_02077e50((void *) (int) func_02077c3c((void *) cur)) != 0) {
            if (i != k) {
                func_02077c64((void *) (base + k), (void *) cur);
                func_02077c40((void *) cur);
            }
            k++;
        }
    }
}

void func_02077ca8(unsigned short *r0, unsigned short r1)
{
    r0[0x240] = r1;
}

unsigned short func_02077c9c(unsigned short *r0)
{
    return r0[0x240];
}

void *func_02077c8c(void *arg)
{
    func_02077ec0(arg);
    return arg;
}

int func_02077c7c(int a)
{
    func_02077ebc((void *) a);
    return a;
}

void *func_02077c64(void *a, void *b)
{
    MI_CpuCopy8(b, (void *) a, 0x24);
    return a;
}

void func_02077c40(void *param)
{
    extern void func_02077e68(void *);
    extern void func_02051bf8(void *, int);

    func_02077e68(param);
    func_02051bf8((char *) param + 0xc, 6);
    func_02051bf8((char *) param + 0x18, 6);
}

void *func_02077c3c(void *object)
{
    return object;
}

int func_02077c38(int p0)
{
    return ((int) (p0) + (12));
}

int func_02077c34(int p0)
{
    return ((int) (p0) + (24));
}

void *func_02077c20(void *arg)
{
    func_02077ec0((char *) arg + 0x40);
    return arg;
}

void *func_02077c0c(void *ptr)
{
    func_02077ebc((char *) ptr + 0x40);
    return ptr;
}

void func_02077be8(unsigned char *param)
{
    func_020eb6e8(param, 0x41444d4b);
    func_020eb6a0(param, (int) func_02077d68(param + 0x40));
}

unsigned long long func_02077be0(const void *data)
{
    return func_020eb694(data);
}

int func_02077bd8(int data)
{
    return func_020eb6ac(data);
}

int func_02077bd0(void *data)
{
    return func_020eb064(data);
}

void *func_02077bcc(void *record)
{
    return record;
}

int func_02077bc8(int p0)
{
    return ((int) (p0) + (64));
}

void func_02077bc0(UnkStruct_02077bc0 *p, unsigned short v)
{
    p->unk_4C = v;
}

unsigned short func_02077bb8(UnkStruct_02077bb8 *p)
{
    return p->unk_4C;
}
