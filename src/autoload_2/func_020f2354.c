/* func_020f2354 @ 0x020f2354, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *NNS_SndCaptureChangeOutputEffect(void *);

void *func_020f2354(void *self, void *val)
{
    struct UnkStruct_020f2354 {
        char pad[0x50];
        void *volatile field;
    } *p = (struct UnkStruct_020f2354 *) self;

    p->field = val;
    return NNS_SndCaptureChangeOutputEffect(p->field);
}
