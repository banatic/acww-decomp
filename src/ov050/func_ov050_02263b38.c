/* func_ov050_02263b38 @ 0x02263b38, 0x68 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_02263b38;
extern UnkStruct_02263b38 data_ov050_02265718;
extern UnkStruct_02263b38 data_ov050_02265710;
extern UnkStruct_02263b38 data_ov050_02265708;
extern int data_ov050_02265ed4;
extern UnkStruct_02263b38 data_ov050_02265ed8[3];
typedef struct UnkStruct_02263b38_2 {
    unsigned char pad_00[0xb8];
    UnkStruct_02263b38 v;
} UnkStruct_02263b38_2;

void func_ov050_02263b38(UnkStruct_02263b38_2 *self, int idx)
{
    if ((data_ov050_02265ed4 & 1) == 0) {
        data_ov050_02265ed8[0] = data_ov050_02265718;
        data_ov050_02265ed8[1] = data_ov050_02265710;
        data_ov050_02265ed8[2] = data_ov050_02265708;
        data_ov050_02265ed4 |= 1;
    }
    self->v = data_ov050_02265ed8[idx];
}
