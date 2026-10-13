/* func_ov107_0229dc58 @ 0x0229dc58, 0x84 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x2318];
} UnkStruct_0229dc58;

extern void func_ov094_0229af40(unsigned char *, int);
extern void func_ov094_0229bbd8(unsigned char *, int);
extern void func_ov094_0229a2b0(unsigned char *, int);
extern void func_ov002_02209e18(unsigned char *);
extern void func_ov002_02209984(unsigned char *, int, int, int _x);
extern int func_ov107_0229c5b0(UnkStruct_0229dc58 *);
extern void func_ov107_0229c2a4(UnkStruct_0229dc58 *, int);

void func_ov107_0229dc58(UnkStruct_0229dc58 *self)
{
    *(int *) (self->data + 0x94) = 0;
    func_ov094_0229af40(self->data + 0x10c, 2);
    func_ov094_0229bbd8(self->data + 0xb6c, 2);
    func_ov094_0229a2b0(self->data + 0xb94, 6);
    self->data[0xb7] = 16;
    func_ov002_02209e18(self->data + 0x229c);
    self->data[0xb5] = 0;
    self->data[0xb8] = 0;
    func_ov002_02209984(self->data + 0x2318, 3, 1, 0);
    if (func_ov107_0229c5b0(self) != 0) {
        func_ov107_0229c2a4(self, 0x40);
    }
    self->data[0xbf] = 0;
}