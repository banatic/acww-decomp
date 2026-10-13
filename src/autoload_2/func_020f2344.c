/* func_020f2344 @ 0x020f2344, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x50];
    int unk_50;
} UnkStruct_020f2344;

extern void func_020eee5c(int arg);

void func_020f2344(UnkStruct_020f2344 *self)
{
    func_020eee5c(self->unk_50);
}
