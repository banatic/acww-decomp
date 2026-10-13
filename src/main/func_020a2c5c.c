/* func_020a2c5c @ 0x020a2c5c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209f180(void *ptr);
extern int data_021dc7a8;

typedef struct {
    unsigned char pad_00[0xA1];
    unsigned char unk_A1;
    unsigned char pad_A2[0x69];
    unsigned char unk_10B;
} UnkStruct_020a2c5c;

void func_020a2c5c(UnkStruct_020a2c5c *ptr)
{
    ptr->unk_A1 = 0;
    if (func_0209f180(&data_021dc7a8) == 0) {
        ptr->unk_10B = 1;
    } else {
        ptr->unk_10B = 0;
    }
}
