/* func_ov131_0229b820 @ 0x0229b820, 0x44 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov002_02209ccc(char *);
extern void *func_ov002_0220b008(char *);
extern void *func_ov130_0229a7ac(char *);
extern int data_ov131_0229b8f0;

struct UnkStruct_0229b820 {
    void *meta;
    char pad_04[0x90];
    char sub_94[0x64];
    char sub_f8[0x1cc];
    char sub_2c4[4];
};

struct UnkStruct_0229b820 *func_ov131_0229b820(void)
{
    struct UnkStruct_0229b820 *self = func_ov002_02207f80(0x1558);
    if (self != 0) {
        func_ov002_0220830c(self);
        self->meta = (void *) &data_ov131_0229b8f0;
        func_ov002_02209ccc(self->sub_94);
        func_ov002_0220b008(self->sub_f8);
        func_ov130_0229a7ac(self->sub_2c4);
    }
    return self;
}
