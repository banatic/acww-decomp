/* map_menu_input_6: 4 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229bd14 @ 0x0229bd14, 0x90 bytes, Thumb
 * func_ov118_0229bccc @ 0x0229bccc, 0x48 bytes, Thumb
 * func_ov118_0229bc7c @ 0x0229bc7c, 0x50 bytes, Thumb
 * func_ov118_0229bb74 @ 0x0229bb74, 0x108 bytes, Thumb
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

extern int func_ov002_02208054(void *p, int flag);
extern void func_ov118_0229b868(void *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov118_0229ab64(void *p);
extern void func_0200467c(int cmd);
extern int func_ov118_0229aca0(void *p);
extern void func_ov002_0220a574(void *p);
extern int func_ov118_0229b0e8(void *p);
extern void func_ov118_0229a474(void *p, int param);
extern int func_ov118_0229b310(void *p);
extern unsigned char data_021f6c54; // 0x021f6c54
extern void *func_0208e95c(unsigned char *p, int n);
extern void func_ov118_0229b8b0(unsigned char *p);
extern void func_ov118_0229ac44(unsigned char *p, int n);
extern int func_020e895c(int *, int, int);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_ov090_02299078(int);
extern int func_ov090_02299098(int);
extern int func_ov118_0229a5bc(void *, int);
extern int func_ov118_0229a460(void *, int);
extern void func_ov118_0229ade0(void *, int);
extern void func_ov118_0229a8b4(void *);
extern void func_ov118_0229afd4(void *, int);
extern void func_ov118_0229af64(void *, int);
extern int func_ov118_0229b088(void *, unsigned char, unsigned char);
extern void func_ov118_0229a450(void *, int);
extern void func_ov118_0229a894(void *);
extern int func_ov118_0229c438(void *, int);
extern GlobalFlags data_021fbe40;

void func_ov118_0229bd14(void *p)
{
    unsigned int flag;

    if (func_ov002_02208054(p, 1) != 0) {
        func_ov118_0229b868(p);
        return;
    }
    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag > 0) {
        if (func_ov118_0229ab64(p) != 0) {
            func_0200467c(0x36);
            return;
        }
        if (func_ov118_0229aca0(p) != 0) {
            func_ov002_0220a574((char *) p + 0x678);
            return;
        }
        if (func_ov118_0229b0e8(p) != 0) {
            func_ov118_0229a474(p, 0x38);
            return;
        }
        if (func_ov118_0229b310(p) != 0) {
            func_ov118_0229a474(p, 0x37);
            return;
        }
    }
}

void func_ov118_0229bccc(unsigned char *obj)
{
    if (data_021fbdd8 == 0) {
        func_0208e95c(obj + 0x678, 3);
        func_ov118_0229b8b0(obj);
    }
    func_ov118_0229ac44(obj, obj[0xa7] + (data_021f6c54 - obj[0xa5]));
}

void func_ov118_0229bc7c(char *param)
{
    if (data_021fbdd8 == 0) {
        func_0208e95c((unsigned char *) (param + 0x678), 3);
        func_ov118_0229b8b0((unsigned char *) param);
    }
    {
        int local;
        local = *(unsigned char *) (param + 0xa4);
        func_020e895c(&local, data_021f6c54 - 0x54, 8);
        func_ov118_0229ac44((unsigned char *) param, local);
    }
}

void func_ov118_0229bb74(UnkStruct_0229bb74 *p)
{
    if (func_ov002_02208014(p)) {
        func_ov118_0229b8b0((unsigned char *) p);
        return;
    }

    switch (func_ov118_0229a5bc(p, func_ov002_02208008(p))) {
        case 1:
            if (func_ov118_0229a460(p, 8)) {
                if (p->unk_AC >= 0x0a && p->unk_AC <= 0x0f) {
                    func_ov118_0229ade0(p, p->unk_98 & ~0xF);
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
