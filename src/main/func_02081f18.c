/* func_02081f18 @ 0x02081f18, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00[0x5c];
    unsigned char unk_5C;
} UnkStruct_02081f18;

extern void func_020642f8(void *arg);
extern void func_0209526c(void *arg);

UnkStruct_02081f18 *func_02081f18(UnkStruct_02081f18 *ptr)
{
    func_020642f8(&ptr->unk_5C);
    func_0209526c(ptr);
    return ptr;
}
