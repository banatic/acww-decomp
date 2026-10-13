/* func_020263b0 @ 0x020263b0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void (*data_020c8f7c[])(unsigned short *, int, unsigned short *);
extern int func_020808b0(void *);
extern unsigned short *func_02080ce4(void *);

typedef void (*Func_t)(unsigned short *, int, unsigned short *);

struct UnkStruct_020263b0 {
    char pad_00[0x100];
    void *ptr;
};

struct UnkStruct_020263b0_2 {
    char pad_00[0x830];
    void *unk_830;
};

void func_020263b0(unsigned short *arg0, struct UnkStruct_020263b0 *arg1, unsigned int arg2)
{
    Func_t fptr;
    if (arg2 < 7 && (fptr = data_020c8f7c[arg2]) != 0) {
        unsigned short local;
        void *r6;
        int r7;
        r6 = ((struct UnkStruct_020263b0_2 *) arg1->ptr)->unk_830;
        r7 = func_020808b0(r6);
        local = *func_02080ce4(r6);
        fptr(arg0, r7, &local);
    } else {
        *arg0 = 0xfff1;
    }
}
