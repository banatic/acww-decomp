/* func_02056658 @ 0x02056658, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a50(int, const char *name);

typedef struct {
    char pad_00[0x22];
    unsigned char unk_22;
    unsigned char unk_23;
    char pad1[0x28 - 0x24];
} UnkStruct_02056658_2;

typedef struct {
    char pad_00[0x18];
    int unk_18;
    char pad1[0x26 - 0x1C];
    unsigned char count;
    char pad_27[0x28 - 0x27];
    UnkStruct_02056658_2 *arr;
} UnkStruct_02056658;

void func_02056658(UnkStruct_02056658 *self, const char *name)
{
    unsigned char count;
    int value;
    int i;

    value = func_02057a50(self->unk_18, name);
    if (value == -1) {
        return;
    }
    count = self->count;
    for (i = 0; i < count; i++) {
        if (value == self->arr[i].unk_22) {
            self->arr[i].unk_23 |= 1;
            break;
        }
    }
}
