/* func_020a9318 @ 0x020a9318, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *func_020a9cc0(void *ptr);
extern void func_020a9ccc(void *ptr);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_020a9318;

void func_020a9318(UnkStruct_020a9318 *arg)
{
    arg->unk_04 = *func_020a9cc0(&arg->unk_08);
    func_020a9ccc(&arg->unk_08);
}
