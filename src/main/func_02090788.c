/* func_02090788 @ 0x02090788, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x148];
} UnkStruct_02090788_2;

typedef struct UnkStruct_02090788 {
    int unk_00;
    UnkStruct_02090788_2 array[4];
    char sub[1];
} UnkStruct_02090788;

extern void func_02090694(void *sub, UnkStruct_02090788 *self);
extern void func_0209050c(UnkStruct_02090788_2 *elem, UnkStruct_02090788 *self);

void func_02090788(UnkStruct_02090788 *self, int value)
{
    int i;
    self->unk_00 = value;
    func_02090694(self->sub, self);
    for (i = 0; i < 4; i++) {
        func_0209050c(&self->array[i], self);
    }
}
