/* func_020ea838 @ 0x020ea838, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_020ea838;
extern void func_020ea88c(void *dst, void *src);

int func_020ea838(UnkStruct_020ea838 *self)
{
    int local[3];
    if (self->unk_00 == 0) {
        if (self->unk_04 == 0) {
            if (self->unk_08 == 0) {
                return 0;
            }
        }
    }
    func_020ea88c(local, self);
    return 1;
}
