/* func_ov096_0229eb98 @ 0x0229eb98, 0xa0 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x2419];
} UnkStruct_0229eb98;

extern int func_ov096_0229f290(UnkStruct_0229eb98 *self, int byte);
extern int func_ov096_0229f200(UnkStruct_0229eb98 *self, int byte);
extern int func_0206fe54(int val);
extern void func_0208aa60(unsigned char *dst, int a, int b);
extern int func_ov096_0229f830(UnkStruct_0229eb98 *self, int byte);
extern int func_ov096_0229f7ac(UnkStruct_0229eb98 *self, int byte);
extern void func_ov094_0229abb8(unsigned char *a, unsigned char *b, int c);
extern int func_ov096_0229f820(UnkStruct_0229eb98 *self, int byte);
extern int func_ov096_0229f548(UnkStruct_0229eb98 *self, int byte);
extern void func_ov094_0229b9b4(unsigned char *a, unsigned char *b, int c);

void func_ov096_0229eb98(UnkStruct_0229eb98 *self)
{
    int v1, raw2, v2;

    v1 = func_ov096_0229f290(self, self->data[0xb3]) - 0x6d;
    raw2 = func_ov096_0229f200(self, self->data[0xb3]);
    v2 = raw2 - 0x78;
    if (func_0206fe54(raw2) != 0) {
        v2 -= 8;
    }
    func_0208aa60(self->data + 0x2418, v1, v2);

    if (func_ov096_0229f830(self, self->data[0xb3]) != 0) {
        int v3;
        v3 = func_ov096_0229f7ac(self, self->data[0xb3]);
        func_ov094_0229abb8(self->data + 0x358, self->data + 0x2418, v3);
    } else {
        if (func_ov096_0229f820(self, self->data[0xb3]) != 0) {
            int v4;
            v4 = func_ov096_0229f548(self, self->data[0xb3]);
            func_ov094_0229b9b4(self->data + 0xdb8, self->data + 0x2418, v4);
        }
    }
}
