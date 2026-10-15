/* func_02020e64 @ 0x02020e64, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x100 - 0x44];
    void *unk_100;
} UnkStruct_02020e64;

extern unsigned char data_021c21fc[];
extern unsigned char data_021c21b4[];
extern unsigned char data_021c2214[];
extern unsigned char data_021c1d6c[];
extern void *data_020ccf94;
extern unsigned char data_020c8928[];
extern unsigned char data_020c8924[];
extern struct Pair {
    unsigned int a, b;
} data_020d90b0;

extern int func_0207f0f0(unsigned int);
extern int func_02073d90(void *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_02094ffc(void *);
extern void func_0201cf74(void *self, void *buf, unsigned int idx, void *tbl, void *msg);
extern void func_0201cec8(void *self, void *buf);
extern void func_0202da74(void *self, struct Pair p);
extern void func_02068388(void *p, int n);

void func_02020e64(UnkStruct_02020e64 *self)
{
    struct {
        unsigned char buf[0x20];
        unsigned char arr[2];
    } local;
    void *msg;

    if (func_0207f0f0(*(unsigned int *) ((unsigned char *) self->unk_100 + 0x830)) != 0) {
        msg = data_021c21fc;
        goto done;
    }

    if (func_02073d90(data_020ccf94) != 0) {
        if (func_02094ffc((void *) func_02099870((int) func_020984e8())) != 0) {
            msg = data_021c2214;
            goto done;
        }
    }

    msg = data_021c21b4;

done:
    func_0201cf74(self, local.buf, 0, data_020c8928, msg);
    func_0201cf74(self, local.buf, 1, data_020c8924, data_021c1d6c);

    local.arr[0] = 2;
    local.arr[1] = local.arr[0] - 1;

    func_0201cec8(self, local.buf);
    func_0202da74(self, data_020d90b0);
    func_02068388(self->unk_40, 1);
}
