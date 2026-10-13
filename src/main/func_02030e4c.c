/* func_02030e4c @ 0x02030e4c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c31e8; // 0x021c31e8
typedef struct {
    unsigned char pad_00[0x138];
} UnkStruct_02030e4c;
extern UnkStruct_02030e4c data_021c31ec[]; // 0x021c31ec
extern UnkStruct_02030e4c *data_020da1a8;  // 0x020da1a8

extern int func_020342ac(int *ptr, int param);

void func_02030e4c(int a)
{
    if (func_020342ac(&data_021c31e8, a) == 0) {
        if (a < 0) {
            func_020342ac(&data_021c31e8, 0);
            data_020da1a8 = &data_021c31ec[data_021c31e8];
        } else {
            func_020342ac(&data_021c31e8, 7);
            data_020da1a8 = &data_021c31ec[data_021c31e8];
        }
    } else {
        data_020da1a8 = &data_021c31ec[data_021c31e8];
    }
}
