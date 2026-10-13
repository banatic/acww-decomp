/* func_0205ec50 @ 0x0205ec50, 0x2d8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021ca16c[];

typedef struct {
    unsigned char unk_00;
    char pad_01[0x27];
    char sub[1];
} UnkStruct_0205ec50;

extern void func_0205f120(char *, int, void *);
extern unsigned short *func_0205f100(char *, int);
extern int func_02062148(unsigned short *);
extern unsigned int func_02062230(void);
extern int func_0205f698(unsigned short *);
extern void func_0205f094(char *, int, int);
extern int func_0205f2f0(char *, int);
extern int func_0205d6fc(void);
extern void func_0205d3d4(int, unsigned short *, int, int, int);
extern int func_0205d25c(int);
extern int func_021077e8(int);
extern void func_0206439c(int, int, void *, void *);
extern void func_0206435c(int, int, void *, void *);
extern void func_0205f070(char *, int);
extern int func_0205f130(char *, int);
extern void func_020554b0(int, int);
extern int func_0205f64c(unsigned short *);
extern int func_0205f2e8(char *, int);
extern void func_02055140(int, int);
extern void func_02055478(int, int);
extern int func_020e9968(int, int, int);
extern void func_0205f298(char *, int, int, int);
extern void func_0205f274(char *, int, int);
extern struct UnkStruct_0205ec50_2 *func_0205f110(char *, int);
extern void func_0205f20c(char *, int, int);
extern int func_0205f2b0(char *, int);
extern int NNS_G3dGetTexSRTAnmSet(int);
extern int func_02107bbc(int, int);
extern int func_0205f280(char *, int);
extern void func_0205650c(struct UnkStruct_0205ec50_2 *, int, int);
extern void func_02056478(struct UnkStruct_0205ec50_2 *, int, int, int, int);
extern int func_02055e00(int);
extern void func_020563dc(struct UnkStruct_0205ec50_2 *, int);
extern int func_020e9e34(void);
extern void func_0205f2c8(char *, int, int, int);
extern void func_0205f1bc(char *, int, int, int, int);
extern void func_02055050(int);
extern void func_02055de0(int, void *, int, int, void *, int);
extern void func_0205ef5c(void);
extern void func_0206064c(char *, int, int, int);
extern void func_0206026c(char *, int);

struct UnkStruct_0205ec50_2 {
    char p[0x18];
    int unk_18;
    int unk_1C;
};

extern int data_020dd75c;
extern int data_020dd764;

void func_0205ec50(UnkStruct_0205ec50 *p, int v, int a2, unsigned short *q, int a4, int a5)
{
    int r7, sp0xc, k, sp0x18, sp0x1c, sp0x2c, sp0x28;
    struct UnkStruct_0205ec50_2 *w;
    int sp0x24, sp0x14;
    unsigned int ok;
    unsigned short id;

    p->unk_00 = (unsigned char) v;
    func_0205f120(data_021ca16c, v, (char *) p + 8);
    if (*q == 0xfff1) {
        *func_0205f100(data_021ca16c, v) = 0xfff1;
        goto tail;
    }
    r7 = func_02062148(q);
    if (r7 >= 0 && (unsigned int) r7 < func_02062230()) {
        *func_0205f100(data_021ca16c, v) = *q;
        func_0205f094(data_021ca16c, v, func_0205f698(q));
        sp0xc = func_0205f2f0(data_021ca16c, v);
        if (a5 == 0) {
            ok = 0;
            id = *q;
            if (id >= 0x13a0 && id <= 0x13a7) {
                ok = 1;
            }
            if (ok) {
                r7 = func_0205d6fc();
                func_0205d3d4(r7, q, a4, 0, 0);
                r7 = func_021077e8(func_0205d25c(r7));
                sp0x18 = func_021077e8(sp0xc);
                func_0206439c(r7, sp0x18, &data_020dd75c, &data_020dd764);
                func_0206435c(r7, sp0x18, &data_020dd75c, &data_020dd764);
            }
        }
        func_0205f070(data_021ca16c, v);
        r7 = func_0205f130(data_021ca16c, v);
        func_020554b0(r7, sp0xc);
        k = func_0205f64c(q);
        if (k == 0x2b) {
            goto tail;
        }
        func_02055140(r7, func_0205f2e8(data_021ca16c, v));
        func_02055478(r7, func_0205f2e8(data_021ca16c, v));
        if (k == 0x27) {
            sp0x1c = func_0205f2e8(data_021ca16c, v);
            func_0205f298(data_021ca16c, v, func_020e9968(sp0x1c, 0x210, 4), 0x210);
            func_0205f274(data_021ca16c, v, sp0x1c);
            func_020e9968(sp0x1c, 0x1c, 4);
            w = func_0205f110(data_021ca16c, v);
            w->unk_18 = 0;
            w->unk_1C = 0;
            func_0205f20c(data_021ca16c, v, 0);
            sp0x24 = func_02107bbc(NNS_G3dGetTexSRTAnmSet(func_0205f2b0(data_021ca16c, v)), 0);
            sp0x14 = *(int *) (r7 + 0x5c);
            func_0205650c(w, sp0x14, func_0205f280(data_021ca16c, v));
            func_02056478(w, sp0x24, 1, 0x1000, 0);
            func_020563dc(w, func_02055e00(r7));
        }
        sp0x28 = func_0205f2e8(data_021ca16c, v);
        sp0x2c = func_020e9e34();
        func_0205f2c8(data_021ca16c, v, func_020e9968(sp0x28, sp0x2c, 4), sp0x2c);
        func_0205f1bc(data_021ca16c, v, k, 0, 0);
        func_02055050(r7);
        if (a5 == 0) {
            func_02055de0(r7, (void *) func_0205ef5c, 6, 1, p, 0);
        }
    } else {
        *func_0205f100(data_021ca16c, v) = 0xfff1;
    }
tail:
    ok = 0;
    id = *q;
    if (id >= 0x1375 && id <= 0x1375) {
        ok = 1;
    }
    if (ok) {
        func_0206064c((char *) p + 0x28, v, a2, 1);
    } else if (id >= 0x1374 && id <= 0x1374) {
        func_0206064c((char *) p + 0x28, v, a2, 0);
    } else if ((id >= 0x137a && id <= 0x137a) || (id >= 0x137b && id <= 0x137b)) {
        func_0206064c((char *) p + 0x28, v, a2, 2);
    } else {
        func_0206064c((char *) p + 0x28, v, a2, 3);
    }
    ok = 0;
    id = *q;
    if (id >= 0x1374 && id <= 0x1374) {
        ok = 1;
    }
    if (ok || (id >= 0x1375 && id <= 0x1375)) {
        func_0206026c((char *) p + 0x28, 1);
    }
}
