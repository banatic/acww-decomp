/* func_020f2354 @ 0x020f2354, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndCaptureChangeOutputEffect(int effect);

void func_020f2354(void *self, int effect)
{
    struct UnkStruct_020f2354 {
        char pad[0x50];
        volatile int field;
    } *p = (struct UnkStruct_020f2354 *) self;

    p->field = effect;
    NNS_SndCaptureChangeOutputEffect(p->field);
}
