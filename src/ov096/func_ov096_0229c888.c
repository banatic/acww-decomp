/* func_ov096_0229c888 @ 0x0229c888, 0x1f0 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern void func_ov002_0220a254(void *);
extern int func_ov096_0229ee38(unsigned char *, int);
extern int func_ov096_0229ee50(unsigned char *, int);
extern int func_ov096_0229ee10(unsigned char *, int);
extern void func_ov096_0229c2ec(unsigned char *, int);
extern int func_ov096_0229c310(unsigned char *);
extern int func_ov096_0229f820(unsigned char *, int);
extern int func_ov096_0229c2fc(unsigned char *, int);
extern void func_ov096_0229f7e0(unsigned char *);

void func_ov096_0229c888(unsigned char *self, int param1, int param2)
{
    int v7 = (int) self[0xb5] - 15;
    int r4 = v7 >> 1;

    if (func_ov002_022088ac(param1) == 0) {
        goto L_c944;
    }

    if ((v7 & 1) <= 0) {
        goto L_c8bc;
    }
    self[0xb5] -= 1;
    goto exit_block;

L_c8bc:
    if (param2 != 2) {
        goto L_c8c2;
    }
    goto exit_block;

L_c8c2:
    if (r4 < 2) {
        goto L_c8d6;
    }
    self[0xb5] = (r4 - 2) * 5 + 4;
    goto exit_block;

L_c8d6: {
    int f1 = func_ov096_0229ee38(self, param2);
    int f2 = func_ov096_0229ee50(self, param2);
    if ((f1 & f2) != 0) {
        if (r4 == 0) {
            self[0xb5] = 0x24;
        } else {
            self[0xb5] = 0x22;
        }
        goto exit_block;
    } else {
        if (f1 != 0) {
            self[0xb5] = 0x22;
            goto exit_block;
        } else {
            if (f2 != 0) {
                self[0xb5] = 0x24;
                goto exit_block;
            } else {
                if (func_ov096_0229ee10(self, param2) != 0) {
                    self[0xb5] = 0x25;
                    goto exit_block;
                } else {
                    self[0xb5] = 4;
                    goto exit_block;
                }
            }
        }
    }
}

L_c944:
    if (func_ov002_0220889c(param1) == 0) {
        goto exit_block;
    }
    if ((v7 & 1) >= 1) {
        goto L_c966;
    }
    self[0xb5] += 1;
    goto exit_block;

L_c966:
    if (param2 == 2) {
        goto exit_block;
    }
    func_ov096_0229c2ec(self, 0x20);
    if (r4 >= 2) {
        goto L_c9e4;
    }

    if (func_ov096_0229ee10(self, param2) != 0) {
        self[0xb5] = 0x25;
        goto exit_block;
    } else {
        int f1 = func_ov096_0229ee38(self, param2);
        int f2 = func_ov096_0229ee50(self, param2);
        if ((f1 & f2) != 0) {
            if (r4 == 0) {
                self[0xb5] = 0x24;
            } else {
                self[0xb5] = 0x22;
            }
            goto exit_block;
        } else {
            if (f1 != 0) {
                self[0xb5] = 0x22;
                goto exit_block;
            } else {
                if (f2 != 0) {
                    self[0xb5] = 0x24;
                    goto exit_block;
                } else {
                    self[0xb5] = 0;
                    goto exit_block;
                }
            }
        }
    }

L_c9e4:
    if (r4 == 4) {
        if (func_ov096_0229c310(self) != 0) {
            self[0xb5] = 0x21;
            goto end;
        }
    }
    self[0xb5] = (r4 - 2) * 5;
    // fall through to exit_block

exit_block:
    if (func_ov096_0229f820(self, self[0xb5]) == 0) {
        goto end;
    }
    if (func_ov096_0229c2fc(self, 0x30) != 0) {
        goto end;
    }
    if (func_ov002_022088cc(param1) != 0) {
        if (r4 > 0) {
            self[0xb5] -= 2;
            goto end;
        } else {
            if (param2 != 0) {
                goto end;
            }
            func_ov096_0229f7e0(self);
            func_ov002_0220a254(self + 0x2500);
            goto end;
        }
    } else {
        if (func_ov002_022088bc(param1) == 0) {
            goto end;
        }
        if (r4 >= 4) {
            goto end;
        }
        self[0xb5] += 2;
        // fall through to end
    }
end:
    return;
}
