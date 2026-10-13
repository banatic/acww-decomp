/* func_ov096_0229c63c @ 0x0229c63c, 0x1a4 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov096_0229ee10(unsigned char *, int);
extern int func_ov096_0229ee38(unsigned char *, int);
extern int func_ov096_0229ee50(unsigned char *, int);
extern void func_ov096_0229c2ec(unsigned char *, int);
extern void func_ov096_0229f7e0(unsigned char *);
extern void func_ov002_0220a254(void *);

void func_ov096_0229c63c(unsigned char *self, void *param, int param2)
{
    unsigned char opcode = self[0xb5];

    if (opcode == 0x24) {
        if (func_ov002_022088ac(param)) {
            if (func_ov096_0229ee10(self, param2)) {
                self[0xb5] = 0x25;
            } else {
                func_ov096_0229c2ec(self, 0x10);
                self[0xb5] = 0x10;
            }
        } else if (func_ov002_0220889c(param)) {
            self[0xb5] = 0x0f;
        } else if (func_ov002_022088cc(param)) {
            if (param2 == 0) {
                func_ov096_0229f7e0(self);
                func_ov002_0220a254(self + 0x2500);
            }
        } else if (func_ov002_022088bc(param)) {
            if (func_ov096_0229ee38(self, param2)) {
                self[0xb5] = 0x22;
            } else {
                self[0xb5] = 0x04;
            }
        }
    } else if ((unsigned char) (opcode + 0xde) <= 1) {
        if (func_ov002_022088ac(param)) {
            if (func_ov096_0229ee10(self, param2)) {
                self[0xb5] = 0x25;
            } else {
                func_ov096_0229c2ec(self, 0x10);
                self[0xb5] = 0x12;
            }
        } else if (func_ov002_0220889c(param)) {
            self[0xb5] = 0x11;
        } else if (func_ov002_022088cc(param)) {
            if (func_ov096_0229ee50(self, param2)) {
                self[0xb5] = 0x24;
            }
        } else if (func_ov002_022088bc(param)) {
            self[0xb5] = 0x04;
        }
    } else if (opcode == 0x25) {
        if (func_ov002_022088ac(param)) {
            func_ov096_0229c2ec(self, 0x10);
            self[0xb5] = 0x12;
        } else if (func_ov002_0220889c(param)) {
            if (func_ov096_0229ee38(self, param2)) {
                self[0xb5] = 0x22;
            } else {
                if (func_ov096_0229ee50(self, param2)) {
                    self[0xb5] = 0x24;
                } else {
                    self[0xb5] = 0x11;
                }
            }
        } else if (func_ov002_022088cc(param)) {
            if (param2 == 0) {
                func_ov096_0229f7e0(self);
                func_ov002_0220a254(self + 0x2500);
            }
        } else if (func_ov002_022088bc(param)) {
            self[0xb5] = 0x01;
        }
    }
}
