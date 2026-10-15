/* func_020194c8 @ 0x020194c8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8E];
    short unk_8E;
    char pad_90[0x2C0];
    char unk_350;
} UnkStruct_020194c8;

typedef struct {
    char pad_00[0x98];
    unsigned char unk_98;
} UnkStruct_020194c8_2;

extern int func_0201afec(void *addr);
extern int func_02019804(UnkStruct_020194c8_2 *a1, UnkStruct_020194c8 *a2);

void func_020194c8(UnkStruct_020194c8_2 *a1, UnkStruct_020194c8 *a2)
{
    if (a2->unk_8E == func_0201afec(&a2->unk_350)) {
        func_02019804(a1, a2);
        a1->unk_98 = 1;
    }
}
