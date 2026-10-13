/* func_020962f8 @ 0x020962f8, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02096408(void *arg, int index);
extern void func_020963e4(void *arg, int index);
extern void func_020012dc(void);
extern void func_020012e8(void);
extern void func_02138d6c(void *ptr, int a, int b, void *f2, void *f1);

typedef struct {
    unsigned int v[3];
} Vec3;

typedef struct {
    unsigned char pad_00[0x18];
    struct {
        unsigned short a : 7;
        unsigned short b : 4;
        unsigned short c : 5;
    } flags;
    unsigned short unk_1A;
    unsigned char unk_1C;
    unsigned char pad_1D[3];
    unsigned int arr20[4];
    unsigned char arr30[4];
    Vec3 vecs[4];
    unsigned short arr64[4];
} UnkStruct_020962f8;

extern unsigned char data_021d5684[];

UnkStruct_020962f8 *func_020962f8(UnkStruct_020962f8 *p)
{
    unsigned int i;
    func_02138d6c((char *) p + 0x34, 4, 0xc, (void *) func_020012e8, (void *) func_020012dc);
    for (i = 0; i < 4; i++) {
        func_02096408((void *) data_021d5684, i);
        func_020963e4((void *) data_021d5684, i);
        p->arr20[i] = 0x93;
        p->arr30[i] = 0x33;
        p->vecs[i].v[0] = 0;
        p->vecs[i].v[1] = 0;
        p->vecs[i].v[2] = 0;
        p->arr64[i] = 0;
    }
    p->flags.a = 0;
    p->flags.b = 1;
    p->flags.c = 1;
    p->unk_1A = 0;
    p->unk_1C = 0;
    return p;
}
