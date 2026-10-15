/* func_02021168 @ 0x02021168, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int func_0201cddc(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *a0, void *a1, void *a2, int a3, int a4, int a5, int a6, int a7, int a8);

struct UnkStruct_02021168 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02021168_2 {
    char pad_00[0x100];
    struct UnkStruct_02021168 *unk_100;
    char unk_104[0x122 - 0x104];
    char unk_122[1];
};

struct Global {
    int a;
    unsigned char b;
};

extern struct Global data_020c8b80;

int func_02021168(struct UnkStruct_02021168_2 *self)
{
    int ret = func_020644cc(2);
    if (func_0201cddc((int) self->unk_100) != 10) {
        goto fail;
    }
    if (ret != 0) {
        goto fail;
    }
    func_0202da38(self, &self->unk_104, &self->unk_122, 30, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                  data_020c8b80.a, data_020c8b80.b, 0, 0);
    return 1;
fail:
    return 0;
}
