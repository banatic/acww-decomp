/* func_ov003_0221fdb8 @ 0x0221fdb8, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221fdc8(void *state);

typedef struct {
    char pad_00[0x1c];
    void (*callback)(void *);
    char pad_20[0x70];
    unsigned char unk_90;
} UnkStruct_0221fdb8;

void func_ov003_0221fdb8(UnkStruct_0221fdb8 *obj)
{
    obj->callback = func_ov003_0221fdc8;
    obj->unk_90 = 2;
}
