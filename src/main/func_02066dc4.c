/* func_02066dc4 @ 0x02066dc4, 0x15c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a94d8(void *arg);
extern int func_020a9cf8(void *arg);
extern int func_020a9d14(void *arg);
extern int func_020671b0(void *arg);
extern int func_02068cbc(void *arg);
extern int func_02068c9c(void *arg);
extern int func_02068d2c(void *arg);
extern int func_02067dbc(void *arg);
extern int func_020676ac(void *arg);
extern int func_02068d20(void *arg);
extern int func_02068c6c(void *arg);
extern int func_02068d14(void *arg);
extern int func_02068c3c(void *arg);
extern int func_02066abc(void *arg);
extern int func_02068d38(void *arg);
extern void RtcSendPxiCommand(int cmd);

void func_02066dc4(unsigned char *s)
{
    int f;
    int flag2, flag3, flag4, flag5;

    func_020a94d8(s + 0x149c);

    f = *(int *) (s + 0x13e8);
    if (f == 2) {
        flag2 = 1;
    } else {
        flag2 = 0;
    }
    if (f == 3) {
        flag3 = 1;
    } else {
        flag3 = 0;
    }
    if (f == 4) {
        flag4 = 1;
    } else {
        flag4 = 0;
    }
    if (f == 5) {
        flag5 = 1;
    } else {
        flag5 = 0;
    }

    if (func_020a9cf8(s + 0xb4) != 0) {
        func_020671b0(s);
    }

    if (flag2 || flag3 || flag4) {
        if (s[0x1e93] == 0 && func_020a9d14(s + 0xb4) != 0) {
            if (s[0x1e92] != 0) {
                func_02066abc(s);
                return;
            } else {
                if (func_02068cbc(s + 0x1c) != 0) {
                    s += 0x1c;
                    func_02068d2c(s);
                    return;
                } else {
                    if (func_02068c9c(s + 0x1c) != 0) {
                        if (func_02067dbc(s) != 0 || func_020676ac(s) != 0) {
                            func_02068d20(s + 0x1c);
                            if (s[0x1e9a] == 0) {
                                RtcSendPxiCommand(0x10);
                            }
                            if (s[0x18] != 0 || s[0x1490] != 0) {
                                RtcSendPxiCommand(0x13);
                            }
                            return;
                        } else {
                            return;
                        }
                    } else {
                        if (func_02068c6c(s + 0x1c) != 0) {
                            s += 0x1c;
                            func_02068d14(s);
                            return;
                        } else {
                            if (func_02068c3c(s + 0x1c) != 0) {
                                func_02066abc(s);
                                return;
                            } else {
                                return;
                            }
                        }
                    }
                }
            }
        } else {
            if (func_02068cbc(s + 0x1c) != 0) {
                return;
            } else {
                s += 0x1c;
                func_02068d38(s);
                return;
            }
        }
    } else {
        if (flag5 && func_020a9d14(s + 0xb4) != 0) {
            func_02066abc(s);
        }
    }
}
