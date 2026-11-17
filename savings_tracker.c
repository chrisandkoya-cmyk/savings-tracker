/*
 * =====================================================
 *   ระบบออมเงิน (SAVINGS TRACKER) - แสดงผลภาษาไทย
 *   ต่อยอดจากโค้ดที่ครูสอน: รับ N -> วนลูป -> Total / Average / Highest
 *   ใช้งานใน Dev-C++: เปิดไฟล์นี้ (File > Open) แล้วกด F11 (Compile & Run)
 *
 *   หมายเหตุเรื่องภาษาไทย:
 *   - ไฟล์นี้ต้องบันทึกเป็นรหัส UTF-8 (ภาษาไทยจึงจะแสดงถูกต้อง)
 *   - โปรแกรมสั่งให้หน้าต่าง console ใช้ UTF-8 ด้วย SetConsoleOutputCP(65001)
 * =====================================================
 */
#include <stdio.h>
#include <stdlib.h>              /* ใช้ system("cls") สำหรับล้างหน้าจอ */
#include <string.h>
#ifdef _WIN32
#include <windows.h>             /* ใช้ตั้งค่าหน้าจอ console ให้แสดงภาษาไทย */
#endif

#define MAX_WEEKS 520            /* เก็บได้สูงสุด 10 ปี (520 สัปดาห์) */
#define DATA_FILE "savings.txt"  /* ไฟล์เก็บข้อมูล เปิดโปรแกรมใหม่ข้อมูลไม่หาย */

char  goalName[100] = "เป้าหมายของฉัน"; /* ชื่อเป้าหมาย */
float goalAmount    = 0;                /* จำนวนเงินเป้าหมาย */
float saving[MAX_WEEKS];                /* เงินที่ออมแต่ละสัปดาห์ */
int   weekCount     = 0;                /* จำนวนสัปดาห์ที่บันทึกแล้ว */

/* ---------- ฟังก์ชันช่วยรับข้อมูล (กันพิมพ์ผิดแล้วโปรแกรมค้าง) ---------- */
void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int readInt(const char *msg, int min, int max) {
    int value;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            clearInput();
            return value;
        }
        clearInput();
        printf("  [!] กรุณากรอกตัวเลข %d - %d\n", min, max);
    }
}

float readFloat(const char *msg, float min) {
    float value;
    while (1) {
        printf("%s", msg);
        if (scanf("%f", &value) == 1 && value >= min) {
            clearInput();
            return value;
        }
        clearInput();
        printf("  [!] กรุณากรอกตัวเลขตั้งแต่ %.2f ขึ้นไป\n", min);
    }
}

void waitEnter() {
    printf("\nกด Enter เพื่อไปต่อ...");
    clearInput();
}

/* ล้างหน้าจอ: Windows (Dev-C++) ใช้ cls / เครื่องอื่นใช้รหัส ANSI */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
    fflush(stdout);
#endif
}

/* ---------- บันทึก / โหลดข้อมูลจากไฟล์ ---------- */
void saveData() {
    int i;
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("  [!] บันทึกไฟล์ไม่สำเร็จ\n");
        return;
    }
    fprintf(fp, "%s\n%.2f\n%d\n", goalName, goalAmount, weekCount);
    for (i = 0; i < weekCount; i++) {
        fprintf(fp, "%.2f\n", saving[i]);
    }
    fclose(fp);
}

void loadData() {
    int i;
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) return;                 /* ยังไม่มีไฟล์ = ใช้งานครั้งแรก */
    if (fgets(goalName, sizeof(goalName), fp) != NULL) {
        goalName[strcspn(goalName, "\n")] = '\0';
    }
    if (fscanf(fp, "%f %d", &goalAmount, &weekCount) != 2 ||
        weekCount < 0 || weekCount > MAX_WEEKS) {
        weekCount = 0;
    }
    for (i = 0; i < weekCount; i++) {
        if (fscanf(fp, "%f", &saving[i]) != 1) {
            weekCount = i;
            break;
        }
    }
    fclose(fp);
    printf("  [OK] โหลดข้อมูลเดิม %d สัปดาห์\n", weekCount);
}

