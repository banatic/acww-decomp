/* func_0209d200 @ 0x0209d200, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b9c(void *arg);

struct UnkStruct_0209d200;

struct UnkStruct_0209d200_2 {
    unsigned short unk_00;
    unsigned char pad_02[6];
    int unk_08;
    struct UnkStruct_0209d200 *unk_0C;
};

struct UnkStruct_0209d200 {
    char unk_00;
    char pad_01[3];
    void *unk_04;
    char pad_08[20];
};

void func_0209d200(struct UnkStruct_0209d200_2 *r4, unsigned short *r1)
{
    unsigned short val = *r1;
    if (val != 0xffff) {
        struct UnkStruct_0209d200 *entry = &r4->unk_0C[val];
        entry->unk_00 = 0;
        r4->unk_00 = *r1;
        *r1 = 0xffff;
        if (entry->unk_04 != 0) {
            func_020e9b9c(entry->unk_04);
        }
        r4->unk_08--;
    }
}
