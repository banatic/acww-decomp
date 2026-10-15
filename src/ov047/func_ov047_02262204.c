/* func_ov047_02262204 @ 0x02262204, 0x34 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov047_022624f4(void *, int);

struct UnkStruct_02262204 {
    char pad_00[0x618];
    int unk_618;
    char pad_61C[0x11A];
    unsigned char unk_736;
};

int func_ov047_02262204(struct UnkStruct_02262204 *obj)
{
    if (func_02014868(&obj->unk_618) == 0) {
        obj->unk_736 = 0;
        func_0203e020(obj);
        func_ov047_022624f4(obj, 4);
    }
    return 1;
}
