/* func_ov147_022993fc @ 0x022993fc, 0xc bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov147_02299fc8(void *, int);

typedef struct {
    char pad_00[0x48];
    void *unk_48;
} UnkStruct_022993fc;

int func_ov147_022993fc(UnkStruct_022993fc *this)
{
    return func_ov147_02299fc8(this->unk_48, 3);
}
