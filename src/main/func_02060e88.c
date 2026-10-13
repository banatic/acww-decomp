/* func_02060e88 @ 0x02060e88, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060e78(void *obj);

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int unk_15A0;
} UnkStruct_02060e88;

int func_02060e88(UnkStruct_02060e88 *obj)
{
    int ret;
    ret = func_02060e78(obj);
    if (((obj->unk_15A0 << 26) >> 29) == ret) {
        return 0;
    } else {
        return 1;
    }
}
