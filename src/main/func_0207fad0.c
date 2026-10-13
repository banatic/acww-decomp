/* func_0207fad0 @ 0x0207fad0, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207fe94(void *self, int *outx, int *outy, int arg1, int arg2, int arg3);
extern int func_0207fe28(void *self, int x, int y);
extern int func_0207fbb4(void *self, int arg2, int x, int y);
extern int func_0207fdbc(void *self, int x, int y);
extern void func_0207fb70(void *entry);

struct UnkStruct_0207fad0 {
    char pad_00[0x78c];
    unsigned short table[1];
};

int func_0207fad0(struct UnkStruct_0207fad0 *self, int arg1, int arg2, int arg3, unsigned char arg5)
{
    int x = 0, y = 0;

    if (func_0207fe94(self, &x, &y, arg1, arg2, arg3)) {
        int idx = func_0207fe28(self, x, y);
        if (idx == -1) {
            idx = func_0207fbb4(self, arg2, x, y);
            if (idx == -1) {
                if (arg5) {
                    idx = func_0207fdbc(self, x, y);
                }
            }
            if (idx != -1) {
                func_0207fb70(&self->table[idx]);
            }
        }
        if (idx != -1) {
            self->table[idx] = 0xfff1;
        }

        return idx;
    }

    return -1;
}
