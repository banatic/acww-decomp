/* func_020f3dc4 @ 0x020f3dc4, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f3fe0(void *self);
extern void func_020f65bc(int cond, int code);
extern char data_0213e99c;
typedef struct UnkStruct_020f3dc4 {
    unsigned char pad_00[0x30];
    unsigned int unk_30;
} UnkStruct_020f3dc4;
extern UnkStruct_020f3dc4 data_021fd1bc;
typedef struct UnkStruct_020f3dc4_2 {
    void *vtable;
    unsigned char unk_04;
} UnkStruct_020f3dc4_2;
void *func_020f3dc4(void *self)
{
    UnkStruct_020f3dc4_2 *s = (UnkStruct_020f3dc4_2 *) self;
    func_020f3fe0(self);
    s->vtable = &data_0213e99c;
    if (data_021fd1bc.unk_30 != 0) {
        func_020f65bc(data_021fd1bc.unk_30, 0xd1);
    }
    s->unk_04 = 2;
    return self;
}
