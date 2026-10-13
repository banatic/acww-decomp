/* func_02017ab4 @ 0x02017ab4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02019de4(void *, void *);
extern int func_02057bf0(int);
extern void func_02057b90(int, void *);
extern int func_02057c20(void *);
extern int func_ov004_0222bf50(void);

typedef struct {
    unsigned char unk_00[0x98];
    unsigned char unk_98;
} UnkStruct_02017ab4;

typedef struct {
    unsigned char unk_00[0x28];
    void *unk_28;
} UnkStruct_02017ab4_2;

void func_02017ab4(UnkStruct_02017ab4 *param1, void *param2)
{
    UnkStruct_02017ab4_2 *ptr;
    ptr = (UnkStruct_02017ab4_2 *) func_02019de4(param1, param2);
    if (func_02057bf0(2) == 0) {
        func_02057b90(9, param2);
        if (func_02057c20(ptr->unk_28) != 0) {
            if (func_ov004_0222bf50() != 0) {
                param1->unk_98 = 9;
            }
        }
    }
}
