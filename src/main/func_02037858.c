/* func_02037858 @ 0x02037858, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02037858_2 {
    unsigned char pad_00[0x634];
    int unk_634;
    int unk_638;
    int unk_63C;
    int unk_640;
    int unk_644;
    int unk_648;
} UnkStruct_02037858;

extern int func_02037af8(const char *a, int b);
extern int NNS_FndMountArchive(void *buf, const char *data, int param);
extern int NNS_FndGetArchiveFileByName(const char *name);
extern int NNS_G3dGetMatCAnmSet(int a);
extern int func_02107b80(int a, int b);
extern int NNS_G3dGetTexSRTAnmSet(int a);
extern int func_02107bbc(int a, int b);
extern int NNS_G3dGetTexPatAnmSet(int a);
extern int func_02107bf8(int a, int b);
extern int func_021077e8(int a);
extern void func_0210285c(void *buf);

extern char data_020da418[];
extern char data_020da390[];
extern char data_020da428[];
extern char data_020da43c[];
extern char data_020da450[];
extern char data_020da460[];
extern char data_020da474[];
extern char data_020da484[];

void func_02037858(UnkStruct_02037858 *self)
{
    char buf[0x68];
    if (NNS_FndMountArchive(buf, data_020da390, func_02037af8(data_020da418, 0)) != 0) {
        self->unk_634 = func_02107b80(NNS_G3dGetMatCAnmSet(NNS_FndGetArchiveFileByName(data_020da428)), 0);
        self->unk_638 = func_02107bbc(NNS_G3dGetTexSRTAnmSet(NNS_FndGetArchiveFileByName(data_020da43c)), 0);
        self->unk_63C = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_020da450)), 0);
        self->unk_640 = func_021077e8(NNS_FndGetArchiveFileByName(data_020da460));
        self->unk_644 = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_020da474)), 0);
        self->unk_648 = func_021077e8(NNS_FndGetArchiveFileByName(data_020da484));
        func_0210285c(buf);
    }
}
