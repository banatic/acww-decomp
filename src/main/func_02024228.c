/* func_02024228 @ 0x02024228, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02024228 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02024228_2 {
    char pad_00[0x100];
    struct UnkStruct_02024228 *unk_100;
    char pad_104[0x60];
    int unk_164;
};

struct UnkStruct_02024228_3 {
    char pad_00[0x64];
    int unk_64;
};

extern int func_0209b91c(int, struct UnkStruct_02024228 *);
extern void func_0209bb90(int, int);
extern void func_02078648(int, int);
extern int func_02073dd4(struct UnkStruct_02024228_3 *, int);
extern void func_0207d71c(int);
extern int func_0207f270(int);
extern void func_02079478(int);

extern struct UnkStruct_02024228_3 *data_020ccf94;

void func_02024228(struct UnkStruct_02024228_2 *self)
{
    int v1;

    v1 = self->unk_100->unk_830;
    func_0209bb90(func_0209b91c(self->unk_164, self->unk_100), 3);
    func_02078648(self->unk_100->unk_830, 3);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        func_0207d71c(v1);
        func_02079478(func_0207f270(v1));
    }
}
