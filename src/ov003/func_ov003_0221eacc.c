/* func_ov003_0221eacc @ 0x0221eacc, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226552c(void *obj);
extern char data_ov003_022395e8;
extern char data_ov003_022396ac;

typedef struct UnkStruct_0221eacc {
    void *unk_00;
    unsigned char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221eacc;

void *func_ov003_0221eacc(void *arg)
{
    UnkStruct_0221eacc *p = arg;
    func_ov009_0226552c(arg);
    p->unk_00 = &data_ov003_022395e8;
    p->unk_EC = &data_ov003_022396ac;
    return arg;
}
