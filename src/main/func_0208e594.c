/* func_0208e594 @ 0x0208e594, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x20];
    int unk_20;
    int unk_24;
    char pad_28[0x18];
    int unk_40;
} UnkStruct_0208e594;

extern int func_0208aef0(UnkStruct_0208e594 *self);
extern void func_020041bc(unsigned char c);

void func_0208e594(UnkStruct_0208e594 *self, int a, int b)
{
    self->unk_20 = a;
    self->unk_24 = b;
    if (self->unk_40 != 0) {
        int value;
        value = func_0208aef0(self) + self->unk_20;
        if (value < 0) {
            value = 0;
        }
        if (value > 0xff) {
            value = 0xff;
        }
        func_020041bc((unsigned char) value);
    }
}