/* ---------- เมนู 1: ตั้งเป้าหมาย ---------- */
void setGoal() {
    printf("ชื่อเป้าหมาย (เช่น New Phone): ");
    if (fgets(goalName, sizeof(goalName), stdin) != NULL) {
        goalName[strcspn(goalName, "\n")] = '\0';
    }
    if (strlen(goalName) == 0) strcpy(goalName, "เป้าหมายของฉัน");
    goalAmount = readFloat("จำนวนเงินเป้าหมาย (บาท): ", 1);
    saveData();
    printf("  [OK] ตั้งเป้าหมาย: %s = %.2f บาท\n", goalName, goalAmount);
}

/* ---------- เมนู 2: บันทึกเงินออม (โครงลูปจากโค้ดครู) ---------- */
void addSavings() {
    int N, i;
    float amount;

    if (weekCount >= MAX_WEEKS) {
        printf("  [!] พื้นที่เก็บข้อมูลเต็มแล้ว\n");
        return;
    }
    N = readInt("กรอกจำนวนสัปดาห์: ", 1, MAX_WEEKS - weekCount);
    for (i = 1; i <= N; i++) {
        printf("กรอกเงินออมสัปดาห์ที่ %d: ", weekCount + 1);
        amount = readFloat("", 0);
        saving[weekCount] = amount;
        weekCount++;
    }
    saveData();
    printf("  [OK] บันทึกแล้ว %d สัปดาห์\n", N);
}

/* ---------- เมนู 3: ประวัติการออม ---------- */
void showHistory() {
    int i, j, bar;
    float running = 0, highest = 0;

    if (weekCount == 0) {
        printf("  ยังไม่มีข้อมูลการออม\n");
        return;
    }
    for (i = 0; i < weekCount; i++) {
        if (saving[i] > highest) highest = saving[i];
    }
    /* หมายเหตุ: หัวตารางภาษาไทยจัดช่องด้วยช่องว่างเอง
       เพราะสระ/วรรณยุกต์ไทยทำให้ %-10s นับความกว้างไม่ตรง */
    printf("\nสัปดาห์      ออมได้        ยอดสะสม   กราฟ\n");
    printf("------------------------------------------------------------\n");
    for (i = 0; i < weekCount; i++) {
        running += saving[i];
        printf("%-6d %12.2f %14.2f   ", i + 1, saving[i], running);
        bar = (highest > 0) ? (int)(saving[i] / highest * 20) : 0;
        for (j = 0; j < bar; j++) printf("#");
        printf("\n");
    }
}

/* ---------- เมนู 4: สรุปผล (หัวใจหลักจากโค้ดที่ครูสอน) ---------- */
void showSummary() {
    int i, highestWeek = 1, lowestWeek = 1, weeksLeft, j, filled;
    float total = 0, average, highest = 0, lowest, remaining, percent;

    if (weekCount == 0) {
        printf("  ยังไม่มีข้อมูลการออม\n");
        return;
    }

    /* ===== โค้ดต้นแบบจากครู: หา Total และ Highest ด้วยลูป ===== */
    lowest = saving[0];
    for (i = 0; i < weekCount; i++) {
        total += saving[i];
        if (saving[i] > highest) {
            highest = saving[i];
            highestWeek = i + 1;
        }
        if (saving[i] < lowest) {       /* ต่อยอด: หา Lowest เพิ่ม */
            lowest = saving[i];
            lowestWeek = i + 1;
        }
    }
    average = total / weekCount;        /* ===== Average จากโค้ดครู ===== */

    printf("\n=== สรุปผลการออม ===\n");
    printf("ยอดออมรวม        : %.2f บาท\n", total);
    printf("เฉลี่ยต่อสัปดาห์    : %.2f บาท\n", average);
    printf("ออมมากที่สุด      : %.2f บาท (สัปดาห์ที่ %d)\n", highest, highestWeek);
    printf("ออมน้อยที่สุด     : %.2f บาท (สัปดาห์ที่ %d)\n", lowest, lowestWeek);

    /* ===== ต่อยอด: เทียบกับเป้าหมาย ===== */
    if (goalAmount > 0) {
        remaining = goalAmount - total;
        percent   = total / goalAmount * 100;
        if (percent > 100) percent = 100;

        printf("\n=== เป้าหมาย: %s ===\n", goalName);
        printf("จำนวนเงินเป้าหมาย : %.2f บาท\n", goalAmount);

        /* แถบความคืบหน้า 30 ช่อง */
        filled = (int)(percent / 100 * 30);
        printf("ความคืบหน้า       : [");
        for (j = 0; j < 30; j++) printf(j < filled ? "#" : "-");
        printf("] %.1f%%\n", percent);

        if (remaining <= 0) {
            printf("*** ยินดีด้วย! คุณออมเงินครบตามเป้าหมายแล้ว ***\n");
        } else if (average > 0) {
            weeksLeft = (int)(remaining / average);
            if (weeksLeft * average < remaining) weeksLeft++;   /* ปัดขึ้น */
            printf("ยังขาดอีก         : %.2f บาท\n", remaining);
            printf("คาดว่าจะครบในอีก  : %d สัปดาห์ (ถ้าออมเท่าค่าเฉลี่ย)\n", weeksLeft);
        } else {
            printf("ยังขาดอีก         : %.2f บาท\n", remaining);
            printf("เริ่มออมเงินเพื่อคำนวณเวลาที่จะถึงเป้าหมาย!\n");
        }
    } else {
        printf("\n(คำแนะนำ: ตั้งเป้าหมายที่เมนู 1 เพื่อดูความคืบหน้า)\n");
    }
}

