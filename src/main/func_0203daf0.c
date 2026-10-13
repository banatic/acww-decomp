/* func_0203daf0 @ 0x0203daf0, 0x52 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0203daf0 {
    char pad_00[0x2c];
    int unk_2C;
} UnkStruct_0203daf0;

extern int func_02050c40(void);
extern int func_02050c38(void);
extern int func_02050c48(void);
extern int func_02050c50(void);
extern void func_020a9334(UnkStruct_0203daf0 *, int);

void func_0203daf0(UnkStruct_0203daf0 *self)
{
    int value = self->unk_2C;
    if (value == 0) {
        func_020a9334(self, func_02050c40());
    } else if (value == 1) {
        func_020a9334(self, func_02050c38());
    } else if (value == 7) {
        func_020a9334(self, func_02050c48());
    } else if (value == 8) {
        func_020a9334(self, func_02050c50());
    }
}
