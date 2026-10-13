/* func_0208b8a8 @ 0x0208b8a8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xC];
    void *unk_0C;
} UnkStruct_0208b8a8;

extern void func_0208a0c8(void **);
extern int func_0208a160(void **);
extern void func_0208b824(UnkStruct_0208b8a8 *);
extern void func_0208b9a8(UnkStruct_0208b8a8 *);

void func_0208b8a8(UnkStruct_0208b8a8 *ptr)
{
    func_0208a0c8(&ptr->unk_0C);
    if (func_0208a160(&ptr->unk_0C)) {
        func_0208b824(ptr);
        func_0208b9a8(ptr);
    }
}
