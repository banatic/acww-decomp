/* func_0201d448 @ 0x0201d448, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int object);
extern int func_02098f0c(int, void *, int, int);
extern int func_020996ac(int);
extern int func_0203cd2c(int, void *, int, int);
extern int func_0207de70(void *, void *);
extern int func_020154b4(void *, void *, int, int, int);

typedef struct {
    unsigned char pad_00[0x100];
    void *unk_100;
    unsigned char pad_104[0x98];
    unsigned short unk_19C;
    unsigned char unk_19E;
} TStruct;

int func_0201d448(TStruct *base)
{
    int r4, r6, r2;
    void *p, *q;

    if (base->unk_19C == 0xfff1) {
        goto fail;
    }

    r4 = func_020984e8();
    r6 = func_02099734(r4);
    r2 = func_02098eb8((int) r6);
    if (r2 < 0) {
        goto fail;
    }

    func_02098f0c(r6, &base->unk_19C, r2, 0);
    func_0203cd2c(func_020996ac(r4), &base->unk_19C, 0, 1);

    if (base->unk_19E == 1) {
        p = base->unk_100;
        q = *(void **) ((char *) p + 0x830);
        func_0207de70(q, &base->unk_19C);
    }

    func_020154b4(base, &base->unk_19C, 0, 5, 0);
    return 1;

fail:
    return 0;
}
