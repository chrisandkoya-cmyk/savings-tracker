/*
 * ระบบออมเงิน (Savings Tracker) - ต่อยอดจากโค้ดที่ครูสอน
 * มีเฉพาะคำสั่งพื้นฐาน: printf, scanf, for, while, switch, if-else, array
 */
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    int choice, N, i, weekCount = 0, hiWeek = 1, loWeek = 1, weeksLeft;
    float saving[100], amount, goal = 0;
    float total, average, highest, lowest, remaining, percent;

#ifdef _WIN32
    SetConsoleOutputCP(65001);   /* ให้หน้าจอ Windows แสดงภาษาไทย */
#endif

    do {
        printf("\n======= ระบบออมเงิน =======\n");
        printf("เป้าหมาย: %.2f บาท | บันทึกแล้ว: %d สัปดาห์\n", goal, weekCount);
        printf("1. ตั้งเป้าหมายการออม\n");
        printf("2. บันทึกเงินออม\n");
        printf("3. ดูประวัติการออม\n");
        printf("4. สรุปผล (ยอดรวม / เฉลี่ย / สูงสุด)\n");
        printf("0. ออกจากโปรแกรม\n");
        printf("เลือกเมนู: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("จำนวนเงินเป้าหมาย (บาท): ");
            scanf("%f", &goal);
            printf("ตั้งเป้าหมาย %.2f บาท เรียบร้อย!\n", goal);
        }
        else if (choice == 2) {
            /* ===== โครงรับค่า N รอบ จากโค้ดที่ครูสอน ===== */
            printf("กรอกจำนวนสัปดาห์: ");
            scanf("%d", &N);
            for (i = 1; i <= N; i++) {
                printf("เงินออมสัปดาห์ที่ %d: ", weekCount + 1);
                scanf("%f", &amount);
                saving[weekCount] = amount;
                weekCount++;
            }
        }
        else if (choice == 3) {
            printf("\nสัปดาห์\tออมได้\t\tยอดสะสม\n");
            total = 0;
            for (i = 0; i < weekCount; i++) {
                total += saving[i];
                printf("%d\t%.2f\t\t%.2f\n", i + 1, saving[i], total);
            }
        }
        else if (choice == 4) {
            if (weekCount == 0) {
                printf("ยังไม่มีข้อมูลการออม\n");
            } else {
                /* ===== โค้ดต้นแบบจากครู: หา Total / Highest / Average ===== */
                total = 0;
                highest = saving[0];
                lowest  = saving[0];
                hiWeek  = 1;
                loWeek  = 1;

                for (i = 0; i < weekCount; i++) {
                    total += saving[i];
                    if (saving[i] > highest) {
                        highest = saving[i];
                        hiWeek = i + 1;
                    }
                    if (saving[i] < lowest) {       /* ต่อยอด: หาค่าต่ำสุด */
                        lowest = saving[i];
                        loWeek = i + 1;
                    }
                }
                average = total / weekCount;

                printf("\n=== สรุปผลการออม ===\n");
                printf("ยอดออมรวม     : %.2f บาท\n", total);
                printf("เฉลี่ยต่อสัปดาห์ : %.2f บาท\n", average);
                printf("ออมมากที่สุด   : %.2f บาท (สัปดาห์ที่ %d)\n", highest, hiWeek);
                printf("ออมน้อยที่สุด  : %.2f บาท (สัปดาห์ที่ %d)\n", lowest, loWeek);

                /* ===== ต่อยอด: เทียบกับเป้าหมาย ===== */
                if (goal > 0) {
                    remaining = goal - total;
                    percent = total / goal * 100;
                    printf("\n=== เทียบกับเป้าหมาย ===\n");
                    printf("ความคืบหน้า   : %.1f%%\n", percent);
                    if (remaining <= 0) {
                        printf("ยินดีด้วย! ออมครบเป้าหมายแล้ว!\n");
                    } else {
                        printf("ยังขาดอีก      : %.2f บาท\n", remaining);
                        if (average > 0) {
                            weeksLeft = (int)((remaining + average - 0.01f) / average);
                            printf("คาดว่าจะครบใน : %d สัปดาห์\n", weeksLeft);
                        }
                    }
                }
            }
        }

        if (choice != 0) {
            printf("\nกด Enter เพื่อไปต่อ...");
            getchar(); getchar();       /* รอรับปุ่ม Enter */
#ifdef _WIN32
            system("cls");              /* ล้างหน้าจอบน Windows */
#else
            printf("\033[2J\033[H");    /* ล้างหน้าจอบนเครื่องอื่น */
#endif
        }
    } while (choice != 0);

    return 0;
}
