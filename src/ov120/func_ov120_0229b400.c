/* func_ov120_0229b400 @ 0x0229b400, 0x34 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229b400_2 {
    char data[0x6C];
} UnkStruct_0229b400_2;

typedef struct UnkStruct_0229b400 {
    char pad_00[0xA0];
    unsigned char count;
    char pad_A1[0x57];
    UnkStruct_0229b400_2 arr[13];
} UnkStruct_0229b400;

UnkStruct_0229b400_2 *func_ov120_0229b400(UnkStruct_0229b400 *self)
{
    if (self->count >= 13) {
        return (UnkStruct_0229b400_2 *) ((char *) self + 0x608);
    } else {
        self->count++;
        return (UnkStruct_0229b400_2 *) ((char *) self + 0xF8 + (self->count - 1) * sizeof(UnkStruct_0229b400_2));
    }
}
