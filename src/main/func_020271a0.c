/* func_020271a0 @ 0x020271a0, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020271a0 {
    int a;
    unsigned char b;
} data_020c8dc8, data_020c8db8;

extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *p1, void *p2, void *p3, int n, int a, int b, int c, int d, int e);

struct Param1 {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[0x3d];
    int flag160;
};

struct UnkStruct_020271a0_2 {
    void *ptr;
    unsigned char byte;
};

void func_020271a0(struct Param1 *p, struct UnkStruct_020271a0_2 *o)
{
    struct UnkStruct_020271a0 *r4 = 0;
    int v;
    int tmp;

    v = func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) p));

    switch (v) {
        case 0xa:
            r4 = &data_020c8dc8;
            break;
        case 0x13:
            r4 = &data_020c8db8;
            break;
    }

    if (p->flag160 != 0 && r4 != 0) {
        tmp = func_020036e8(func_0208150c(*(int *) ((char *) p->unk_100 + 0x830)));
        func_0202da38(p, &p->unk_104, &p->unk_122, 0x1e, tmp, r4->a, r4->b, 0, 0);
    }

    o->ptr = &p->unk_104;
    o->byte = p->unk_122;
}
