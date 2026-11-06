/* event_queue_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203e58c @ 0x0203e58c, 0x34 bytes, Thumb
 * func_0203e55c @ 0x0203e55c, 0x30 bytes, Thumb
 */

struct UnkStruct_0203e55c {
    unsigned char pad_00[0x14];
    unsigned char unk_14;
    unsigned char unk_15;
};

extern struct UnkStruct_0203e58c {
    unsigned char pad_00[0x14];
    unsigned char unk_14;
    unsigned char unk_15;
} *data_021c72b8;
extern int (*data_020da9ec[])(struct UnkStruct_0203e58c *);
extern int (*data_020daaa0[])(struct UnkStruct_0203e55c *);
extern void func_0203df6c(void);

void func_0203e58c(int receiver)
{
    if (data_021c72b8->unk_14 == 3) {
        if (data_020da9ec[data_021c72b8->unk_15](data_021c72b8) != 0) {
            data_021c72b8->unk_14 = 4;
        }
    }
}

void func_0203e55c(int receiver)
{
    if ((*(struct UnkStruct_0203e55c **) &data_021c72b8)->unk_14 == 4) {
        if (data_020daaa0[(*(struct UnkStruct_0203e55c **) &data_021c72b8)->unk_15](
                (*(struct UnkStruct_0203e55c **) &data_021c72b8)) != 0) {
            func_0203df6c();
        }
    }
}
