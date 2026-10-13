/* func_02033118 @ 0x02033118, 0x4fc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char unk_11;
    unsigned char unk_12;
    unsigned char unk_13;
};

extern struct Node *func_020342c0(int, int, int);
extern void func_0202f8fc(int *, int, int);
extern void __register_global_object(void *, void (*)(void), void *);
extern void func_0202f2f0(void);
extern void func_02033614(void *, int *, int *, int *, int, int, int, int);

extern int data_021c30cc;
extern int data_021c30d4;
extern int data_021c30d8;
extern int data_021c30e8;
extern int data_021c30ec;
extern int data_021c30f0;
extern int data_021c30f4;
extern int data_021c30fc;
extern int data_021c3100[2];
extern int data_021c3108[2];
extern int data_021c3110[2];
extern int data_021c3118[2];
extern int data_021c3120[2];
extern int data_021c3128[2];
extern int data_021c3130[2];
extern int data_021c3138[2];
extern char data_021c3140[];
extern char data_021c314c[];
extern char data_021c3164[];
extern char data_021c3188[];
extern char data_021c31ac[];
extern char data_021c31c4[];
extern char data_021c31d0[];
extern char data_021c31dc[];

void func_02033118(void *a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    int r4 = 1;
    int i;
    int j;

    i = a5;
    for (; i >= a4; i--) {
        j = a3;
        for (; j >= a2; j--) {
            struct Node *r5;
            struct Node *sp_24;
            struct Node *sp_28;
            int sp_2c;

            int sp_30[2];
            int sp_38[2];
            int sp_40[2];
            int sp_48[2];
            int sp_50[2];
            int sp_58[2];
            int sp_60[2];
            int sp_68[2];
            volatile int sp_70;
            volatile int sp_74;
            volatile int sp_78;

            r5 = func_020342c0(a1, j, i);
            if (r5 == (void *) 0) {
                continue;
            }

            sp_24 = func_020342c0(a1, j + 1, i);
            sp_28 = func_020342c0(a1, j, i + 1);

            sp_2c = (i << 13) + 0x1000;
            sp_70 = (j << 13) + 0x1000;
            sp_74 = 0;
            sp_78 = sp_2c;

            // Block 1
            if (sp_24 != (void *) 0 && r5->unk_0C != sp_24->unk_04) {
                if ((data_021c30e8 & r4) == 0) {
                    func_0202f8fc(data_021c3128, (int) 0x00001000, 0);
                    __register_global_object(data_021c3128, func_0202f2f0, data_021c31c4);
                    data_021c30e8 |= r4;
                }
                if ((data_021c30d8 & r4) == 0) {
                    func_0202f8fc(data_021c3138, (int) 0xfffff000, 0);
                    __register_global_object(data_021c3138, func_0202f2f0, data_021c31dc);
                    data_021c30d8 |= r4;
                }
                func_0202f8fc(sp_30, sp_70 + 0x1000u, sp_78 - 0x1000u);
                func_0202f8fc(sp_38, sp_30[0], sp_78 + 0x1000u);

                if (r5->unk_0C > sp_24->unk_04) {
                    func_02033614(a0, sp_30, sp_38, data_021c3128, r5->unk_0C, 1, r5->unk_13, 0);
                    if (a6 != 0) {
                        func_02033614(a0, sp_30, sp_38, data_021c3138, 0x8000, 2, 2, 0);
                    }
                } else {
                    func_02033614(a0, sp_30, sp_38, data_021c3138, sp_24->unk_00, 1, sp_24->unk_10, 0);
                    if (a6 != 0) {
                        func_02033614(a0, sp_30, sp_38, data_021c3128, 0x8000, 2, 2, 0);
                    }
                }
            }

            // Block 2
            if (sp_28 != (void *) 0 && r5->unk_08 != sp_28->unk_00) {
                if ((data_021c30d4 & r4) == 0) {
                    func_0202f8fc(data_021c3100, 0, (int) 0x00001000);
                    __register_global_object(data_021c3100, func_0202f2f0, data_021c3140);
                    data_021c30d4 |= r4;
                }
                if ((data_021c30cc & r4) == 0) {
                    func_0202f8fc(data_021c3110, 0, (int) 0xfffff000);
                    __register_global_object(data_021c3110, func_0202f2f0, data_021c3164);
                    data_021c30cc |= r4;
                }
                func_0202f8fc(sp_40, sp_70 - 0x1000u, sp_78 + 0x1000u);
                func_0202f8fc(sp_48, sp_70 + 0x1000u, sp_40[1]);

                if (r5->unk_08 > sp_28->unk_00) {
                    func_02033614(a0, sp_40, sp_48, data_021c3100, r5->unk_08, 1, r5->unk_12, 0);
                    if (a6 != 0) {
                        func_02033614(a0, sp_40, sp_48, data_021c3110, 0x8000, 2, 2, 0);
                    }
                } else {
                    func_02033614(a0, sp_40, sp_48, data_021c3110, sp_28->unk_00, 1, sp_28->unk_10, 0);
                    if (a6 != 0) {
                        func_02033614(a0, sp_40, sp_48, data_021c3100, 0x8000, 2, 2, 0);
                    }
                }
            }

            // Block 3 and 4 are mutually exclusive
            if (r5->unk_00 != r5->unk_04) {
                // Block 3
                if ((data_021c30f0 & r4) == 0) {
                    func_0202f8fc(data_021c3120, (int) 0xfffff4b0, (int) 0x00000b50);
                    __register_global_object(data_021c3120, func_0202f2f0, data_021c3188);
                    data_021c30f0 |= r4;
                }
                if ((data_021c30ec & r4) == 0) {
                    int *ptr = data_021c3120;
                    func_0202f8fc(data_021c3118, -ptr[0], -ptr[1]);
                    __register_global_object(data_021c3118, func_0202f2f0, data_021c31ac);
                    data_021c30ec |= r4;
                }
                func_0202f8fc(sp_50, sp_70 - 0x1000u, sp_78 - 0x1000u);
                func_0202f8fc(sp_58, sp_70 + 0x1000u, sp_78 + 0x1000u);

                if (r5->unk_00 > r5->unk_04) {
                    func_02033614(a0, sp_50, sp_58, data_021c3120, r5->unk_00, 1, r5->unk_10, 0);
                    if (a6 != 0) {
                        func_02033614(a0, sp_50, sp_58, data_021c3118, 0x8000, 2, 2, 0);
                    }
                } else {
                    func_02033614(a0, sp_50, sp_58, data_021c3118, r5->unk_04, 1, r5->unk_11, 0);
                    if (a6 != 0) {
                        func_02033614(a0, sp_50, sp_58, data_021c3120, 0x8000, 2, 2, 0);
                    }
                }
            } else if (r5->unk_00 != r5->unk_0C) {
                // Block 4
                if ((data_021c30fc & r4) == 0) {
                    func_0202f8fc(data_021c3130, (int) 0x00000b50, (int) 0x00000b50);
                    __register_global_object(data_021c3130, func_0202f2f0, data_021c31d0);
                    data_021c30fc |= r4;
                }
                if ((data_021c30f4 & r4) == 0) {
                    int *ptr = data_021c3130;
                    func_0202f8fc(data_021c3108, -ptr[0], -ptr[1]);
                    __register_global_object(data_021c3108, func_0202f2f0, data_021c314c);
                    data_021c30f4 |= r4;
                }
                func_0202f8fc(sp_60, sp_70 - 0x1000u, sp_78 + 0x1000u);
                func_0202f8fc(sp_68, sp_70 + 0x1000u, sp_78 - 0x1000u);

                if (r5->unk_00 > r5->unk_0C) {
                    func_02033614(a0, sp_60, sp_68, data_021c3130, r5->unk_00, 1, r5->unk_10, 0);
                    if (a6 != 0) {
                        func_02033614(a0, sp_60, sp_68, data_021c3108, 0x8000, 2, 2, 0);
                    }
                } else {
                    func_02033614(a0, sp_60, sp_68, data_021c3108, r5->unk_0C, 1, r5->unk_13, 0);
                    if (a6 != 0) {
                        func_02033614(a0, sp_60, sp_68, data_021c3130, 0x8000, 2, 2, 0);
                    }
                }
            }
        }
    }
}
