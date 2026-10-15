/* func_020273fc @ 0x020273fc, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *arg);
extern int func_020036e8(int arg);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int scale, int h, int i);

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
extern Global data_020c8df8;

typedef struct UnkStruct_020273fc_3 {
    void *ptr;
    unsigned char byte;
} UnkStruct_020273fc_3;

void func_020273fc(UnkStruct_020273fc_2 *self, UnkStruct_020273fc_3 *out)
{
    int local0 = func_020036e8(func_0208150c(self->unk_100->unk_830));
    int local1 = data_020c8df8.word;
    unsigned char local2 = data_020c8df8.byte;
    func_0202da38(self, self->unk_104, &self->unk_122, 30, local0, local1, local2, 0, 0);
    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}
