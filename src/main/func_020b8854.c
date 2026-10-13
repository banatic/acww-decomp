/* func_020b8854 @ 0x020b8854, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xfc];
    int unk_FC;
    unsigned char pad_100[8];
    int unk_108;
} UnkStruct_020b8854;

int func_020b8854(UnkStruct_020b8854 *arg0)
{
    int val;
    if (arg0->unk_FC != 0) {
        val = 1;
    } else {
        val = 0;
    }
    if (arg0->unk_108 == 0) {
        val = 0;
    }
    return val;
}
