/* func_ov046_022614e8 @ 0x022614e8, 0x20 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206844c(void *a, void *b, const void *c);

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_022614e8;

extern unsigned char data_ov046_02261fe8[];

void func_ov046_022614e8(UnkStruct_022614e8 *this)
{
    void *p = this->unk_40;
    char local = 0x12;
    func_0206844c(p, &local, (const void *) data_ov046_02261fe8);
}
