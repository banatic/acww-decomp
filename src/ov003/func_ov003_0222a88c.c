/* func_ov003_0222a88c @ 0x0222a88c, 0x1a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x44];
    int unk_44;
} UnkStruct_0222a88c;
int func_0204fd6c(int a, int b);

int func_ov003_0222a88c(UnkStruct_0222a88c *self)
{
    int r = 0;
    if (func_0204fd6c(self->unk_44, 1) != 0) {
        r = 1;
    }
    return r;
}
