/*
 * ระบบคำนวณค่าไฟบ้าน (Electricity Bill Tracker) - ต่อยอดจากโค้ดที่ครูสอน
 * ใช้เฉพาะคำสั่งพื้นฐาน: printf, scanf, for, do-while, if-else
 */
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    int choice, N, i, monthCount = 0, hiMonth = 0;
    float unit, rate = 4.50f, totalUnit = 0, avgUnit, highestUnit = 0;
    float totalCost, avgCost, highestCost;

#ifdef _WIN32
    SetConsoleOutputCP(65001);   /* ให้หน้าจอ Windows แสดงภาษาไทย */
#endif

    do {
        printf("\n======= ระบบคำนวณค่าไฟบ้าน =======\n");
        printf("ค่าไฟหน่วยละ: %.2f บาท | บันทึกแล้ว: %d เดือน\n", rate, monthCount);
        printf("1. ตั้งราคาค่าไฟต่อหน่วย\n");
        printf("2. บันทึกหน่วยไฟที่ใช้\n");
        printf("3. สรุปผลค่าไฟ (รวม / เฉลี่ย / สูงสุด)\n");
        printf("0. ออกจากโปรแกรม\n");
        printf("เลือกเมนู: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("ราคาค่าไฟต่อหน่วย (บาท): ");
            scanf("%f", &rate);
            printf("ตั้งราคา %.2f บาท/หน่วย เรียบร้อย!\n", rate);
        }
        else if (choice == 2) {
            /* ===== โค้ดต้นแบบจากครู: รับ N -> วนลูปหา Total และ Highest ===== */
            printf("กรอกจำนวนเดือน: ");
            scanf("%d", &N);
            for (i = 1; i <= N; i++) {
                monthCount++;
                printf("หน่วยไฟเดือนที่ %d (หน่วย): ", monthCount);
                scanf("%f", &unit);
                totalUnit += unit;
                if (unit > highestUnit) {
                    highestUnit = unit;
                    hiMonth = monthCount;
                }
            }
        }
        else if (choice == 3) {
            if (monthCount == 0) {
                printf("ยังไม่มีข้อมูลหน่วยไฟ\n");
            } else {
                /* ===== โค้ดต้นแบบจากครู: คำนวณ Average ===== */
                avgUnit = totalUnit / monthCount;

                /* ===== ส่วนที่ต่อยอด: คำนวณเป็นเงินบาท + ประเมินการใช้ไฟ ===== */
                totalCost   = totalUnit * rate;
                avgCost     = avgUnit * rate;
                highestCost = highestUnit * rate;

                printf("\n=== สรุปผลการใช้ไฟฟ้า ===\n");
                printf("หน่วยไฟรวม     : %.2f หน่วย (%.2f บาท)\n", totalUnit, totalCost);
                printf("เฉลี่ยต่อเดือน   : %.2f หน่วย (%.2f บาท)\n", avgUnit, avgCost);
                printf("เดือนที่ใช้สูงสุด  : %.2f หน่วย (%.2f บาท) [เดือนที่ %d]\n",
                       highestUnit, highestCost, hiMonth);

                printf("\n=== ประเมินการใช้ไฟ ===\n");
                if (avgUnit <= 150) {
                    printf("สถานะ: ประหยัดไฟดีมาก!\n");
                } else if (avgUnit <= 300) {
                    printf("สถานะ: ใช้ไฟระดับปกติ\n");
                } else {
                    printf("สถานะ: ใช้ไฟสูง! ควรลดการเปิดแอร์หรือเครื่องใช้ไฟฟ้า\n");
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
