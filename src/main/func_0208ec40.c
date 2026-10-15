/* func_0208ec40 @ 0x0208ec40, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e2330;

typedef struct UnkStruct_0208ec40 {
    int _dummy[5];
} UnkStruct_0208ec40;

typedef struct UnkStruct_0208ec40_2 {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    UnkStruct_0208ec40 sub_14;
    UnkStruct_0208ec40 sub_28;
    int unk_3C;
    char unk_40;
    int unk_44;
} UnkStruct_0208ec40_2;

extern void func_0208af30(void *);
extern void func_0208a1f8(UnkStruct_0208ec40 *);
extern void *func_0208e95c(void *, int);

UnkStruct_0208ec40_2 *func_0208ec40(UnkStruct_0208ec40_2 *self, char param)
{
    func_0208af30(self);
    self->unk_00 = &data_020e2330;
    self->unk_0C = 0;
    self->unk_10 = 0;
    func_0208a1f8(&self->sub_14);
    func_0208a1f8(&self->sub_28);
    self->unk_3C = 0;
    self->unk_40 = param;
    self->unk_44 = -1;
    func_0208e95c(self, 0);
    return self;
}
