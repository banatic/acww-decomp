/* func_02057c44 @ 0x02057c44, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02057c44;

typedef struct {
    char pad_00[0x60];
    UnkStruct_02057c44 sub;
} UnkStruct_02057c44_2;

extern UnkStruct_02057c44_2 *data_021c9350;

int func_02057c44(UnkStruct_02057c44 *out)
{
    int result = 0;
    if (data_021c9350) {
        UnkStruct_02057c44 *p = &data_021c9350->sub;
        out->a = data_021c9350->sub.a;
        out->b = p->b;
        out->c = p->c;
        result = 1;
    }
    return result;
}
