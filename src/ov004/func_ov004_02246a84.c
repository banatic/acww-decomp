/* func_ov004_02246a84 @ 0x02246a84, 0xe8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short a, b;
    int c, d, e, unk_10, g, h, i;
} Settings;
typedef struct {
    char pad_00[0xfc];
    Settings first;
    char pad_11C[0x2c];
    Settings second;
    char pad_168[0xb4];
    short state[3];
} Object;
extern Settings data_ov004_022569ac, data_ov004_0225698c;
extern char data_ov004_0225695c[];
extern void func_0203c97c(void *, void *);
extern void func_0203ad58(void);
void func_ov004_02246a84(Object *self)
{
    short *s = self->state;
    s[0] = 0;
    s[1] = 0;
    s[2] = 2;
    self->first.a = data_ov004_022569ac.a;
    self->first.b = data_ov004_022569ac.b;
    self->first.c = data_ov004_022569ac.c;
    self->first.d = data_ov004_022569ac.d;
    self->first.e = data_ov004_022569ac.e;
    self->first.unk_10 = data_ov004_022569ac.unk_10;
    self->first.g = data_ov004_022569ac.g;
    self->first.h = data_ov004_022569ac.h;
    self->first.i = data_ov004_022569ac.i;
    self->second.a = data_ov004_0225698c.a;
    self->second.b = data_ov004_0225698c.b;
    self->second.c = data_ov004_0225698c.c;
    self->second.d = data_ov004_0225698c.d;
    self->second.e = data_ov004_0225698c.e;
    self->second.unk_10 = data_ov004_0225698c.unk_10;
    self->second.g = data_ov004_0225698c.g;
    self->second.h = data_ov004_0225698c.h;
    self->second.i = data_ov004_0225698c.i;
    func_0203c97c(self, data_ov004_0225695c);
    func_0203ad58();
}
