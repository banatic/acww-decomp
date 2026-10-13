/* func_020030dc @ 0x020030dc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d7220;
extern int func_02064b18(int *);

typedef struct {
    char pad_00[0x48];
    volatile int unk_48;
} UnkStruct_020030dc;

int func_020030dc(UnkStruct_020030dc *s)
{
    s->unk_48 = func_02064b18(&data_020d7220);
    if (s->unk_48) {
        return 1;
    } else {
        return 0;
    }
}
