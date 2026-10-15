/* func_020388f0 @ 0x020388f0, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xBC];
    int unk_BC;
} UnkStruct_020388f0;

extern int func_02055454(void *arg);

void func_020388f0(UnkStruct_020388f0 *self)
{
    if (self->unk_BC != 0) {
        func_02055454((char *) self + 4);
        self->unk_BC = 0;
    }
}
