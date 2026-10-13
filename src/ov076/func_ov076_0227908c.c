/* func_ov076_0227908c @ 0x0227908c, 0xec bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *, int);
extern int func_020164cc(void *, void *);
extern void func_ov076_02279370(void *, int);
extern void func_020e8870(void *, int, int);
extern void func_ov003_02228400(void *, unsigned int);
extern void func_020912d4(int, void *, int, int);
extern void func_0200442c(void *, int, int, int);
extern void func_0201aff4(void *, int);

typedef struct {
    unsigned int : 12;
    unsigned int field : 16;
    unsigned int : 4;
} Bitfield190;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C; // 0x5c
    unsigned int unk_60; // 0x60
    unsigned int unk_64; // 0x64
    unsigned char pad_68[0x8e - 0x68];
    short unk_8E;            // 0x8e
    unsigned char pad_90[4]; // 0x90 .. 0x94
    short unk_94;            // 0x94
    unsigned char pad_96[0x190 - 0x96];
    Bitfield190 bf190; // 0x190
    unsigned char pad_194[0x334 - 0x194];
} UnkStruct_0227908c;

int func_ov076_0227908c(void *self)
{
    unsigned int arr[3];

    if (func_020164a0((char *) self + 0x334, 0) == 0xf9) {
        if (func_020164cc((char *) self + 0x334, self) != 0) {
            func_ov076_02279370(self, 5);
            goto exit;
        }
    }

    if (func_020164a0((char *) self + 0x334, 0) == 0xf9) {
        if (((UnkStruct_0227908c *) self)->bf190.field == 0xb) {
            *((unsigned char *) self + 0x511) = 0;
            *((unsigned char *) self + 0x510) = 0;
        }
    }

    func_020e8870((char *) self + 0x8e, 0, *(short *) ((char *) self + 0x724));

    if (((UnkStruct_0227908c *) self)->bf190.field == 0x1b) {
        unsigned int *p = (unsigned int *) ((char *) self + 0x5c);
        arr[0] = *(unsigned int *) ((char *) self + 0x5c);
        arr[1] = p[1];
        arr[2] = p[2];
        arr[1] = 0;
        arr[2] += 0x3800;
        func_ov003_02228400(arr, 0x5000);
        func_020912d4(0x16, arr, 0, 0);
        func_0200442c((char *) self + 0x514, 0x7ed, 0x7f, 0);
    }

exit:
    ((UnkStruct_0227908c *) self)->unk_94 = ((UnkStruct_0227908c *) self)->unk_8E;
    func_0201aff4((char *) self + 0x350, ((UnkStruct_0227908c *) self)->unk_8E);
    return 1;
}
