/* func_ov066_02267348 @ 0x02267348, 0xbc bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int type;
    int val;
} UnkStruct_02267348;

extern UnkStruct_02267348 *data_ov066_0226bdec;

int func_ov066_02267348(void)
{
    int result = 0;
    UnkStruct_02267348 *p = data_ov066_0226bdec;
    switch (p->type) {
        case 0:
            result = (p->val == 2);
            break;
        case 1:
            result = (p->val == 3);
            break;
        case 2:
            result = (p->val == 4);
            break;
        case 3:
            result = (p->val == 10);
            break;
        case 4:
            result = (p->val == 7);
            break;
        case 5:
            result = (p->val == 11);
            break;
        case 6:
            result = (p->val == 10) || (p->val == 11);
            break;
    }
    return result;
}
