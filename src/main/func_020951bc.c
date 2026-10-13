/* func_020951bc @ 0x020951bc, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[14];
    unsigned short unk_0E;
} UnkStruct_020951bc;
extern int func_02064294(UnkStruct_020951bc *p);
int func_020951bc(UnkStruct_020951bc *p)
{
    if (func_02064294(p) == 1 && p->unk_0E != 0) {
        return 1;
    }
    return 0;
}
