/* func_02012588 @ 0x02012588, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082d04(char *p);

struct UnkStruct_02012588 {
    char pad_00[4];
    char unk_04;
};

struct UnkStruct_02012588 *func_02012588(struct UnkStruct_02012588 *p)
{
    func_02082d04(&p->unk_04);
    return p;
}
