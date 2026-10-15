/* func_ov003_0221fca4 @ 0x0221fca4, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221ef78(void *);
extern void *func_02057694(void *);
extern int func_ov003_0221f1f4(void *);
extern void *func_ov003_0221f5f4(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern int data_ov003_02239a58;
extern int data_020da13c;

struct UnkStruct_0221fca4 {
    void *unk_00;
};

void *func_ov003_0221fca4(struct UnkStruct_0221fca4 *this)
{
    this->unk_00 = (void *) &data_ov003_02239a58;
    func_ov003_0221ef78((char *) this + 0x310);
    func_02057694((char *) this + 0x280);
    func_02057694((char *) this + 0x1f0);
    func_ov003_0221f1f4((char *) this + 0x150);
    func_ov003_0221f5f4((char *) this + 0x54);
    this->unk_00 = (void *) &data_020da13c;
    func_020ee62c(this);
    func_020edf54(this);
    return this;
}
