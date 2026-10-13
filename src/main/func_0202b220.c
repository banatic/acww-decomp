/* func_0202b220 @ 0x0202b220, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207f1c8(void *);
extern void func_0209b5ec(void);
extern void func_0209c330(void);
extern int func_02099fe8(void);
extern void func_0207de14(void *, void *);
extern void func_0202d694(unsigned short *);
extern int func_020644b4(int);
extern int func_0204c878(unsigned short *);
extern int func_0205be38(void);
extern int func_0202b510(int);
extern void func_020984e8(void);
extern int func_02099734(void);
extern int func_02098cf8(int, int);
extern void func_0208150c(void *);
extern int func_020036e8(void);
extern void func_0202da38(void *, void *, void *, int, int, int, unsigned char, int, int);
extern void func_02015fb0(void *, int, int, int, int, int);
extern unsigned char data_020c8be8[];

typedef struct {
    unsigned char pad_00[0x100];
    void *unk_100;
    char unk_104[0x122 - 0x104];
    char unk_122[0x19c - 0x122];
    unsigned short unk_19C;
    unsigned char unk_19E;
    unsigned char pad_19F;
    int unk_1A0;
} UnkStruct_0202b220;

typedef struct {
    unsigned short a;
    unsigned short b;
} UnkStruct_0202b220_2;

int func_0202b220(UnkStruct_0202b220 *p)
{
    UnkStruct_0202b220_2 local;
    int r5, limit, v, arg5, arg6, arg8;
    unsigned char arg7;
    void *r6;

    r6 = *(void **) ((char *) p->unk_100 + 0x830);
    func_0207f1c8(r6);
    func_0209b5ec();
    func_0209c330();
    if (func_02099fe8() == -1) {
        goto fail;
    }

    func_0207de14(&local, r6);
    p->unk_19C = local.a;
    if (p->unk_19C != 0xfff1) {
        p->unk_19E = 1;
    } else {
        func_0202d694(&local.b);
        p->unk_19C = local.b;
        p->unk_19E = 0;
    }

    if (p->unk_19C == 0xfff1) {
        goto fail;
    }

    r5 = func_020644b4(0xccd) + 0xccd;
    r5 = (r5 * func_0204c878(&p->unk_19C)) >> 12;
    limit = 3 * func_0205be38();
    v = r5 - (r5 > limit ? limit : 0);
    p->unk_1A0 = func_0202b510(v);

    if (p->unk_1A0 > 0xbb8) {
        p->unk_1A0 = 0xbb8;
    }

    func_020984e8();
    if (p->unk_1A0 > func_02098cf8(func_02099734(), 1)) {
        goto fail;
    }

    func_0208150c(r6);
    arg5 = func_020036e8();
    arg6 = *(int *) data_020c8be8;
    arg7 = data_020c8be8[4];
    func_0202da38(p, p->unk_104, p->unk_122, 30, arg5, arg6, arg7, 0, 0);
    func_02015fb0(p, p->unk_1A0, 2, 0xa, 0, 0);
    return 1;

fail:
    return 0;
}
