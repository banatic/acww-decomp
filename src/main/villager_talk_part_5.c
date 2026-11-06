/* villager_talk_part_5: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020273fc @ 0x020273fc, 0x64 bytes, Thumb
 * func_020273e0 @ 0x020273e0, 0x1c bytes, Thumb
 * func_020273a8 @ 0x020273a8, 0x38 bytes, Thumb
 * func_020272c0 @ 0x020272c0, 0xe8 bytes, Thumb
 */

typedef struct UnkStruct_020273fc {
    unsigned char pad_00[0x830];
    void *unk_830;
} UnkStruct_020273fc;

typedef struct UnkStruct_020273fc_2 {
    unsigned char pad_00[0x100];
    UnkStruct_020273fc *unk_100;
    char unk_104[30];
    unsigned char unk_122;
} UnkStruct_020273fc_2;

typedef struct Global {
    int word;
    unsigned char byte;
} Global;

typedef struct UnkStruct_020273fc_3 {
    void *ptr;
    unsigned char byte;
} UnkStruct_020273fc_3;

typedef struct {
    unsigned int x;
    unsigned int y;
} TwoWords;

typedef struct {
    int unk_00;
    int unk_04;
} DataPair;

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[30];
    unsigned char unk_122;
    unsigned short unk_124;
    char pad_126[0x3a];
    unsigned int unk_160;
} UnkStruct_020272c0;

typedef struct {
    char pad_00[0x830];
    unsigned int unk_830;
} UnkStruct_020272c0_2;

typedef struct {
    unsigned int a;
    unsigned char b;
} UnkStruct_020272c0_3;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020272c0_4;

extern int func_0208150c(void *arg);
extern int func_020036e8(int arg);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int scale, int h, int i);
extern Global data_020c8df8;
extern int func_02015094(unsigned int arg);
extern void func_0202dbdc(unsigned int arg, TwoWords pair);
extern TwoWords data_020d9068;
extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_0202d754(int);
extern void func_0201579c(int, int, int);
extern int func_02015828(int, int);
extern void func_0202dbf0(int, DataPair);
extern DataPair data_020d9488;
extern UnkStruct_020272c0_3 data_020c8df0;
extern UnkStruct_020272c0_3 data_020c8de8;
extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern unsigned int func_0209b4d4(unsigned int);
extern void func_0209bb90(unsigned int, int);
extern void func_0207df18(unsigned int, unsigned short *);
extern void func_02066650(int);

void func_020273fc(UnkStruct_020273fc_2 *self, UnkStruct_020273fc_3 *out)
{
    int local0 = func_020036e8(func_0208150c(self->unk_100->unk_830));
    int local1 = data_020c8df8.word;
    unsigned char local2 = data_020c8df8.byte;
    func_0202da38(self, self->unk_104, &self->unk_122, 30, local0, local1, local2, 0, 0);
    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}

void func_020273e0(unsigned int arg)
{
    func_02015094(arg);
    func_0202dbdc(arg, data_020d9068);
}

void func_020273a8(int param, int event)
{
    int tmp;

    tmp = func_0202d754(func_02099734(func_020984e8()));
    func_0201579c(param, tmp, 1);
    func_02015828(param, 5);
    func_0202dbf0(param, data_020d9488);
}

void func_020272c0(UnkStruct_020272c0 *self, UnkStruct_020272c0_4 *out)
{
    int mode;
    int r7;
    int v;
    UnkStruct_020272c0_3 *data = &data_020c8df0;
    unsigned int flag;

    mode = func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) self));

    switch (mode) {
        case 10:
            func_0209bb90(func_0209b4d4(self->unk_160), 1);
            flag = 0;
            if (self->unk_124 >= 0x11a8 && self->unk_124 <= 0x12a7) {
                flag = 1;
            }
            if (flag != 0) {
                func_0207df18(((UnkStruct_020272c0_2 *) self->unk_100)->unk_830, &self->unk_124);
            }
            break;
        case 19:
            r7 = func_0202d754((int) ((void *) func_02099734((int) func_020984e8())));
            func_0209bb90(func_0209b4d4(self->unk_160), 1);
            data = &data_020c8de8;
            if (r7 != 0) {
                func_02066650(r7);
            }
            break;
        default:
            break;
    }

    v = func_020036e8(
        (int) ((unsigned char *) (unsigned int) func_0208150c((void *) (((UnkStruct_020272c0_2 *) self->unk_100)->unk_830))));
    func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 30, v, data->a, data->b, 0, 0);

    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}
