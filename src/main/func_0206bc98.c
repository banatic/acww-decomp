/* func_0206bc98 @ 0x0206bc98, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206c058(void *param1, int param2);

typedef struct {
    char pad_00[0x28];
    void *unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0206bc98;

void func_0206bc98(UnkStruct_0206bc98 *self)
{
    self->unk_30 = 3;
    func_0206c058(self->unk_28, 3);
}
