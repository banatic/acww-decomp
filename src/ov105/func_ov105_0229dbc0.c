/* func_ov105_0229dbc0 @ 0x0229dbc0, 0x104 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov105_0229dafc(void *this);
extern void func_ov002_0220a1dc(void *this);
extern unsigned char *func_ov002_02208098(void *this, unsigned char value);
extern void func_ov105_0229cfc0(void *this);
extern void func_ov105_0229c5fc(void *this);
extern void func_ov105_0229c62c(void *this);
extern void *func_ov002_02208008(void *this);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_0220a768(void *this, int amount);
extern int func_ov002_0220a72c(void *this, int amount);
extern void func_ov105_0229cf10(void *this, int a, int b);

struct Global {
    unsigned short pad_00;
    unsigned short flags;
};

extern struct Global data_021fbe40;

struct UnkStruct_0229dbc0 {
    char pad_00[0x2c2];                 // 0x0000
    unsigned char unk_2C2;              // 0x02c2
    char pad_2C3[0x24a4 - 0x2c2 - 1];   // 0x02c3
    char unk_24A4;                      // 0x24a4
    char pad_24A5[0x5fb8 - 0x24a4 - 1]; // 0x24a5
    char unk_5FB8;                      // 0x5fb8
};

void func_ov105_0229dbc0(struct UnkStruct_0229dbc0 *self)
{
    unsigned short flags;
    unsigned char old;
    void *p;
    int a;
    int b;

    if (func_ov002_02208014(self) != 0) {
        func_ov105_0229dafc(self);
        return;
    }

    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov002_0220a1dc(&self->unk_24A4);
        func_ov002_02208098(self, 0x1f);
        return;
    }

    if (flags & 2) {
        func_ov105_0229cfc0(self);
        func_ov105_0229c5fc(self);
        return;
    }

    if (flags & 8) {
        func_ov105_0229cfc0(self);
        func_ov105_0229c62c(self);
        return;
    }

    old = self->unk_2C2;
    p = func_ov002_02208008(self);
    if (func_ov002_022088ac(p) != 0) {
        if (self->unk_2C2 != 0) {
            self->unk_2C2--;
        }
    } else {
        if (func_ov002_0220889c(p) != 0) {
            if (self->unk_2C2 < 1) {
                self->unk_2C2++;
            }
        }
    }

    if (old != self->unk_2C2) {
        if (self->unk_2C2 != 0) {
            a = func_ov002_0220a768(&self->unk_5FB8, 4);
            b = func_ov002_0220a72c(&self->unk_5FB8, 4);
            func_ov105_0229cf10(self, a, b);
        } else {
            a = func_ov002_0220a768(&self->unk_5FB8, 3);
            b = func_ov002_0220a72c(&self->unk_5FB8, 3);
            func_ov105_0229cf10(self, a, b);
        }
    }
}
