/* func_0203eb08 @ 0x0203eb08, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x10];
    int unk_10;
} UnkStruct_0203eb08;
extern int func_0203ef90(int x);
extern int func_0203ed8c(int);
extern int func_0203eb40(UnkStruct_0203eb08 *self);
extern int func_0203ebd0(UnkStruct_0203eb08 *self);

int func_0203eb08(UnkStruct_0203eb08 *self)
{
    if (func_0203ed8c((int) func_0203ef90(self->unk_10))) {
        if (func_0203eb40(self) != 0) {
            goto one;
        }
        return 0;
    } else {
        if (func_0203ebd0(self) != 0) {
            goto one;
        }
        return 0;
    }
one:
    return 1;
}
