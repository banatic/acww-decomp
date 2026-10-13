/* func_02070cf4 @ 0x02070cf4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_Copy33To43_(void *a, void *b);
extern void MTX_Concat43(void *a, void *b, void *c);
extern char data_021cfe68[];

typedef struct {
    unsigned int a, b, c;
} Src;
typedef struct {
    unsigned char pad_00[0x24];
    unsigned int unk_24, unk_28, unk_2C;
} UnkStruct_02070cf4;

void func_02070cf4(void *param0, Src *param1)
{
    UnkStruct_02070cf4 local;
    MTX_Copy33To43_(param0, &local);
    local.unk_24 = param1->a;
    local.unk_28 = param1->b;
    local.unk_2C = param1->c;
    MTX_Concat43(&local, data_021cfe68, data_021cfe68);
}
