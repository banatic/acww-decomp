/* villager_talk_part_7: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202777c @ 0x0202777c, 0x88 bytes, Thumb
 * func_02027740 @ 0x02027740, 0x3c bytes, Thumb
 * func_020276dc @ 0x020276dc, 0x64 bytes, Thumb
 */

typedef struct Pair {
    int field0;
    int field4;
} Pair;

typedef struct UnkStruct_0202777c {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x100 - 0xd0];
    int *unk_100;
    char unk_104;
    char pad_105[0x122 - 0x105];
    unsigned char unk_122;
    char pad_123[0x160 - 0x123];
    int unk_160;
} UnkStruct_0202777c;

typedef struct UnkStruct_0202777c_2 {
    void *field0;
    unsigned char field4;
} UnkStruct_0202777c_2;

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[0x1E];
    unsigned char unk_122;
} UnkStruct_020276dc;

typedef struct {
    void *ptr;
    unsigned char c;
} UnkStruct_020276dc_2;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} GlobalData;

extern int func_0209b4d4(int);
extern void func_0209bb90(int, int);
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern struct {
    int field0;
    unsigned char field4;
} data_020c8e28;
extern Pair data_020d9080;
extern int func_02015094(unsigned char *p);
extern void func_0207df18(void *y, unsigned short *h);
extern GlobalData data_020c8e20;

void func_0202777c(UnkStruct_0202777c *self, UnkStruct_0202777c_2 *out)
{
    func_0209bb90(func_0209b4d4(self->unk_160), 1);
    func_0202da38(self, ((char *) self) + 0x104, ((char *) self) + 0x122, 0x1e,
                  func_020036e8((unsigned char *) func_0208150c(*((int *) (((char *) self->unk_100) + 0x830)))),
                  data_020c8e28.field0, data_020c8e28.field4, 0, 0);
    out->field0 = ((char *) self) + 0x104;
    out->field4 = self->unk_122;
    self->unk_C8 = data_020d9080;
}

void func_02027740(unsigned char *p)
{
    unsigned char *x = *(unsigned char **) (p + 0x100);
    void *y = *(void **) (x + 0x830);
    unsigned short *h;
    func_02015094(p);
    h = (unsigned short *) (p + 0x124);
    if (*h != 0xfff1) {
        func_0207df18(y, h);
    }
}

void func_020276dc(UnkStruct_020276dc *p1, UnkStruct_020276dc_2 *p2)
{
    func_0202da38(p1, (void *) p1->unk_104, (void *) (&p1->unk_122), 30,
                  func_020036e8((unsigned char *) ((int) func_0208150c(*(int *) ((char *) p1->unk_100 + 0x830)))),
                  data_020c8e20.unk_00, data_020c8e20.unk_04, 0, 0);
    p2->ptr = p1->unk_104;
    p2->c = p1->unk_122;
}
