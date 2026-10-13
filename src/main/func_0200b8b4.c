/* func_0200b8b4 @ 0x0200b8b4, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_0200bb60(void *self);
extern void func_02010d64(void *self);
extern void func_0200b930(void *self);
extern void func_02010f5c(void *self);
extern void func_0200f530(void *self, void *loc);
extern int func_02008258(void *self, int arg);
typedef struct {
    char pad_00[0x7d4];
    unsigned char sub[0x1c];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
    int unk_800;
} UnkStruct_0200b8b4;
typedef struct {
    int a;
    int b;
} TwoInts;

void func_0200b8b4(UnkStruct_0200b8b4 *self)
{
    unsigned char *sub;
    unsigned char y;
    TwoInts loc;

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_0200bb60(self);
        func_02010d64(self);
        func_0200b930(self);
    } else {
        func_02010f5c(self);
        sub = self->sub;
        y = sub[6];
        loc.a = sub[5];
        loc.b = y;
        func_0200f530(self, &loc);
        func_02010d64(self);
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200b930(self);
    }
}
