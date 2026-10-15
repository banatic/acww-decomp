/* func_ov003_0221e9dc @ 0x0221e9dc, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad0[0x10a];
    unsigned char unk_10A;
    unsigned char pad_10B[0x12c - 0x10b];
    int unk_12C;
    unsigned char pad_130[0x2b4 - 0x130];
    unsigned short unk_2B4;
} UnkStruct_0221e9dc;

typedef struct {
    unsigned char pad0[0x58];
    unsigned int unk_58;
} UnkStruct_0221e9dc_2;

extern void func_020a8164(void *p, void *d);
extern void *func_02062f90(void *dst, void *arg);
extern void func_02068404(int, int, void *);
extern void *func_02062f4c(void *dst);
extern char data_ov003_02239724;
extern UnkStruct_0221e9dc_2 data_021f39a8;

void func_ov003_0221e9dc(UnkStruct_0221e9dc *self)
{
    struct {
        short pad0;
        unsigned short val;
    } local1;
    unsigned char buffer[0x2c];
    unsigned short computed;

    func_020a8164((unsigned char *) self + 0xec, &data_ov003_02239724);

    self->unk_10A = (unsigned char) ((self->unk_2B4 % 0xe) + 1);

    if (data_021f39a8.unk_58 < 5) {
        computed = (unsigned short) (data_021f39a8.unk_58 + 0x1518);
    } else {
        computed = 0x1518;
    }
    local1.val = computed;

    func_02062f90(buffer, &local1.val);
    func_02068404(self->unk_12C, 1, buffer);
    func_02062f4c(buffer);
}
