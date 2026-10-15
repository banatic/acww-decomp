/* func_ov003_02215570 @ 0x02215570, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02215620(void *, unsigned char);
extern void func_ov003_0221561c(void *, unsigned char);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern void func_0205eae0(void *, int, int, int);
extern int func_0200f328(void *, int);
extern int func_02073908(unsigned int *, unsigned int);
extern int func_0203b144(void);
extern unsigned int *data_020ccf94;

typedef struct {
    unsigned char pad_00[0x5a0];
    unsigned char addr_5a0;
    unsigned char pad_5A1[0x2f];
    unsigned int src[3];
    unsigned char pad_5DC[0x1f8];
    unsigned char addr_7d4;
    unsigned char pad_7D5[0x2b];
    unsigned int unk_800;
    unsigned char pad_804[0xc0];
    unsigned int dest1;
    unsigned int dest2;
    unsigned int dest3;
    unsigned char pad_8D0[0x20];
    unsigned char addr_8f0;
} UnkStruct_02215570;

void func_ov003_02215570(UnkStruct_02215570 *self, const unsigned char *param, int previous)
{
    unsigned char byte;
    unsigned int *src;

    byte = param[0xc];

    func_ov003_02215620(&self->addr_7d4, byte);
    func_ov003_0221561c(&self->addr_8f0, byte);
    func_020109a0(self, 0x56, 3, 0);
    func_0205eae0(&self->addr_5a0, 0x19, 3, 0);
    func_0200f328(self, 0x84c);
    func_0200f328(self, 0x84e);

    src = self->src;
    self->dest1 = src[0];
    self->dest2 = src[1];
    self->dest3 = src[2];

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_0203b144();
    }
}
