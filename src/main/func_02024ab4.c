/* func_02024ab4 @ 0x02024ab4, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc8c(void *self);
extern void func_0209a088(unsigned short *p, int flag, int extra);
extern void func_0202d9c4(void *self);
extern int func_0209bc40(void);
extern void func_020151c0(void *self);
extern void func_02015094(void *self);
extern unsigned short *func_02080ce4(void *);

struct UnkStruct_02024ab4 {
    char pad_00[0x100];
    void *ptr;
};

struct UnkStruct_02024ab4_2 {
    char pad_00[0x830];
    void *unk_830;
};

typedef struct {
    int a;
    int b;
} Pair;

extern void func_0202dbf0(void *self, Pair p);
extern Pair data_020d9348;

void func_02024ab4(void *self)
{
    unsigned short local;
    int extra;
    unsigned int flagset;

    extra = func_0206fc8c(self);
    local = 0xfff1;
    func_0209a088(&local, 0, extra);

    func_0202d9c4(self);

    if (func_0209bc40() == 3) {
        void *b;
        unsigned short *hp;
        unsigned short hval;

        func_020151c0(self);

        b = ((struct UnkStruct_02024ab4_2 *) ((struct UnkStruct_02024ab4 *) self)->ptr)->unk_830;
        hp = func_02080ce4(b);
        flagset = 0;
        hval = *hp;

        if (hval < 0x11a8) {
            goto skip_flag;
        }
        if (hval > 0x12a7) {
            goto skip_flag;
        }
        flagset = 1;
    skip_flag:

        if (flagset != 0) {
            b = ((struct UnkStruct_02024ab4_2 *) ((struct UnkStruct_02024ab4 *) self)->ptr)->unk_830;
            hval = *func_02080ce4(b);
            *(unsigned short *) ((char *) self + 0x19c) = hval;
        }
    } else {
        func_02015094(self);
    }

    func_0202dbf0(self, data_020d9348);
}
