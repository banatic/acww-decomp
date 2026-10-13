/* func_ov075_02278ac0 @ 0x02278ac0, 0x2c bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);

struct UnkStruct_02278ac0 {
    unsigned char pad_00[0x561];
    unsigned char flag;
    unsigned char pad_562[0xB6];
    unsigned char sub;
};

int func_ov075_02278ac0(struct UnkStruct_02278ac0 *self)
{
    if (self->flag) {
        if (func_02014868(&self->sub) == 0) {
            return 1;
        }
    }
    return 0;
}
