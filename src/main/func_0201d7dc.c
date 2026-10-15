/* func_0201d7dc @ 0x0201d7dc, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201d7dc {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_0201d7dc_2 {
    char pad_00[0x100];
    struct UnkStruct_0201d7dc *unk_100;
    char pad_104[0x28];
    int unk_12C;
    char pad_130[0x8];
    int unk_138;
};

struct Big {
    unsigned char a[0x28];
    unsigned char b[0x34];
    unsigned char c[0x20];
    unsigned char d[0x98];
};

extern int func_020814f4(int);
extern int func_0208150c(int);
extern int func_02081a14(void *);
extern void *func_0206daf8(unsigned char *);
extern void *func_0206da98(unsigned char *);
extern void *func_0206da38(unsigned char *);
extern void *func_02094fd4(unsigned char *);
extern int func_02003618(int, unsigned char *);
extern void func_0203d73c(unsigned char *);
extern void *func_02094fbc(unsigned char *);
extern int func_0203d930(unsigned char *, unsigned char *, unsigned char *, int *, unsigned char *, unsigned char *);
extern void func_02066198(unsigned char *, unsigned char *, unsigned char *, unsigned char *, int, unsigned char *, int, int);
extern void *func_0206da20(unsigned char *);
extern void *func_0206da80(unsigned char *);
extern void *func_0206dae0(unsigned char *);
extern void func_0201579c(struct UnkStruct_0201d7dc_2 *, void *, int);
extern int func_02015828(struct UnkStruct_0201d7dc_2 *, int);

extern unsigned char data_021c2604;
extern unsigned char data_020d9f5c;
extern unsigned char data_020d8d1c;

int func_0201d7dc(struct UnkStruct_0201d7dc_2 *self)
{
    void *tested_value0;
    void *p;
    int a;
    int b;
    struct Big big;
    int result;
    unsigned char flag;

    if (self->unk_138 != 0) {
        p = (void *) func_020814f4(self->unk_100->unk_830);
    } else {
        a = func_0208150c(self->unk_100->unk_830);

        func_0206daf8(big.a);
        func_0206da98(big.d);
        func_0206da38(big.b);

        b = 0;
        p = &data_021c2604;
        if ((tested_value0 = (void *) (self->unk_12C)) != 0) {
            b = func_02081a14(tested_value0);
        }

        func_02094fd4(big.c);
        func_02003618(a, big.c);
        func_0203d73c(big.c);
        func_02094fbc(big.c);

        flag = (unsigned char) b;
        func_0203d930(big.a, big.d, big.b, &result, &flag, &data_020d9f5c);
        func_02066198(p, big.a, big.d, big.b, result, &data_020d8d1c, a, a);

        func_0206da20(big.b);
        func_0206da80(big.d);
        func_0206dae0(big.a);
    }

    func_0201579c(self, p, 0);
    func_02015828(self, 5);
    return 1;
}
