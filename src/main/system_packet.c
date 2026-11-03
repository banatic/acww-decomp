/* system_packet: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02075484 @ 0x02075484, 0x2c bytes, Thumb
 * func_02075450 @ 0x02075450, 0x34 bytes, Thumb
 * func_02075448 @ 0x02075448, 0x8 bytes, Thumb
 * func_02075404 @ 0x02075404, 0x44 bytes, Thumb
 * func_020753a8 @ 0x020753a8, 0x5c bytes, Thumb
 * func_02075380 @ 0x02075380, 0x26 bytes, Thumb
 * func_02075358 @ 0x02075358, 0x26 bytes, Thumb
 * func_02075334 @ 0x02075334, 0x24 bytes, Thumb
 * func_0207530c @ 0x0207530c, 0x26 bytes, Thumb
 * func_02075300 @ 0x02075300, 0xc bytes, Thumb
 * func_020752a8 @ 0x020752a8, 0x58 bytes, Thumb
 * func_02075278 @ 0x02075278, 0x2e bytes, Thumb
 * func_02075254 @ 0x02075254, 0x24 bytes, Thumb
 */

typedef struct UnkStruct_020752a8 {
    char pad_00[0x68];
    void *unk_68;
} UnkStruct_020752a8;

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1274(int, int);
extern char *func_020738e4(int);
extern int data_020ccf94;
extern void func_02077638(unsigned char *, unsigned int);
extern int func_020ec260(void);
extern void func_020a1238(void *, int, unsigned char);
extern int func_020a7880(unsigned char *);
extern void func_020a7830(unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned int *);
extern void func_020a7394(unsigned int, unsigned char, unsigned char, unsigned char, unsigned int);
extern int func_020a7870(unsigned char *);
extern void func_020a1200(int, int, int);
extern void func_020a11f8(int a, int b, int c);
extern void func_020a126c(int, int);
extern void func_020a1208(int a0, int a1, int a2);
extern void func_020a11e0(int player);
extern void *func_020a245c(int);
extern void func_020962a4(void *, void *);
extern char *func_020984e8(void);
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern int func_020989e0(int object);
extern void func_020a11b8(int, int);

void func_02075484(unsigned char *payload, unsigned int length, int player)
{
    int temp;
    int result;

    temp = func_020b65c4();
    if (temp == 0xd || func_020b65c4() == 0x2f) {
        result = func_020a132c();
        if (result != 0) {
            result = func_020a132c();
            func_020a1274(result, 1);
        }
    }
}

void func_02075450(unsigned char *payload, unsigned int length, int player)
{
    int local;
    char *ret;

    MI_CpuCopy8((const void *) payload, (void *) (&local), 4);
    ret = func_020738e4(data_020ccf94);
    MI_CpuCopy8((const void *) (payload + 4), (void *) (ret + local), length - 4);
}

void func_02075448(unsigned char *payload, unsigned int length, int player)
{
    func_02077638((unsigned char *) payload, (unsigned int) length);
}

void func_02075404(unsigned char *payload, unsigned int length, int player)
{
    if (func_020b65c4() == 0x2e || func_020b65c4() == 9) {
        void *p = (void *) func_020a132c();
        if (p != 0) {
            if (func_020ec260() == 0) {
                func_020a1238(p, player, *payload);
            } else {
                func_020a1238(p, 0, *payload);
            }
        }
    }
}

void func_020753a8(unsigned char *payload, unsigned int length, int player)
{
    unsigned int i;
    unsigned char buf[8];
    unsigned int word;

    i = 0;
    do {
        func_020a7880(&buf[3]);
        MI_CpuCopy8((const void *) payload, (void *) (&buf[3]), 2);
        func_020a7830(&buf[3], &buf[0], &buf[1], &buf[2], &word);
        func_020a7394(i, buf[0], buf[1], buf[2], word);
        payload += 2;
        func_020a7870(&buf[3]);
        i++;
    } while (i < 4);
}

void func_02075380(unsigned char *payload, unsigned int length, int player)
{
    int r4 = player;
    int result;

    result = func_020b65c4();
    if (result == 0x2e) {
        if (func_020a132c() != 0) {
            func_020a1200(func_020a132c(), r4, 1);
        }
    }
}

void func_02075358(unsigned char *payload, unsigned int length, int player)
{
    int ret1;
    int ret2;
    int ret3;

    ret1 = func_020b65c4();
    if (ret1 == 0x2e) {
        ret2 = func_020a132c();
        if (ret2 != 0) {
            ret3 = func_020a132c();
            func_020a11f8(ret3, player, 1);
        }
    }
}

void func_02075334(unsigned char *payload, unsigned int length, int player)
{
    int x;
    int y;

    x = func_020b65c4();
    if (x == 0x2e) {
        y = func_020a132c();
        if (y != 0) {
            func_020a126c(func_020a132c(), 1);
        }
    }
}

void func_0207530c(unsigned char *payload, unsigned int length, int player)
{
    if (func_020b65c4() == 0x2e && func_020a132c()) {
        func_020a1208(func_020a132c(), player, 1);
    }
}

void func_02075300(unsigned char *payload, unsigned int length, int player)
{
    func_020a11e0(player);
}

void func_020752a8(unsigned char *payload, unsigned int length, int player)
{
    int off;
    UnkStruct_020752a8 *g;
    void *t;
    char *dst;

    if (func_020b65c4() != 0x2e) {
        return;
    }
    if (func_020a132c() == 0) {
        return;
    }
    MI_CpuCopy8(payload, &off, 4);
    t = func_020a245c(func_020a132c());
    g = (*(UnkStruct_020752a8 * *) &data_020ccf94);
    g->unk_68 = 0;
    dst = (((void *) (func_020962a4(g->unk_68, t), g->unk_68)), func_020984e8());
    MI_CpuCopy8(payload + 4, dst + off, length - 4);
}

void func_02075278(unsigned char *payload, unsigned int length, int player)
{
    unsigned int local;
    int ret;

    MI_CpuCopy8(payload, &local, 4);
    ret = func_020989e0((int) func_020984e8());
    MI_CpuCopy8(payload + 4, (void *) (ret + local), length - 4);
}

void func_02075254(unsigned char *payload, unsigned int length, int player)
{
    if (func_020b65c4() == 0x2e) {
        if (func_020a132c() != 0) {
            func_020a11b8(func_020a132c(), 1);
        }
    }
}
