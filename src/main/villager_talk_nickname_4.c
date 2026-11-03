/* villager_talk_nickname_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202adc8 @ 0x0202adc8, 0xc bytes, Thumb
 * func_0202ad58 @ 0x0202ad58, 0x70 bytes, Thumb
 * func_0202acec @ 0x0202acec, 0x6c bytes, Thumb
 */

typedef struct SubA {
    unsigned char pad_00[0x824];
    unsigned char unk_824;
    unsigned char pad_825[0xB];
    unsigned int unk_830;
} SubA;

typedef struct UnkStruct_0202ad58 {
    unsigned char pad_00[0x100];
    SubA *sub100;
    char buf104[30];
    unsigned char unk_122;
} UnkStruct_0202ad58;

typedef struct UnkStruct_0202ad58_2 {
    char *p;
    unsigned char b;
} UnkStruct_0202ad58_2;

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

extern void func_0202aea0(int, int);
extern int data_020c8b18;
extern int func_0208150c(unsigned int);
extern int func_020036e8(int);
extern int func_0200368c(char *, int, int, int);
extern void func_0201cfb4(void *a, void *b);
extern void func_0201cf90(void *a, void *b, int c, int d, int e, int f);
extern void func_0201cec8(void *a, void *b);
extern void func_0202da74(void *a, Pair b);
extern void func_02068388(int a, int b);
extern Pair data_020d9268;
extern unsigned char data_021c2734[];
extern unsigned char data_021c2764[];

void func_0202adc8(int arg, void *output)
{
    func_0202aea0(arg, 0);
}

void func_0202ad58(UnkStruct_0202ad58 *self, UnkStruct_0202ad58_2 *out)
{
    int temp;

    temp = func_020036e8(func_0208150c(self->sub100->unk_830));
    func_0200368c(self->buf104, 30, data_020c8b18, temp);

    if (self->sub100->unk_824 == 0) {
        self->unk_122 = 6;
    } else {
        self->unk_122 = 11;
    }

    out->p = self->buf104;
    out->b = self->unk_122;
}

void func_0202acec(void *param)
{
    char local[0x22];
    func_0201cfb4(param, local);
    func_0201cf90(param, local, 0, 0x4a, 0x4a, (unsigned int) data_021c2764);
    func_0201cf90(param, local, 1, 0x49, 0x49, (unsigned int) data_021c2734);
    local[0x20] = 2;
    local[0x21] = -1;
    func_0201cec8(param, local);
    func_0202da74(param, data_020d9268);
    func_02068388(*(int *) ((char *) param + 0x40), 1);
}
