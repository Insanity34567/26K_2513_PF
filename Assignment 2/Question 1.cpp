#include <stdio.h>
/*
    *header = Cinema.Booking.c
    *Author= Aman Kumar    
*/
int main(){
    int x,y;
    printf("Enter the number of rows and columns in the cinema hall: ");
    scanf("%d %d",&x,&y);
    int cinema[x][y]={0};
    int seats_available[100][1];
    int total=0;
    int col=0;
    for (int i=0;i<100;i++){
        for(int j=0;j<0;j++){
            seats_available[i][j]=0; //initializing the array with 0
        }
    }

    printf("Enter the elements for a %dx%d grid:\n", x, y);
    
    for (int r = 0; r < x; r++) { //initializing the array with user input
        for (int c = 0; c < y; c++) {
            scanf("%d", &cinema[r][c]);
        }
    }
    printf("\nCinema seating arrangement:\n");
    int i=0;
    int j=0;
    for(i=0;i<x;i++){ //displaying the initialized array
        printf("Row %d: ", i);
        col=0;
        for(j=0;j<y;j++){
            if (cinema[i][j] == 0) {
                col++;
                total++;
                printf("_ "); // Display '_' for empty seats
            } else {
                printf("X "); // Display 'X' for booked seats
            }
        }
        seats_available[i][0]=col;
        printf("\n");
    }
    printf("Seat Availability Report:\n");
    for(i=0;i<x;i++){
        printf("Row %d: %d seats available\n", i, seats_available[i][0]);
    }   
    printf("Total seats available: %d\n", total);
    printf("Enter the number of customers: \n");
    
    int k; //number of customers
    scanf("%d", &k);
    
    if(k<=0 || k>y){ // Validate the group size
        printf("Invalid group size. Booking unsuccessful.\n");
        return 0;
    }
    
    int mid_row= x/2;
    int found=0;
    for (int dist=0; dist<=x && found==0; dist++){
        int r_to_check[2]={-1,-1};
        if(dist==0){
            r_to_check[0]=mid_row;
        } else {
            r_to_check[0]=mid_row-dist;
            r_to_check[1]=mid_row+dist;
        }
        for(int i=0;i<2 && found==0;i++){
            int r=r_to_check[i];
            if(r>=0 && r<x){
                int consecutive=0;
                for(int c=0;c<y;c++){
                    if(cinema[r][c]==0){
                        consecutive++;
                    } else {
                        consecutive=0;
                    }
                    if(consecutive==k){
                        found=1;
                        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n", k, r, c-k+1, c);
                        for(int seat=c-k+1;seat<=c;seat++){
                            cinema[r][seat]=1; // Mark seats as booked
                        }
                        break;
                    }
                }
            }
        }
    }
    if (found == 1) {
        printf("\nBooking successful.\n");
        printf("\nUpdated Cinema seating arrangement:\n\n");
    total=0;
    for(i=0;i<x;i++){ //displaying the initialized array
        printf("Row %d: ", i);
        col=0;
        for(j=0;j<y;j++){
            if (cinema[i][j] == 0) {
                col++;
                total++;
                printf("_ "); // Display '_' for empty seats
            } else {
                printf("X "); // Display 'X' for booked seats
            }
        }   
        seats_available[i][0]=col;
        printf("\n");
    }
    printf("\nSeat Availability Report:\n");
    for(i=0;i<x;i++){
        printf("Row %d: %d seats available\n", i, seats_available[i][0]);
    }   
    printf("Total seats available: %d\n", total);
    
    } else {
        printf("\nBooking unsuccessful. No suitable seats available.\n");
    }


    return 0;
}