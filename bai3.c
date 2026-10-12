#include <stdio.h>

struct BadDevice {
    char status;
    double voltage;
    char flag_phu;
    double current;
    double power;
    int time_minutes;
}; 

struct OptDevice {
    double voltage;
    double current;
    double power;
    int time_minutes;
    char status;
    char flag_phu;
}; 

int main() {
    printf("--- KET QUA TOI UU MEMORY PADDING ---\n");
    printf("Kich thuoc Struct CU: %zu bytes\n", sizeof(struct BadDevice));
    printf("Kich thuoc Struct MOI: %zu bytes\n", sizeof(struct OptDevice));
    printf("=========================================\n\n");

    struct OptDevice dev;
    dev.flag_phu = 'A'; 

    printf("--- NHAP THONG SO THIET BI IOT ---\n");
    printf("Trang thai (1-Bat, 0-Tat): ");
    
    int tempStatus;
    scanf("%d", &tempStatus);
    dev.status = (char)tempStatus;

    printf("Dien ap (V): ");
    scanf("%lf", &dev.voltage);
    printf("Dong dien (A): ");
    scanf("%lf", &dev.current);
    printf("Cong suat do duoc tu cam bien (W): ");
    scanf("%lf", &dev.power);
    printf("Thoi gian hoat dong (phut): ");
    scanf("%d", &dev.time_minutes);

    if (dev.status != 0 && dev.status != 1) {
        printf("\n[LOI] Trang thai khong hop le. Dung he thong!\n");
        return 1;
    }
    if (dev.voltage <= 0 || dev.current < 0 || dev.time_minutes < 0) {
        printf("\n[LOI] Du lieu ranh gioi sai. Dung he thong!\n");
        return 1;
    }

    printf("\n--- KIEM TRA AN TOAN VA THONG KE ---\n");
    
    double p_calc = dev.voltage * dev.current;
    double diff = dev.power - p_calc;
    if (diff < 0) {
        diff = -diff; 
    }

    if (diff > (0.05 * p_calc)) {
        printf("[CANH BAO] Cam bien cong suat bao sai lech! (Do: %.2f W | Tinh: %.2f W)\n", dev.power, p_calc);
    }

    if (dev.current > 30.0 || dev.power > 6600.0) {
        printf("[CANH BAO] QUA TAI NGUY HIEM!\n");
    }

    if (dev.status == 0 && dev.current > 0.05) {
        printf("[CANH BAO] RO RI DIEN HOAC TAI AN! Dong dien: %.2f A.\n", dev.current);
    }

    double kwh = (dev.power * ((double)dev.time_minutes / 60.0)) / 1000.0;
    
    printf("\n=> TONG KET: Dien nang tieu thu = %.4f kWh\n", kwh);

    return 0;
}