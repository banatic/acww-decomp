/* func_020329ec @ 0x020329ec, 0x66 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020329ec;

extern int func_02031c50(void);
extern int func_02032eb8(void *q, unsigned int a, unsigned int *sub, unsigned int *out, unsigned int b, int c);
extern void func_02032f0c(void *q, unsigned int a, unsigned int b, struct UnkStruct_020329ec *arg3, unsigned int c, int d);

struct UnkStruct_020329ec {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

struct UnkStruct_020329ec_2 {
    unsigned int unk_00;
    struct UnkStruct_020329ec *unk_04;
    unsigned int unk_08;
    unsigned int sub;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned int flags;
};

void func_020329ec(struct UnkStruct_020329ec_2 *p, void *q)
{
    unsigned int local;

    if (p->flags & 1) {
        if (func_02032eb8(q, p->unk_08, &p->sub, &local, p->unk_20, func_02031c50())) {
            p->unk_04->unk_04 |= 1;
            p->unk_04->unk_08 = local;
        }
    }

    if (p->flags & 6) {
        func_02032f0c(q, p->unk_08, p->unk_1C, p->unk_04, p->unk_20, func_02031c50());
    }
}
