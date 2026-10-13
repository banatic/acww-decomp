/* func_ov100_0229dd54 @ 0x0229dd54, 0xc4 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208008(void);
extern int func_ov100_0229c60c(void *self, int a, int b);
extern void func_ov100_0229cecc(void *self);
extern void func_ov100_0229cbd4(void *self);
extern void func_ov002_02207d24(void *p, int a);
extern void func_ov002_02207d00(void *p);
extern int func_ov100_0229d630(void *self, unsigned char b);
extern int func_ov100_0229d620(void *self, unsigned char b);
extern int func_ov100_0229d194(void *self, unsigned char b);
extern int func_ov100_0229d158(void *self, unsigned char b);
extern void func_ov100_0229c9e0(void *self, unsigned char b);
extern void func_ov100_0229c994(void *self, unsigned char b);
extern void func_ov100_0229ce24(void *self);

typedef struct {
    char pad_00[0x218c];
    unsigned char unk_218C;
    char pad_218D[0x793];
    unsigned char unk_2920;
    unsigned char unk_2921;
} Object;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
} Globals;

extern Globals data_021fbe40;

void func_ov100_0229dd54(Object *self)
{
    int r = func_ov002_02208008();
    if (func_ov100_0229c60c(self, r, 1) != 0) {
        func_ov100_0229cecc(self);
        func_ov100_0229cbd4(self);
        func_ov002_02207d24((void *) &self->unk_218C, 0);
    } else {
        unsigned short t = data_021fbe40.unk_02;
        if ((t & 1) != 0) {
            if (func_ov100_0229d630(self, self->unk_2921) != 0 || func_ov100_0229d620(self, self->unk_2921) != 0) {
                if (func_ov100_0229d194(self, self->unk_2921) == 0) {
                    if (func_ov100_0229d158(self, self->unk_2921) != 0) {
                        func_ov100_0229c9e0(self, self->unk_2921);
                    } else {
                        func_ov100_0229c994(self, self->unk_2921);
                    }
                }
            }
        } else if ((t & 2) != 0) {
            func_ov100_0229c9e0(self, self->unk_2920);
        } else {
            func_ov100_0229ce24(self);
            func_ov002_02207d00((void *) &self->unk_218C);
        }
    }
}
