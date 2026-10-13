/* func_020160b4 @ 0x020160b4, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
} UnkStruct_020160b4;

extern int func_0206837c(void *);

int func_020160b4(UnkStruct_020160b4 *obj)
{
    int ret = 0;
    if (obj->unk_40) {
        ret = func_0206837c(obj->unk_40);
    }
    return ret;
}
