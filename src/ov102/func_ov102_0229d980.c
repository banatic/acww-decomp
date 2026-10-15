/* func_ov102_0229d980 @ 0x0229d980, 0x30 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d980 UnkStruct_0229d980;
struct UnkStruct_0229d980 {
    char pad_00[0x2274];
    unsigned char unk_2274;
    char pad_2275[0x332];
    unsigned char unk_25A7;
};

extern int func_0208e484(void *ptr);
extern unsigned char *func_ov002_02208098(UnkStruct_0229d980 *self, unsigned char value);
extern void func_ov102_0229cd38(UnkStruct_0229d980 *self);

void func_ov102_0229d980(UnkStruct_0229d980 *self)
{
    if (func_0208e484(&self->unk_2274) != 0) {
        func_ov002_02208098(self, self->unk_25A7);
    }
    func_ov102_0229cd38(self);
}
