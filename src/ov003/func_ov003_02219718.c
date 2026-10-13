/* func_ov003_02219718 @ 0x02219718, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02219718 UnkStruct_02219718;
struct UnkStruct_02219718 {
    char pad_00[0xd];
    unsigned char flag;
    char pad_0E[0xe];
    unsigned int unk_1C;
};

typedef struct {
    char pad_00[0x7d4];
    UnkStruct_02219718 sub;
} UnkStruct_02219718_2;

extern UnkStruct_02219718_2 *func_02096718(int);

int func_ov003_02219718(void)
{
    UnkStruct_02219718_2 *p = func_02096718(4);

    if (p != 0) {
        if (p->sub.unk_1C == 6) {
            UnkStruct_02219718 *s = &p->sub;

            if (s->flag == 1) {
                s->flag = 2;
                return 1;
            }
        }
    }

    return 0;
}
