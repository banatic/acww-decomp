/* func_02056610 @ 0x02056610, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a50(int, int);

typedef struct {
    char pad_00[0x22];
    unsigned char unk_22;
    unsigned char unk_23;
    char pad2[0x4];
} UnkStruct_02056610_2;

typedef struct {
    char pad_00[0x18];
    int unk_18;
    char pad_1C[0x0A];
    unsigned char count;
    char pad2[0x01];
    UnkStruct_02056610_2 *array;
} UnkStruct_02056610;

void func_02056610(UnkStruct_02056610 *self, int argument1)
{
    int i;
    int val;

    val = func_02057a50(self->unk_18, (int) argument1);
    if (val == -1) {
        return;
    }

    for (i = 0; i < self->count; i++) {
        if (val == self->array[i].unk_22) {
            self->array[i].unk_23 &= ~1;
            break;
        }
    }
}
