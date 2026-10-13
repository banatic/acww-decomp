/* func_02011eec @ 0x02011eec, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020118a0(void *p, unsigned int v);

typedef struct {
    unsigned char pad_00[0x250];
    unsigned int unk_250;
} UnkStruct_02011eec;

typedef struct {
    unsigned char pad_00[0x50];
    unsigned int unk_50;
} UnkStruct_02011eec_2;

extern UnkStruct_02011eec data_021c1284;
extern UnkStruct_02011eec_2 data_021c1484;

void func_02011eec(void)
{
    UnkStruct_02011eec *p = &data_021c1284;
    if (data_021c1484.unk_50 != 3) {
        func_020118a0(p, p->unk_250);
        p->unk_250 = 3;
    }
}
