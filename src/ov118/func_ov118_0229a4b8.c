/* func_ov118_0229a4b8 @ 0x0229a4b8, 0x104 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa3];
    unsigned char unk_A3;
    unsigned char pad_A4[0xac - 0xa4];
    unsigned char unk_AC;
    unsigned char unk_AD;
    unsigned char pad_AE[0x678 - 0xae];
    unsigned char sub_678[1];
} Ov118Obj;

extern int func_ov118_0229a460(Ov118Obj *p, unsigned short mask);
extern void func_ov118_0229afd4(Ov118Obj *p, unsigned char a1);
extern void func_ov118_0229a474(Ov118Obj *p, int a1);
extern unsigned char *func_ov002_02208098(Ov118Obj *p, unsigned char value);
extern void func_ov002_0220a574(void *sub);
extern void func_ov118_0229a450(Ov118Obj *p, unsigned short mask);
extern void func_ov002_0220a4bc(void *receiver);
extern void func_ov118_0229b454(Ov118Obj *p);
extern void func_ov118_0229b43c(Ov118Obj *p);
extern void RtcSendPxiCommand(int a0);
extern int func_ov118_0229c438(Ov118Obj *p, unsigned char a1);

int func_ov118_0229a4b8(Ov118Obj *p)
{
    unsigned char type;

    if (func_ov118_0229a460(p, 0x800) != 0) {
        func_ov118_0229afd4(p, (unsigned char) (p->unk_AD + 1));
        func_ov118_0229a474(p, 0x38);
        return 0;
    }

    type = p->unk_AC;
    if (type == 0x10) {
        func_ov002_02208098(p, 7);
        func_ov002_0220a574(p->sub_678);
        func_ov118_0229a450(p, 0x1000);
        func_ov002_0220a4bc(p->sub_678);
        return 1;
    } else if (type == 8) {
        if (func_ov118_0229a460(p, 1) != 0) {
            func_ov118_0229afd4(p, 0);
            func_ov118_0229b454(p);
            RtcSendPxiCommand(0x36);
            return 2;
        }
        return 0;
    } else if (type == 9) {
        if (func_ov118_0229a460(p, 1) == 0) {
            func_ov118_0229afd4(p, 0);
            func_ov118_0229b43c(p);
            RtcSendPxiCommand(0x36);
            return 2;
        }
        return 0;
    } else if (type <= 7) {
        if (func_ov118_0229c438(p, type) != 0) {
            return 1;
        }
        return 0;
    } else if (type >= 0xa && type <= 0xf) {
        func_ov118_0229afd4(p, (unsigned char) (p->unk_A3 + type + 5));
        func_ov118_0229a474(p, 0x37);
        return 0;
    }

    return 0;
}
