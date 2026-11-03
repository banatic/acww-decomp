/* message_query: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a7a98 @ 0x020a7a98, 0x10 bytes, Thumb
 * func_020a7a64 @ 0x020a7a64, 0x34 bytes, Thumb
 * func_020a7a50 @ 0x020a7a50, 0x14 bytes, Thumb
 * func_020a7a48 @ 0x020a7a48, 0x8 bytes, Thumb
 * func_020a7a2c @ 0x020a7a2c, 0x1c bytes, Thumb
 * func_020a7a14 @ 0x020a7a14, 0x18 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x48];
    int unk_48;
    int unk_4C;
    unsigned char pad_50[8];
    unsigned char unk_58;
} UnkStruct_020a7a50;

extern void func_020a8754(void *);
extern void func_020a94a4(void *);

int func_020a7a98(unsigned char *p)
{
    if (p[0x58] == 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_020a7a64(void *arg0)
{
    unsigned char *p;
    void *r4 = arg0;

    *(int *) ((char *) r4 + 0x24) = 0;
    func_020a8754((char *) r4 + 0x28);
    *(int *) ((char *) r4 + 0x3c) = 0;
    *(int *) ((char *) r4 + 0x40) = -1;
    *(int *) ((char *) r4 + 0x44) = -1;
    *(int *) ((char *) r4 + 0x48) = 0;
    *(int *) ((char *) r4 + 0x4c) = 0;
    *(int *) ((char *) r4 + 0x50) = 0;
    *(int *) ((char *) r4 + 0x54) = 0;
    p = (unsigned char *) r4 + 0x58;
    *p = 0;
    func_020a94a4(r4);
}

void func_020a7a50(UnkStruct_020a7a50 *p)
{
    int old = p->unk_4C;
    p->unk_4C = old + 1;
    if (old == p->unk_48) {
        p->unk_58 = 1;
    }
}

void func_020a7a48(int *p0)
{
    p0[19] = ((int) (p0[19]) + (1));
}

void func_020a7a2c(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x3c) == 0xa) {
        *(unsigned int *) ((char *) arg0 + 0x54) = *(unsigned int *) ((char *) arg0 + 0x54) + 1;
        if (*(unsigned int *) ((char *) arg0 + 0x54) == *(unsigned int *) ((char *) arg0 + 0x50)) {
            *(unsigned char *) ((char *) arg0 + 0x58) = 1;
        }
    }
}

/* FAKEMATCH: the empty if keeps the goal y, goal x and cur x loads in that order; the plain compare loads cur x first */
void func_020a7a14(void *p)
{
    int d = *(unsigned int *) ((char *) p + 0x44);
    int b = *(unsigned int *) ((char *) p + 0x40);
    if ((b && b) && b) {
    }
    if (*(unsigned int *) ((char *) p + 0x28) == b && *(unsigned int *) ((char *) p + 0x2c) == d) {
        *(unsigned char *) ((char *) p + 0x58) = 1;
    }
}
