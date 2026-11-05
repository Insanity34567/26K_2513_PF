#include <stdio.h>
/* 
 * Header: Amicable_Pairs.c
 * Description: Find amicable pairs up to n
 * Author: Aman Kumar
 */
#include <stdio.h>
// Function that returns the sum of proper divisors
int sumOfDivisors(int num) {
    if (num <= 1) return 0;
    int sum = 1; 
    
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i; // Add the divisor
            
            //if it's not a perfect square
            if (i != (num / i)) {
                sum += (num / i);
            }
        }
    }
    return sum;
}
int main() {
    int n;
    int count = 0;

    printf("Enter a number: \n");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);

    // Loop to check each number up to n
    for (int i = 2; i <= n; i++) {
        int sum1 = sumOfDivisors(i);
        
        if (sum1 > i && sum1 <= n) {
            int sum2 = sumOfDivisors(sum1);
            
            if (sum2 == i) {
                printf("(%d, %d)\n", i, sum1);
                count++;
            }
        }
    }

    if (count > 0) {
        printf("Total pairs: %d\n", count);
    } else {
        printf("No pairs found.\n");
    }

    return 0;
}