/* func_ov055_022607a0 @ 0x022607a0, 0xd0 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned char pad_44[0xb0 - 0x44];
    unsigned char *unk_B0;
} UnkStruct_022607a0;

extern void func_02073090(void);
extern int func_020ead48(void);
extern void func_020ead7c(void);
extern void func_02074958(void);
extern void func_0206844c(unsigned int a, void *b, void *c);
extern void func_ov055_02260870(UnkStruct_022607a0 *self, int mode);
extern void *data_ov055_02260e60;

typedef struct {
    unsigned short pad_00;
    unsigned short unk_02;
} G_021fbe40_t;

extern G_021fbe40_t data_021fbe40;

#define HWREG (*(unsigned short *) 0x027fffa8)
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

void func_ov055_022607a0(UnkStruct_022607a0 *self)
{
    int bit;
    int r5;
    unsigned char *p;
    char buf[4];
    int cond;

    bit = ((HWREG & 0x8000) >> 15) != 0;
    r5 = 0;
    p = self->unk_B0;
    if (p[0x711] == 1 && bit == 0) {
        r5 = 1;
    }
    p[0x711] = (unsigned char) bit;

    func_02073090();
    if (func_020ead48() != 0) {
        func_02074958();
        buf[0] = 0x3c;
        func_0206844c(self->unk_40, &buf[0], data_ov055_02260e60);
        func_ov055_02260870(self, 2);
    } else {
        if ((data_021fbe40.unk_02 & 1) == 0) {
            cond = (data_021fbdd8 != 0 && data_021fbddc != 0);
            if (cond == 0 && r5 == 0) {
                return;
            }
        }
        func_02073090();
        func_020ead7c();
        buf[1] = 0x3a;
        func_0206844c(self->unk_40, &buf[1], data_ov055_02260e60);
        func_ov055_02260870(self, 3);
    }
}
