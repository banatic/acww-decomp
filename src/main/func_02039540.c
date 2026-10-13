/* func_02039540 @ 0x02039540, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02039540 {
    unsigned char pad_00[0x2e4];
    void *arr[4];
} UnkStruct_02039540;
extern int func_020395a8(UnkStruct_02039540 *self, void *p);

void func_02039540(UnkStruct_02039540 *self)
{
    int i;
    int j;
    int k;

    for (i = 0; i < 4; i++) {
        if (self->arr[i] != 0 && func_020395a8(self, self->arr[i]) != 0) {
            self->arr[i] = 0;
        }
    }
    for (j = 0; j < 4; j++) {
        if (self->arr[j] == 0) {
            for (k = j + 1; k < 4; k++) {
                if (self->arr[k] != 0) {
                    self->arr[j] = self->arr[k];
                    self->arr[k] = 0;
                    break;
                }
            }
        }
    }
}
