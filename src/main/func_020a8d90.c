/* func_020a8d90 @ 0x020a8d90, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a92b0(void *a, int b);
extern int data_020e3e04;

typedef struct UnkStruct_020a8d90 {
    void *vtable;      // offset 0
    char pad_04[0x28]; // offset 4 to 0x2b
    int unk_2C;        // offset 0x2c
    int unk_30;        // offset 0x30
    int unk_34;        // offset 0x34
    char unk_38;       // offset 0x38
} UnkStruct_020a8d90;

UnkStruct_020a8d90 *func_020a8d90(UnkStruct_020a8d90 *a)
{
    func_020a92b0(a, 1);
    a->vtable = &data_020e3e04;
    a->unk_2C = 0;
    a->unk_30 = 0;
    a->unk_34 = 0;
    a->unk_38 = 0;
    return a;
}
