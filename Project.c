#include <stdio.h>
#include <string.h>

int main()
{
    
    char destinations[7][20] = {"Jamshedpur", "Ranchi", "Bokaro", "Dhanbad", "Deoghar", "Hazaribagh", "Ramgarh"};
    int distances[7] = {47, 20, 280, 347, 380, 15, 120}; 
    
   
    int seat_status[40] = {0}; 
    int seats_booked = 0;
    int choice_id;
    int bus_type_choice;
    int num_tickets;
    int distance_km = 0; 
    int stop_midway;
    double total_final_fare = 0.0;
    int main_menu_choice;
    int seat_to_cancel;
    int i, j, k; 
    


    while (1)
    {
        total_final_fare = 0.0; 
        printf("\n======================================================\n");
        printf("              UPES Bus Reservation System             \n");
        printf("======================================================\n");
        printf("1. Book New Ticket(s)\n");
        printf("2. Check Available Seats\n");
        printf("3. Cancel a Seat Reservation\n");
        printf("4. Exit Program\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &main_menu_choice) != 1) 
        {
            printf("\nInvalid input. Exiting.\n");
            
        }
        
     
        switch (main_menu_choice) 
        {
            
            case 1:
              
                printf("\n--- Available Destinations ---\n");
                printf("%-5s | %-20s | %-10s\n", "ID", "DESTINATION", "DISTANCE(km)");
                printf("------------------------------------------\n");
                for (i = 0; i < 7; i++) 
                {
                    printf("%-5d | %-20s | %-10d\n", i + 1, destinations[i], distances[i]);
                }
                printf("------------------------------------------\n");

               
                printf("Enter the ID of your destination (1-7): ");
                if (scanf("%d", &choice_id) != 1 || choice_id < 1 || choice_id > 7) 
                {
                    printf("\nERROR: Invalid Destination ID. Returning to main menu.\n");
                    break;
                }

                distance_km = distances[choice_id - 1];

                switch (choice_id)
                {
                    case 1: 
                    case 2: 
                    case 3:
                    case 4:
                    case 5: 
                    case 6: 
                    case 7:
                        printf("\nSelected Route: UPES to %s (Full Distance: %d km)\n", destinations[choice_id - 1], distance_km);
                        break;
                    default:
                        break; 
                }

                printf("\nChoose Bus Type:\n");
                printf("1. AC Bus (+20%% Surcharge)\n");
                printf("2. Non-AC Bus\n");
                printf("Enter choice (1 or 2): ");
                
                if (scanf("%d", &bus_type_choice) != 1 || (bus_type_choice != 1 && bus_type_choice != 2)) 
                {
                    printf("ERROR: Invalid Bus Type choice. Returning to main menu.\n");
                    break;
                }

                printf("\nHow many tickets do you want to book? (Max %d available): ", 40 - seats_booked);
                if (scanf("%d", &num_tickets) != 1 || num_tickets <= 0 || num_tickets > (40 - seats_booked)) 
                {
                    printf("ERROR: Invalid number of tickets or seats unavailable. Returning to main menu.\n");
                    break;
                }

    
                for (i = 0; i < num_tickets; i++) 
                {
                    char name[50];
                    int age;
                    char gender;
                    int seat_num = -1;
                    int final_distance_km = 0;
                    double base_fare_per_ticket = 0.0;
                    double final_ticket_price = 0.0;
                    
                    printf("\n--- Passenger %d Details ---\n", i + 1);

                    printf("Is this passenger traveling the full route to %s (1) or will stop midway (2)? ", destinations[choice_id - 1]);
                    if (scanf("%d", &stop_midway) != 1 || (stop_midway != 1 && stop_midway != 2)) {
                        printf("ERROR: Invalid choice. Assuming full route.\n");
                        stop_midway = 1;
                    }

                    if (stop_midway == 2)
                    {
                        printf("Enter the stopping  distance (km, max %d km): ", distance_km);
                        if (scanf("%d", &final_distance_km) != 1 || final_distance_km <= 0 || final_distance_km > distance_km) {
                            printf("ERROR: Invalid distance. Booking for full route (%d km).\n", distance_km);
                            final_distance_km = distance_km;
                        }
                    } 

                    else 
                    {
                        final_distance_km = distance_km;
                    }

       
                    double fare = 0.0;
                    int remaining_km = final_distance_km;

                    if (remaining_km > 0) 
                    {
                        int slab1_km = (remaining_km >= 20) ? 20 : remaining_km;
                        fare += slab1_km * 10.0;
                        remaining_km -= slab1_km;
                    }
                    if (remaining_km > 0)
                    {
                        int slab2_km = (remaining_km >= 20) ? 20 : remaining_km;
                        fare += slab2_km * 8.0;
                        remaining_km -= slab2_km;
                    }
                    if (remaining_km > 0) 
                    {
                        int slab3_km = (remaining_km >= 20) ? 20 : remaining_km;
                        fare += slab3_km * 6.0;
                        remaining_km -= slab3_km;
                    }
                    if (remaining_km > 0) 
                    {
                        fare += remaining_km * 5.0;
                    }
                    base_fare_per_ticket = fare;
                   
                    printf("Enter Passenger Name: ");
                    scanf(" %49s", name); 
                    
                    printf("Enter Passenger Age: ");
                    if (scanf("%d", &age) != 1 || age <= 0) 
                    {
                        printf("Invalid age. Skipping passenger.\n");
                        continue;
                    }

                    printf("Enter Passenger Gender (M/F): ");
                    scanf(" %c", &gender);
                    
           
                    if (gender >= 'a' && gender <= 'z') 
                    {
                        gender = gender - 32; 
                    }
            
                    if (seats_booked < 40) 
                    {
                        for (j = 0; j < 40; j++) {
                            if (seat_status[j] == 0) 
                            {
                                seat_status[j] = 1; 
                                seats_booked++;
                                seat_num = j + 1;
                                break;
                            }
                        }
                    } 
                    else 
                    {
                         printf("FATAL ERROR: Bus is full. Cannot assign seat.\n");
                         break; 
                    }

                 
                    switch (bus_type_choice)
                    {
                        case 1:
                            final_ticket_price = base_fare_per_ticket * (1.0 + (double)20 / 100.0);
                            break;
                        case 2: 
                            final_ticket_price = base_fare_per_ticket;
                            break;
                        default:
                            break;
                    }


                    double discount_amount = 0.0;
                    char discount_type[50] = "None";
                    if (age < 18) 
                    {
                        discount_amount = final_ticket_price * 0.30;
                        final_ticket_price -= discount_amount;
                        strcpy(discount_type, "Minor (30%)");
                    } 
                    else if (gender == 'F') 
                    {
                        discount_amount = final_ticket_price * 0.50;
                        final_ticket_price -= discount_amount;
                        strcpy(discount_type, "Woman (50%)");
                    }
                    
    
                    printf("\n------------------- TICKET PRINTED -------------------\n");
                    printf("Route:        UPES -> %s\n", destinations[choice_id - 1]);
                    printf("Distance:     %d km\n", final_distance_km);
                    printf("Bus Type:     %s\n", (bus_type_choice == 1) ? "AC" : "Non-AC");
                    printf("------------------------------------------------------\n");
                    printf("Passenger:    %s\n", name);
                    printf("Age/Gender:   %d / %c\n", age, gender);
                    printf("Seat No:      %d\n", seat_num);
                    printf("Discount:     %s (Rs. %.2lf)\n", discount_type, discount_amount);
                    printf("------------------------------------------------------\n");
                    printf("Base Fare:    Rs. %.2lf\n", base_fare_per_ticket);
                    printf("Final Fair:   Rs. %.2lf\n", final_ticket_price);
                    printf("------------------------------------------------------\n");
                    
                    total_final_fare += final_ticket_price;
                }

                printf("\n======================================================\n");
                printf("TOTAL BOOKING SUMMARY\n");
                printf("Total Passengers: %d\n", num_tickets);
                printf("Total Combined Fair: Rs. %.2lf\n", total_final_fare);
                printf("Seats remaining: %d\n", 40 - seats_booked);
                printf("======================================================\n");
                break;
            
            case 2: 
                printf("\n--- BUS SEATING LAYOUT (Total Seats: 40, Booked: %d) ---\n", seats_booked);
                printf("S = Seat, [B] = Booked, [A] = Available\n");
                printf("------------------------------------------------------\n");

                for (k = 0; k < 40; k++) 
                {
                    printf("S%02d [%c] ", k + 1   , (seat_status[k] == 1) ? 'B' : 'A');
                    
                   
                    if ((k + 1) % 4 == 0)
                    {
                        printf("\n");
                    }
                }
               
                printf("------------------------------------------------------\n");
                break;

            case 3: 
                printf("\n--- SEAT CANCELLATION ---\n");
                
                printf("Enter the seat number to cancel (1-40): ");
                scanf("%d", &seat_to_cancel);
               
                if (seat_to_cancel < 1 || seat_to_cancel > 40) 
                {
                    printf("ERROR: Seat number must be between 1 and 40.\n");
                } 
          
                else if (seat_status[seat_to_cancel - 1] == 0) 
                {
                    printf("ERROR: Seat %d is already Available (not booked).\n", seat_to_cancel);
                } 
             
                else
                {
                    seat_status[seat_to_cancel - 1] = 0; 
                    seats_booked--; 
                    printf("\nSUCCESS! Seat %d has been successfully cancelled.\n", seat_to_cancel);
                    printf("Remaining available seats: %d\n", 40 - seats_booked);
                }
                break;

            case 4: 
                printf("\nExiting the UPES Bus Reservation System. happy journey !\n");
                return 0; 
                

        }
    } 

    return 0;
}
