/* func_02003cc0 @ 0x02003cc0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x10];
    int unk_10;
} UnkStruct_02003cc0;
extern int func_020ec1e8(void);
int func_02003cc0(UnkStruct_02003cc0 *p)
{
    unsigned int ok = 0;
    unsigned int v;
    v = (unsigned int) func_020ec1e8();
    if (v != 0) {
        v = (unsigned int) func_020ec1e8();
        if (v != 6) {
            ok = 1;
        }
    }
    if (ok > 0 && p->unk_10 == 0) {
        return 1;
    }
    return 0;
}
