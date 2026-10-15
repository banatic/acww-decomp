/* func_ov118_0229abe0 @ 0x0229abe0, 0x64 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern int func_ov118_0229b374(void *self);
extern void func_ov002_0220a4c8(void *receiver);
extern void func_ov118_0229adf0(void *self, int v);

typedef struct {
    char pad_00[0x9A];
    unsigned short unk_9A;
} UnkStruct_0229abe0;

void func_ov118_0229abe0(void *self)
{
    int v;
    unsigned short flags;
    int limit;

    v = ((UnkStruct_0229abe0 *) self)->unk_9A;
    flags = data_021fbe40;

    if (flags & 0x40) {
        v -= 4;
    } else if (flags & 0x80) {
        v += 4;
    }

    limit = func_ov118_0229b374(self);

    if (v < 0) {
        v = 0;
    } else if (v > limit) {
        v = limit;
    }

    if (v != ((UnkStruct_0229abe0 *) self)->unk_9A) {
        func_ov002_0220a4c8((char *) self + 0x678);
    }

    func_ov118_0229adf0(self, v);
}
