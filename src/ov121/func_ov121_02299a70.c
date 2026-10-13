/* func_ov121_02299a70 @ 0x02299a70, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299a70 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
};

extern int func_02073d90(struct UnkStruct_02299a70 *p);
extern unsigned int func_020b2300(void);
extern struct UnkStruct_02299a70 *data_020ccf94;

int func_ov121_02299a70(void)
{
    struct UnkStruct_02299a70 *p = data_020ccf94;
    if (func_02073d90(p)) {
        if (p->unk_64 == 0 && func_020b2300() <= 1) {
            goto ret1;
        }
        return 0;
    }
    if (func_020b2300() <= 1) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}
