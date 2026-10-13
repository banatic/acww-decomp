/* func_020203c8 @ 0x020203c8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Global {
    int unk_00;
    unsigned char unk_04;
} Global;

typedef struct UnkStruct_020203c8 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_020203c8;

typedef struct UnkStruct_020203c8_2 {
    char pad_00[0x100];
    UnkStruct_020203c8 *unk_100;
    char unk_104[0x1E];
    unsigned char unk_122;
} UnkStruct_020203c8_2;

typedef struct UnkStruct_020203c8_3 {
    char *unk_00;
    unsigned char unk_04;
} UnkStruct_020203c8_3;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, unsigned char *, int, int, int, int, int, int);
extern Global data_020c8ab0;

void func_020203c8(UnkStruct_020203c8_2 *self, UnkStruct_020203c8_3 *out)
{
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1E, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                  data_020c8ab0.unk_00, 1, 0x11, data_020c8ab0.unk_04);
    out->unk_00 = self->unk_104;
    out->unk_04 = self->unk_122;
}
