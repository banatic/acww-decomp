/* func_ov100_0229d1d0 @ 0x0229d1d0, 0x36 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d208(void *obj, int i);
extern int func_ov100_0229d5d4(void *obj, int i);
extern void func_ov094_0229a888(char *p, int v);

typedef struct {
    char pad_00[0xcc];
    char unk_CC;
} UnkStruct_0229d1d0;

void func_ov100_0229d1d0(UnkStruct_0229d1d0 *self)
{
    unsigned char i;
    i = 0;
    do {
        if (func_ov100_0229d208(self, i)) {
            func_ov094_0229a888(&self->unk_CC, func_ov100_0229d5d4(self, i));
        }
    } while (++i <= 14);
}