/* ---------- เมนู 5: ลบข้อมูลสัปดาห์ล่าสุด (กรณีกรอกผิด) ---------- */
void undoLast() {
    if (weekCount == 0) {
        printf("  ไม่มีข้อมูลให้ลบ\n");
        return;
    }
    weekCount--;
    saveData();
    printf("  [OK] ลบสัปดาห์ที่ %d (%.2f บาท) แล้ว\n", weekCount + 1, saving[weekCount]);
}

/* ---------- เมนู 6: ล้างข้อมูลทั้งหมด ---------- */
void resetAll() {
    if (readInt("ต้องการลบข้อมูลทั้งหมดใช่ไหม? (1 = ใช่, 0 = ไม่): ", 0, 1) == 1) {
        weekCount  = 0;
        goalAmount = 0;
        strcpy(goalName, "เป้าหมายของฉัน");
        saveData();
        printf("  [OK] ล้างข้อมูลทั้งหมดแล้ว\n");
    }
}

/* ---------- โปรแกรมหลัก ---------- */
int main() {
    int choice;
#ifdef _WIN32
    SetConsoleOutputCP(65001);   /* ให้ console แสดงผลภาษาไทย (UTF-8) */
    SetConsoleCP(65001);         /* ให้ console รับภาษาไทยจากคีย์บอร์ด */
#endif
    loadData();
    do {
        printf("\n=====================================\n");
        printf("        ระบบออมเงิน (SAVINGS)\n");
        printf("=====================================\n");
        if (goalAmount > 0)
            printf(" เป้าหมาย: %s (%.2f บาท)\n", goalName, goalAmount);
        printf(" บันทึกแล้ว: %d สัปดาห์\n", weekCount);
        printf("-------------------------------------\n");
        printf(" 1. ตั้งเป้าหมายการออม\n");
        printf(" 2. บันทึกเงินออมรายสัปดาห์\n");
        printf(" 3. ดูประวัติการออม\n");
        printf(" 4. สรุปผล (ยอดรวม / เฉลี่ย / สูงสุด)\n");
        printf(" 5. ลบสัปดาห์ล่าสุด\n");
        printf(" 6. ล้างข้อมูลทั้งหมด\n");
        printf(" 0. ออกจากโปรแกรม\n");
        printf("-------------------------------------\n");
        choice = readInt("เลือกเมนู: ", 0, 6);

        switch (choice) {
            case 1: setGoal();     break;
            case 2: addSavings();  break;
            case 3: showHistory(); break;
            case 4: showSummary(); break;
            case 5: undoLast();    break;
            case 6: resetAll();    break;
            case 0: printf("ออมเงินต่อไปนะ! แล้วพบกันใหม่\n"); break;
        }
        if (choice != 0) {
            waitEnter();
            clearScreen();   /* กด Enter แล้วล้างหน้าจอ ก่อนแสดงเมนูใหม่ */
        }
    } while (choice != 0);

    return 0;
}
