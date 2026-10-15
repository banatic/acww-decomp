/* func_020f64c8 @ 0x020f64c8, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int flags;
    char pad_04[6];
    char unk_0A;
} UnkStruct_020f64c8;

extern int func_020eed18(UnkStruct_020f64c8 *obj, int val);
extern void NNS_SndHandleReleaseSeq(UnkStruct_020f64c8 *obj);

void func_020f64c8(UnkStruct_020f64c8 *obj)
{
    int b = 0;
    obj->unk_0A = 0;
    if (obj->flags) {
        b = 1;
    }
    if (b != 0) {
        func_020eed18(obj, 0);
    }
    NNS_SndHandleReleaseSeq(obj);
}
