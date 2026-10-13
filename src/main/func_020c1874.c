/* func_020c1874 @ 0x020c1874, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct System {
    char pad_00[0x654];
    int unk_654;
};
extern struct System *data_021fbbe0;
extern void func_020c26b4(struct System *, int);

void func_020c1874(void)
{
    if (data_021fbbe0 != 0 && data_021fbbe0->unk_654 != 5) {
        func_020c26b4(data_021fbbe0, 5);
    }
}
