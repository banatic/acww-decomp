/* func_0205992c @ 0x0205992c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0205992c {
    char pad_00[0xcc];
    int unk_CC;
    int unk_D0;
};

extern int func_0205996c(struct UnkStruct_0205992c *, int, int);

int func_0205992c(struct UnkStruct_0205992c *p, int val)
{
    int result = 0;
    if (func_0205996c(p, val, 1) == 1) {
        p->unk_D0 = p->unk_CC;
        p->unk_CC = val;
        result = 1;
    } else {
        if (func_0205996c(p, val, 0) == 1) {
            result = 1;
        }
    }
    return result;
}
