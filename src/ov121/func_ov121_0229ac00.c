/* func_ov121_0229ac00 @ 0x0229ac00, 0x140 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xac];
    unsigned char unk_AC;
    unsigned char pad_AD;
    unsigned char unk_AE;
    unsigned char unk_AF;
} UnkStruct_0229ac00;

extern void func_0200467c(int);
extern void func_ov121_0229abc8(UnkStruct_0229ac00 *, int, int);
extern void func_ov121_0229aab4(UnkStruct_0229ac00 *);
extern int func_ov121_02299a70(void);
extern void func_ov121_0229ab8c(UnkStruct_0229ac00 *, int);
extern void func_ov121_0229af7c(UnkStruct_0229ac00 *, int, int);
extern void func_ov121_0229a568(UnkStruct_0229ac00 *);
extern void func_ov121_0229a7c8(UnkStruct_0229ac00 *, int);
extern void func_ov121_0229a6b4(UnkStruct_0229ac00 *);
extern void func_ov121_0229a63c(UnkStruct_0229ac00 *);

int func_ov121_0229ac00(UnkStruct_0229ac00 *s)
{
    if (s->unk_AF <= 7) {
        func_0200467c(0xe);
        func_ov121_0229abc8(s, s->unk_AF, s->unk_AE);
        return 0;
    }
    switch (s->unk_AF) {
        case 8:
            func_ov121_0229aab4(s);
            return 1;
        case 10:
            if (func_ov121_02299a70()) {
                func_ov121_0229ab8c(s, 0);
            } else {
                func_ov121_0229af7c(s, 0x17, 1);
                return 1;
            }
            func_ov121_0229a568(s);
            return 1;
        case 11:
            if (func_ov121_02299a70()) {
                func_ov121_0229ab8c(s, 1);
            } else {
                func_ov121_0229af7c(s, 0x18, 1);
                return 1;
            }
            func_ov121_0229a568(s);
            return 1;
        case 13:
            switch (s->unk_AC) {
                case 0:
                case 2:
                    func_ov121_0229a7c8(s, 0);
                    break;
                case 1:
                    func_ov121_0229ab8c(s, 3);
                    func_ov121_0229a568(s);
                    break;
            }
            return 1;
        case 12:
            switch (s->unk_AC) {
                case 0:
                case 2:
                    func_ov121_0229a7c8(s, 1);
                    break;
                case 1:
                    func_ov121_0229ab8c(s, 4);
                    func_ov121_0229a568(s);
                    break;
            }
            return 1;
        case 14:
            switch (s->unk_AC) {
                case 0:
                    func_ov121_0229a7c8(s, 2);
                    break;
                case 1:
                    func_ov121_0229a6b4(s);
                    return 1;
                default:
                    return 0;
            }
            return 1;
        case 9:
            func_ov121_0229a6b4(s);
            return 1;
        case 15:
            func_ov121_0229a63c(s);
            return 1;
    }
    return 0;
}
