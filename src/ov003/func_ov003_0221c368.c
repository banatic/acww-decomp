/* func_ov003_0221c368 @ 0x0221c368, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_022387a8;
extern char data_ov003_0223886c;
extern void func_ov009_0226539c(void *p);
extern void func_020edf54(void *p);

struct UnkStruct_0221c368 {
    char *unk_00;
    char pad_04[0xE8];
    char *unk_EC;
};

struct UnkStruct_0221c368 *func_ov003_0221c368(struct UnkStruct_0221c368 *p)
{
    p->unk_00 = &data_ov003_022387a8;
    p->unk_EC = &data_ov003_0223886c;
    func_ov009_0226539c(p);
    func_020edf54(p);
    return p;
}
