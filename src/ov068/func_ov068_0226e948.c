/* func_ov068_0226e948 @ 0x0226e948, 0x68 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *);
extern void func_ov068_0226e878(void *, int);
extern void *func_020984e8(void);
extern int func_020a12c0(void);
extern int func_020a12d4(void);
extern void func_02098fd0(void *, int);
extern void func_02035684(int, int, int);

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x458];
    int unk_4E8;
    char pad_4EC[0x228];
    short unk_714;
} UnkStruct_0226e948;

int func_ov068_0226e948(UnkStruct_0226e948 *self)
{
    void *p;
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    func_ov068_0226e878(self, 0);
    self->unk_714 = self->unk_8E;
    self->unk_4E8 |= 2;
    p = func_020984e8();
    if (p != 0) {
        if (func_020a12c0() == 0) {
            if (func_020a12d4() == 0) {
                func_02098fd0(p, 1);
            }
        }
    }
    func_02035684(0x13, 0xf, 0);
    return 1;
}
