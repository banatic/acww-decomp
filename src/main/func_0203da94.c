/* func_0203da94 @ 0x0203da94, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_0203da8c(void *self);
extern void func_0203da84(void *self);
extern void func_0203da7c(void *self);
extern void func_0203da78(void);
extern void func_0203d9f0(void *self, char *ptr);
extern void func_0203d9f4(void *self);

typedef struct {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
    unsigned char pad_28[4];
    int unk_2C;
} UnkStruct_0203da94;

void func_0203da94(UnkStruct_0203da94 *self)
{
    int v = self->unk_2C;
    if (v == 1) {
        func_0203da8c(self);
    } else if (v == 2) {
        func_0203da84(self);
    } else if (v == 3) {
        func_0203da7c(self);
    } else if (v == 4) {
        func_0203da78();
    } else if (v >= 5 && v <= 15) {
        int t = v - 5;
        int base = self->unk_24 + 0x510;
        func_0203d9f0(self, (char *) (base + t * 0x5c));
    } else if (v == 0x14) {
        func_0203d9f4(self);
    }
}
