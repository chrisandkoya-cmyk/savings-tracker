#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice, N, i, months = 0, hiMonth = 0;
    float unit, rate = 4.5f, total = 0, average, highest = 0;

    do {
        printf("\n=== ระบบคำนวณค่าไฟ (หน่วยละ %.2f บาท | %d เดือน) ===\n", rate, months);
        printf("1.ตั้งราคา/หน่วย  2.บันทึกหน่วยไฟ  3.สรุปผล  0.ออก\nเลือกเมนู: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("ราคาค่าไฟต่อหน่วย (บาท): ");
            scanf("%f", &rate);
        } else if (choice == 2) {
            printf("จำนวนเดือนที่ต้องการเพิ่ม: ");
            scanf("%d", &N);
            for (i = 1; i <= N; i++) {                 /* ลูปรับค่าจากโค้ดครู */
                months++;
                printf("หน่วยไฟเดือนที่ %d: ", months);
                scanf("%f", &unit);
                total += unit;
                if (unit > highest) { highest = unit; hiMonth = months; }
            }
        } else if (choice == 3 && months > 0) {
            average = total / months;
            printf("\n=== SUMMARY ===\n");
            printf("หน่วยไฟรวม    : %.2f หน่วย (%.2f บาท)\n", total, total * rate);
            printf("เฉลี่ยต่อเดือน  : %.2f หน่วย (%.2f บาท)\n", average, average * rate);
            printf("เดือนที่ใช้สูงสุด : %.2f หน่วย (เดือนที่ %d)\n", highest, hiMonth);
            if (average <= 150)      printf("สถานะการใช้ไฟ : ประหยัดดีมาก\n");
            else if (average <= 300) printf("สถานะการใช้ไฟ : ปกติ\n");
            else                     printf("สถานะการใช้ไฟ : สูง (ควรลดการใช้ไฟ)\n");
        }

        if (choice != 0) {
            printf("\nกด Enter เพื่อไปต่อ...");
            getchar(); getchar();
            system("cls");                      /* ล้างหน้าจอ */
        }
    } while (choice != 0);
    return 0;
}
