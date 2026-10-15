/* func_020979f0 @ 0x020979f0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Entry Entry;
struct Entry {
    char pad_00[0x100];
};

extern Entry data_021f20fc;

extern Entry *func_02097ff0(Entry *arg, int arg1);
extern int func_02065ec0(Entry *p);
extern int func_02066830(Entry *p, int a);
extern void func_020664e0(Entry *p);

int func_020979f0(int a, int b)
{
    int i;
    Entry *p;

    p = func_02097ff0(&data_021f20fc, 0);
    for (i = 0; i < 10; p++, i++) {
        if (func_02065ec0(p) != 0) {
            continue;
        }
        func_02066830(p, a);
        if (b != 0) {
            func_020664e0(p);
        }
        return 1;
    }
    return 0;
}
