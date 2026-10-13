/* func_ov009_02263344 @ 0x02263344, 0x68 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern void func_020676c4(int, int);

struct UnkStruct_02263344 {
    char pad_00[0x12c];
    int unk_12C;
    char pad_130[6];
    unsigned short unk_136;
};

void func_ov009_02263344(struct UnkStruct_02263344 *self)
{
    int result;
    if (func_0204bcdc(&self->unk_136) != 0) {
        unsigned short local = 0x500a;
        result = (func_0204bc64(&self->unk_136) == func_0204bc64(&local));
    } else {
        result = (self->unk_136 == 0x500a);
    }
    if (!result) {
        func_020676c4(self->unk_12C, 100);
    }
}
