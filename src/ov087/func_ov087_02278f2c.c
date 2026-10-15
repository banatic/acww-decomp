/* func_ov087_02278f2c @ 0x02278f2c, 0x74 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_02278f2c;

extern void *func_020984e8(void);
extern int func_02099640(void *);
extern int func_02099020(void *, int);
extern void func_02098ff8(void *, int);
extern int func_0202ea80(int, int);
extern int func_020644cc(int);
extern char data_ov087_02279598;

void func_ov087_02278f2c(void *self, UnkStruct_02278f2c *out)
{
    void *obj;

    obj = func_020984e8();
    func_02099640(obj);
    out->unk_00 = (void *) &data_ov087_02279598;
    if (func_02099020(obj, 0xf) == 0) {
        out->unk_04 = 0;
        func_02098ff8(obj, 0xf);
        func_0202ea80(0x19, 1);
    } else if (func_0202ea80(0x19, 1) == 0) {
        out->unk_04 = 2;
    } else if (func_020644cc(2) == 0 || func_0202ea80(0x1a, 0) != 0) {
        out->unk_04 = 3;
    } else {
        out->unk_04 = 0x10;
    }
}
