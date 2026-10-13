/* func_02087358 @ 0x02087358, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00, unk_01, unk_02, unk_03, unk_04, unk_05, unk_06, unk_07;
} UnkStruct_02087358;

extern void func_0209e474(UnkStruct_02087358 *out);
extern void MI_CpuCopy8(const void *src, void *dst, int size);
extern void func_0209e140(UnkStruct_02087358 *info, int flag);

void func_02087358(void *self, void *src)
{
    UnkStruct_02087358 info;
    char *out = (char *) self;
    *(unsigned int *) &info = 0;
    *(unsigned int *) ((char *) &info + 4) = 0;
    if (src == 0) {
        func_0209e474(&info);
    } else {
        MI_CpuCopy8(src, &info, 8);
    }
    if (info.unk_05 == 0) {
        if (info.unk_04 == 1) {
            if (info.unk_03 == 1) {
                goto skip;
            }
        }
    }
    if (info.unk_02 < 6) {
        func_0209e140(&info, 1);
    }
skip:
    out[2] = info.unk_05;
    out[1] = info.unk_04;
    out[0] = info.unk_03;
}
