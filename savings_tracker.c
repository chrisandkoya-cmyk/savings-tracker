#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice, N, i, weeks = 0, hiWeek = 0;
    float amount, goal = 0, total = 0, average, highest = 0;

    do {
        printf("\n=== ระบบออมเงิน (เป้า %.0f บาท | ออมแล้ว %d สัปดาห์) ===\n", goal, weeks);
        printf("1.ตั้งเป้าหมาย  2.บันทึกเงินออม  3.สรุปผล  0.ออก\nเลือกเมนู: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("ตั้งเป้าหมาย (บาท): ");
            scanf("%f", &goal);
        } else if (choice == 2) {
            printf("จำนวนสัปดาห์ที่ต้องการเพิ่ม: ");
            scanf("%d", &N);
            for (i = 1; i <= N; i++) {                 /* ลูปรับค่าจากโค้ดครู */
                weeks++;
                printf("เงินออมสัปดาห์ที่ %d: ", weeks);
                scanf("%f", &amount);
                total += amount;
                if (amount > highest) { highest = amount; hiWeek = weeks; }
            }
        } else if (choice == 3 && weeks > 0) {
            average = total / weeks;
            printf("\n=== SUMMARY ===\n");
            printf("ยอดออมรวม      : %.2f บาท\n", total);
            printf("เฉลี่ยต่อสัปดาห์  : %.2f บาท\n", average);
            printf("ออมสูงสุด       : %.2f บาท (สัปดาห์ที่ %d)\n", highest, hiWeek);
            if (goal > 0) {
                if (total >= goal) printf("สถานะเป้าหมาย : ออมครบเป้าหมายแล้ว!\n");
                else printf("ยังขาดอีก       : %.2f บาท (%.1f%%)\n", goal - total, total / goal * 100);
            }
        }

        if (choice != 0) {
            printf("\nกด Enter เพื่อไปต่อ...");
            getchar(); getchar();
            system("cls");                      /* ล้างหน้าจอ */
        }
    } while (choice != 0);
    return 0;
}
