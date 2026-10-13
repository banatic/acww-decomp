/* func_ov003_0221e8c4 @ 0x0221e8c4, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223948c;
extern int data_ov003_02239550;
extern void func_020b7f60(void *);
extern void func_020565b0(void *);
extern void func_ov009_0226539c(void *);
extern void func_020edf54(void *);

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221e8c4;

UnkStruct_0221e8c4 *func_ov003_0221e8c4(UnkStruct_0221e8c4 *p)
{
    p->unk_00 = &data_ov003_0223948c;
    p->unk_EC = &data_ov003_02239550;
    func_020b7f60((char *) p + 0x2d8);
    func_020565b0((char *) p + 0x2b8);
    func_ov009_0226539c(p);
    func_020edf54(p);
    return p;
}
