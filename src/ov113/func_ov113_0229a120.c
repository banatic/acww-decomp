/* func_ov113_0229a120 @ 0x0229a120, 0x28 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov113_022998ac(void *ptr);
extern void func_ov002_02208098(void *ptr, int arg);

typedef struct {
    char pad_00[0x2b20];
    void *unk_2B20;
} UnkStruct_0229a120;

void func_ov113_0229a120(UnkStruct_0229a120 *self)
{
    if (func_0208e484(&self->unk_2B20)) {
        func_ov113_022998ac(self);
        func_ov002_02208098(self, 1);
    }
}
