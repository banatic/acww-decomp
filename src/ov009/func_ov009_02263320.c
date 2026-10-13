/* func_ov009_02263320 @ 0x02263320, 0x24 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xEC];
    char sub[0x1E];
    char flag;
} UnkStruct_02263320;

extern void func_020a8164(void *a, void *b);

extern unsigned char data_ov009_02265a18[];

void func_ov009_02263320(UnkStruct_02263320 *self)
{
    volatile long long unused;
    (void) &unused;
    func_020a8164(&self->sub, (void *) data_ov009_02265a18);
    self->flag = 0;
}
