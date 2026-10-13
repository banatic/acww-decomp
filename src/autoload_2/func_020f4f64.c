/* func_020f4f64 @ 0x020f4f64, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    char unk_0C;
} UnkStruct_020f4f64;

extern void NNS_SndHandleReleaseSeq(void *);

UnkStruct_020f4f64 *func_020f4f64(UnkStruct_020f4f64 *self)
{
    NNS_SndHandleReleaseSeq(&self->unk_0C);
    return self;
}
