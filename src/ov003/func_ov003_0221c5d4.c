/* func_ov003_0221c5d4 @ 0x0221c5d4, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b374c(void *);
extern int func_020b3848(void);
extern void func_ov003_0221c438(void *, unsigned int, int);
extern void func_0204f818(int *, int *, void *);
extern void func_02030920(int, int, int);

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C;
    unsigned char pad_5D[0x198 - 0x5d];
    unsigned int unk_198;
    unsigned char pad_19C[0x2b4 - 0x19c];
    unsigned char unk_2B4;
} UnkStruct_0221c5d4;

extern unsigned char data_021f34b0[];

int func_ov003_0221c5d4(UnkStruct_0221c5d4 *self)
{
    unsigned int old;
    int v0;
    int v1;
    int i;
    int result;

    old = self->unk_198;
    func_020b374c((void *) data_021f34b0);
    result = func_020b3848();
    func_ov003_0221c438(&self->unk_2B4, old, result);
    func_0204f818(&v0, &v1, &self->unk_5C);
    for (i = -2; i <= 2; i++) {
        func_02030920(v0 + i, v1 - 1, 15);
    }
    return 1;
}
