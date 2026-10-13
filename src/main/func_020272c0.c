/* func_020272c0 @ 0x020272c0, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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

extern UnkStruct_020272c0_3 data_020c8df0;
extern UnkStruct_020272c0_3 data_020c8de8;

extern void func_0202d9c4(void);
extern int func_0209bc40(void);
extern unsigned int func_0209b4d4(unsigned int);
extern void func_0209bb90(unsigned int, int);
extern void func_0207df18(unsigned int, unsigned short *);
extern void func_020984e8(void);
extern void func_02099734(void);
extern int func_0202d754(void);
extern void func_02066650(int);
extern void func_0208150c(unsigned int);
extern int func_020036e8(void);
extern void func_0202da38(UnkStruct_020272c0 *, char *, unsigned char *, int, int, int, int, int, int);

void func_020272c0(UnkStruct_020272c0 *self, UnkStruct_020272c0_4 *out)
{
    int mode;
    int r7;
    int v;
    UnkStruct_020272c0_3 *data = &data_020c8df0;
    unsigned int flag;

    func_0202d9c4();
    mode = func_0209bc40();

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
            func_020984e8();
            func_02099734();
            r7 = func_0202d754();
            func_0209bb90(func_0209b4d4(self->unk_160), 1);
            data = &data_020c8de8;
            if (r7 != 0) {
                func_02066650(r7);
            }
            break;
        default:
            break;
    }

    func_0208150c(((UnkStruct_020272c0_2 *) self->unk_100)->unk_830);
    v = func_020036e8();
    func_0202da38(self, self->unk_104, &self->unk_122, 30, v, data->a, data->b, 0, 0);

    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}
