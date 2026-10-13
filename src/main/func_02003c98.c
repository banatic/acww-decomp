/* func_02003c98 @ 0x02003c98, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ec1e8(void);

typedef struct {
    char pad_00[0x15];
    unsigned char unk_15;
} UnkStruct_02003c98;

int func_02003c98(UnkStruct_02003c98 *obj)
{
    int r = func_020ec1e8();
    return obj->unk_15 == (r == 3 || r == 4);
}
