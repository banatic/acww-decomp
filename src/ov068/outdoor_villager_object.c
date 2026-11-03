/* outdoor_villager_object: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226d528 @ 0x0226d528, 0x70 bytes, Thumb
 * func_ov068_0226d4ac @ 0x0226d4ac, 0x7c bytes, Thumb
 */

struct UnkStruct_0226d4ac {
    char pad_00[0x561];
    unsigned char unk_561;
    unsigned char unk_562;
    char pad_563[0x618 - 0x563];
    char unk_618;
    char pad_619[0x8b0 - 0x619];
    unsigned int unk_8B0;
    char pad_8B4[0xa06 - 0x8b4];
    unsigned short short_a06;
};

extern int func_02089cc0(void *, int);
extern void *func_02096190(int);
extern int func_0200322c(void *, void *);
extern int func_02014868(char *);
extern int func_ov068_0226d598(void *);

int func_ov068_0226d528(void *p)
{
    void *q;
    short diff;

    if (((unsigned char *) p)[0x508] == 0) {
        goto fail;
    }
    if (func_02089cc0((unsigned char *) p + 0x4cc, 4) == 0) {
        goto fail;
    }
    q = func_02096190(4);
    if (q == 0) {
        goto fail;
    }
    if (*(int *) ((unsigned char *) q + 0x98) == 0) {
        goto fail;
    }

    diff = (short) (func_0200322c((unsigned char *) q + 0x5c, (unsigned char *) p + 0x5c) -
                    *(short *) ((unsigned char *) q + 0x94));
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x31c6) {
        goto fail;
    }

    return 1;

fail:
    return 0;
}

void func_ov068_0226d4ac(struct UnkStruct_0226d4ac *p)
{
    if (p->unk_562 && p->unk_561 && p->unk_8B0 && func_02014868(&p->unk_618) == 0 && func_ov068_0226d598(p) != 0) {
        if (func_ov068_0226d528(p) != 0) {
            p->short_a06++;
            if ((int) p->short_a06 < 100) {
                // nothing
            } else {
                p->short_a06 = 100;
            }
        } else {
            p->short_a06 = 0;
        }
    } else {
        p->short_a06 = 0;
    }
}
