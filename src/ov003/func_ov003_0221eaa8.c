/* func_ov003_0221eaa8 @ 0x0221eaa8, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221eaa8;

extern void *func_ov009_0226539c(UnkStruct_0221eaa8 *s);
extern char data_ov003_022395e8[];
extern char data_ov003_022396ac[];

UnkStruct_0221eaa8 *func_ov003_0221eaa8(UnkStruct_0221eaa8 *s)
{
    s->unk_00 = data_ov003_022395e8;
    s->unk_EC = data_ov003_022396ac;
    func_ov009_0226539c(s);
    return s;
}
