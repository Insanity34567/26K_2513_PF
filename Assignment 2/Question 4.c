#include <stdio.h>
/* 
 * Header: Bakery_Festival_Sales.c
 * Description: Bakery Festival Sales Management System
 * Author: Aman Kumar
 */

int getvaliddays(){
    int days;
    printf("Enter the number of days for the bakery festival sales (1-7): ");
    scanf("%d", &days);
    while(days < 1 || days > 7){
        printf("Invalid input. Please enter a number between 1 and 7: ");
        scanf("%d", &days);
    }
    return days;
}

float calculateDailySales(int i) {
    printf("Enter the number of orders for day %d: ", i);
    int orders;
    float total_sales = 0.0;
    float highest_order = 0.0;
    scanf("%d", &orders);
    
    int f;
    printf("Enter the order amounts:- \n");
    for (f = 1; f <= orders; f++) {
        float amount;  
        scanf("%f", &amount);
        
        while (amount <= 0) {
            printf("Invalid input. Please enter a positive amount for order %d: ", f);
            scanf("%f", &amount);
        }
        
        total_sales += amount;
        
        if (f == 1 || amount > highest_order) {
            highest_order = amount;
        }
    }
    
    float average = total_sales / orders;
    printf("Total sales for day %d: %.2f\n", i, total_sales);
    printf("Average order amount for day %d: %.2f\n", i, average);
    printf("Highest order amount for day %d: %.2f\n", i, highest_order);
    
    return total_sales;
}

int findHighestSalesDay(float dailysales[], int number_of_days){
    int highest_sales_day = 0;
    float highest_sales = dailysales[0];
    int i;
    for (i=1; i<number_of_days; i++){
        if (dailysales[i] > highest_sales){
            highest_sales = dailysales[i];
            highest_sales_day = i;
        }
    }
    return highest_sales_day + 1;
}

void displayBarChart(float dailysales[], int number_of_days){
    printf("\n===== DAILY SALES BAR CHART =====[cite: 16]\n");
    int i;
    for (i=0; i<number_of_days; i++){
        printf("Day %d: ", i+1);
        int bar_length = (int)(dailysales[i] / 100); 
        int j;
        for (j=0; j<bar_length; j++){
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailysales[i]); 
    }
}

int main(){
    int days = getvaliddays();
    float dailysales[7]; //maximum 7 days
    float total_festival_sales = 0.0;
    int i;
    
    for (i = 1; i <= days; i++) {
        float total_sales = calculateDailySales(i);
        dailysales[i-1] = total_sales;
        total_festival_sales += total_sales;
    }
    
    int number_of_days = days;
    int highest_sales_day = findHighestSalesDay(dailysales, number_of_days);
    
    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", total_festival_sales);
    printf("Day with highest sales: Day %d\n", highest_sales_day);
    printf("Highest daily sales: Rs. %.2f\n", dailysales[highest_sales_day - 1]);
    
    displayBarChart(dailysales, number_of_days);
    return 0;



}


