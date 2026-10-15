/* func_ov109_0229d2d0 @ 0x0229d2d0, 0x98 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x218c];
    unsigned char unk_218C;
    char pad_218D[0x29d0 - 0x218d];
    unsigned char unk_29D0;
    char pad_29D1[0x29d9 - 0x29d1];
    unsigned char unk_29D9;
} UnkStruct_0229d2d0;

extern unsigned char data_021fbdd8;
extern int func_ov109_0229cae0(void *p, int a);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov002_02207ce4(void *p, int a);
extern void func_ov109_0229d7b4(void *p);
extern int func_ov002_02207cc0(int);
extern void func_ov109_0229c418(void *p, int a, int b);
extern void func_ov002_02207d00(void *p);

void func_ov109_0229d2d0(UnkStruct_0229d2d0 *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov109_0229cae0(self, self->unk_29D0) != 0) {
            func_ov002_02208098(self, 0);
            func_ov002_02207ce4(&self->unk_218C, 0x3c);
            return;
        }
        func_ov002_02208098(self, 3);
        func_ov109_0229d7b4(self);
        return;
    }
    if (func_ov109_0229cae0(self, self->unk_29D0) != 0) {
        goto L34a;
    }
    if (func_ov002_02207cc0((int) &self->unk_218C) == 0) {
        goto L34a;
    }
    if (self->unk_29D9 != 0) {
        self->unk_29D9--;
    } else {
        func_ov109_0229c418(self, self->unk_29D0, 1);
        func_ov002_02208098(self, 2);
    }
    goto L352;
L34a:
    func_ov002_02207d00(&self->unk_218C);
L352:;
}
