/* func_02066cd4 @ 0x02066cd4, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8];
    int unk_08;
    int unk_0C;
    char pad_10[0x684 - 0x10];
    char unk_684[4];
    char pad_688[0x13b8 - 0x688];
    char unk_13B8[4];
    char pad_13BC[0x13e8 - 0x13bc];
    int unk_13E8;
    char pad_13EC[0x149c - 0x13ec];
    char unk_149C[4];
    char pad_14A0[0x1a2c - 0x14a0];
    char unk_1A2C[4];
    char pad_1A30[0x1e98 - 0x1a30];
    unsigned char unk_1E98;
} UnkStruct_02066cd4;

extern int func_02067d7c(void *);
extern void func_0206bd2c(void *);
extern void func_02068ae4(void *, int);
extern int func_020a94d8(void *);
extern void func_0206c05c(void *);
extern void func_02068a04(void *);
extern void func_02067540(void *);
extern void func_020680d0(void *);

void func_02066cd4(UnkStruct_02066cd4 *p)
{
    int val, b3, b2, b4, b5, b0, bc, r7;

    if (func_02067d7c(p)) {
        func_0206bd2c(&p->unk_13B8);
    }
    func_02068ae4(&p->unk_1A2C, 0);
    func_020a94d8(&p->unk_149C);
    func_0206c05c(&p->unk_684);
    if (p->unk_1E98 == 0) {
        func_02068a04(&p->unk_1A2C);
    }
    val = p->unk_13E8;
    b3 = (val == 3);
    b2 = (val == 2);
    b4 = (val == 4);
    b5 = (val == 5);
    b0 = (val == 0);
    bc = (p->unk_0C == 0);
    r7 = 1;
    if (!bc && !b2 && !b4 && !b5 && !b0) {
        r7 = 0;
    }
    if (b3) {
        p->unk_0C = 0;
    }
    if (r7) {
        if (bc) {
            func_02067540(p);
        }
        p->unk_08 = 2;
        func_020680d0(p);
    }
}
