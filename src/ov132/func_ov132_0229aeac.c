/* func_ov132_0229aeac @ 0x0229aeac, 0x2c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov132_0229b910[];
extern int func_ov002_0220a72c(void *p, int n);

struct UnkStruct_0229aeac {
    char pad_00[0x1502];
    unsigned char flag;
};

int func_ov132_0229aeac(struct UnkStruct_0229aeac *obj)
{
    if (obj->flag == 2) {
        return func_ov002_0220a72c((char *) obj + 0xf8, 6);
    } else {
        return data_ov132_0229b910[obj->flag];
    }
}
