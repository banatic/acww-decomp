/* func_02033c48 @ 0x02033c48, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA00];
    int unk_A00;
} UnkStruct_02033c48;

extern void func_02033ca8(void);
extern void func_02033ccc(void);
extern void func_02138d6c(UnkStruct_02033c48 *ptr, int a, int b, void (*cb1)(void), void (*cb2)(void));

UnkStruct_02033c48 *func_02033c48(UnkStruct_02033c48 *ptr)
{
    func_02138d6c(ptr, 40, 64, func_02033ccc, func_02033ca8);
    ptr->unk_A00 = 0;
    return ptr;
}
