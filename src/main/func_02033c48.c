/* func_02033c48 @ 0x02033c48, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA00];
    int unk_A00;
} UnkStruct_02033c48;

extern void func_02033ca8(void);
extern void func_02033ccc(void);
extern void __cxa_vec_ctor(UnkStruct_02033c48 *ptr, int a, int b, void (*cb1)(void), void (*cb2)(void));

UnkStruct_02033c48 *func_02033c48(UnkStruct_02033c48 *ptr)
{
    __cxa_vec_ctor(ptr, 40, 64, func_02033ccc, func_02033ca8);
    ptr->unk_A00 = 0;
    return ptr;
}
