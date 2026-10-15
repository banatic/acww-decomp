/* func_020f0f68 @ 0x020f0f68, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f12cc(void *self, int arg);

typedef struct {
    char pad_00[0x70];
    char unk_70;
} UnkStruct_020f0f68;

void func_020f0f68(UnkStruct_020f0f68 *self, char value)
{
    self->unk_70 = value;
    func_020f12cc(self, 1);
}
