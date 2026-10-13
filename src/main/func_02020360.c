/* func_02020360 @ 0x02020360, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
} UnkStruct_02020360;

extern unsigned char data_021c1e14[];
extern unsigned char data_021c1d6c[];
extern unsigned char data_020c8928[];
extern unsigned char data_020c8924[];
extern struct Pair {
    unsigned int a, b;
} data_020d91d8;

extern void func_0201cf74(void *self, void *buf, unsigned int idx, void *tbl, void *msg);
extern void func_0201cec8(void *self, void *buf);
extern void func_0202da74(void *self, struct Pair p);
extern void func_02068388(void *p, int n);

void func_02020360(UnkStruct_02020360 *self)
{
    struct {
        unsigned char buf[0x20];
        unsigned char arr[2];
    } local;

    func_0201cf74(self, local.buf, 0, data_020c8928, data_021c1e14);
    func_0201cf74(self, local.buf, 1, data_020c8924, data_021c1d6c);

    local.arr[0] = 2;
    local.arr[1] = local.arr[0] - 1;

    func_0201cec8(self, local.buf);
    func_0202da74(self, data_020d91d8);
    func_02068388(self->unk_40, 1);
}
