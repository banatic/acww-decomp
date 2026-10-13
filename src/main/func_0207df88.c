/* func_0207df88 @ 0x0207df88, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7b0];
    unsigned short arr[4];
} UnkStruct_0207df88;

void func_0207df88(UnkStruct_0207df88 *self)
{
    int i, j;
    i = 0;
    while (i < 3) {
        if (self->arr[i] == 0xfff1) {
            j = i + 1;
            while (j < 4) {
                if (self->arr[j] != 0xfff1) {
                    self->arr[i] = self->arr[j];
                    self->arr[j] = 0xfff1;
                    break;
                }
                ++j;
            }
            if (j == 4) {
                return;
            }
        }
        ++i;
    }
}
