/* func_ov003_0221c4bc @ 0x0221c4bc, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0221c4bc {
    char pad_00[0x198];
    int unk_198;
    char pad_19C[0x118];
    char unk_2B4[1];
} UnkStruct_0221c4bc;

extern int func_020b374c(int);
extern int func_020b3848(int);
extern void func_ov003_0221c438(void *ptr, int a, int b);

extern unsigned char data_021f34b0[];

int func_ov003_0221c4bc(UnkStruct_0221c4bc *self)
{
    int a = self->unk_198;
    int result = func_020b3848(func_020b374c((unsigned int) data_021f34b0));
    func_ov003_0221c438(&self->unk_2B4, a, result);
    return 1;
}
