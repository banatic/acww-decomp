/* func_0206ba6c @ 0x0206ba6c, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206ba6c {
    unsigned char pad_00[0x34];
    int unk_34;
    unsigned char pad_38[0x14];
    unsigned char unk_4C;
    unsigned char unk_4D;
    unsigned char unk_4E;
    unsigned char unk_4F;
    int unk_50;
    int unk_54;
    int unk_58;
} UnkStruct_0206ba6c;

extern void func_0206bb5c(UnkStruct_0206ba6c *s);
extern int func_0206bb74(UnkStruct_0206ba6c *s);

int func_0206ba6c(UnkStruct_0206ba6c *s)
{
    int res = 1;
    unsigned flag = res;
    unsigned cond;
    int r4;

    if (s->unk_34 != 1 && s->unk_4E == 0) {
        flag = 0;
    }

    if (s->unk_4D != 0) {
        res = 0;
        s->unk_4D = 0;
        goto end;
    }

    if (flag != 0) {
        s->unk_50 = 0;
        s->unk_54 = 0;
        s->unk_58 = 0;
        while (func_0206bb74(s) == 0) {
            func_0206bb5c(s);
        }
    } else {
        if (s->unk_34 != 2 && s->unk_4F == 0 && s->unk_4C != 0) {
            cond = 1;
        } else {
            cond = 0;
        }

        if (cond != 0) {
            s->unk_58 = 0;
        }

        if (s->unk_58 > 0) {
            s->unk_58 -= 0x1800;
            res = 0;
            goto end;
        }

        if (s->unk_54 == 0) {
            r4 = 1;
        } else {
            r4 = 2;
        }

        if (cond != 0) {
            r4 = 3;
        }

        if (s->unk_50 >= r4) {
            s->unk_50 = 0;
            s->unk_54++;
            if (s->unk_54 >= 2) {
                s->unk_54 = 0;
            }
            res = 0;
            goto end;
        } else {
            while (func_0206bb74(s) == 0) {
                func_0206bb5c(s);
                s->unk_50++;
                if (s->unk_50 >= r4) {
                    s->unk_50 = 0;
                    s->unk_54++;
                    if (s->unk_54 >= 2) {
                        s->unk_54 = 0;
                    }
                    res = 0;
                    goto end;
                }
            }
        }
    }

end:
    return res;
}
