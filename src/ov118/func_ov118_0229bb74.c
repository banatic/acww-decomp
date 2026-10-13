/* func_ov118_0229bb74 @ 0x0229bb74, 0x108 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x98];
    unsigned short unk_98;
    char pad_9A[0xac - 0x9a];
    unsigned char unk_AC;
    unsigned char unk_AD;
    unsigned char unk_AE;
    unsigned char unk_AF;
} UnkStruct_0229bb74;

typedef struct {
    unsigned short unk_00;
    unsigned short flags;
} GlobalFlags;

extern int func_ov002_02208014(void *);
extern int func_ov002_02208008(void *);
extern void func_ov002_02208098(void *, int);
extern int func_ov090_02299078(int);
extern int func_ov090_02299098(int);

extern void func_ov118_0229b8b0(void *);
extern int func_ov118_0229a5bc(void *, int);
extern int func_ov118_0229a460(void *, int);
extern void func_ov118_0229ade0(void *, int, int);
extern void func_ov118_0229a8b4(void *);
extern void func_ov118_0229afd4(void *, int);
extern void func_ov118_0229af64(void *, int);
extern int func_ov118_0229b088(void *, unsigned char, unsigned char);
extern void func_ov118_0229a450(void *, int);
extern void func_ov118_0229a894(void *);
extern void func_ov118_0229c438(void *, int);

extern GlobalFlags data_021fbe40;

void func_ov118_0229bb74(UnkStruct_0229bb74 *p)
{
    if (func_ov002_02208014(p)) {
        func_ov118_0229b8b0(p);
        return;
    }

    switch (func_ov118_0229a5bc(p, func_ov002_02208008(p))) {
        case 1:
            if (func_ov118_0229a460(p, 8)) {
                if (p->unk_AC >= 0x0a && p->unk_AC <= 0x0f) {
                    func_ov118_0229ade0(p, p->unk_98 & ~0xF, 0xF);
                }
            }
            func_ov118_0229a8b4(p);
            break;

        case 2:
            func_ov118_0229afd4(p, 0);
            func_ov118_0229af64(p, 0xe);
            p->unk_AD = (unsigned char) func_ov118_0229b088(p, p->unk_AE, p->unk_AF);
            func_ov118_0229a450(p, 0x800);
            func_ov002_02208098(p, 0xa);
            func_ov118_0229a8b4(p);
            break;

        case 3:
            func_ov118_0229a8b4(p);
            break;

        default: {
            unsigned short fl = data_021fbe40.flags;
            if (fl & 0x0001) {
                func_ov118_0229a894(p);
            } else if (fl & 0x0100) {
                func_ov118_0229c438(p, func_ov090_02299078(5));
            } else if (fl & 0x0200) {
                func_ov118_0229c438(p, func_ov090_02299098(5));
            }
            break;
        }
    }
}
