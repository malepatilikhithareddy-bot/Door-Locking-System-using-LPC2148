#include <lpc214x.h>
#include <string.h>
#include "timerdelay.h"
#include "lcd.h"
#include "keypad.h"
#define BUZZER bit(22) // Using P0.22 for buzzer
#define LED bit(23)  // Using P0.23 instead of buzzer



#define bit(x) (1 << x)

char pwd[5] = "3333";  // default password
char input[5];
int attempts = 0;
int entry = 0;

// Function declarations
void lock(void);

void handle_open_lock(void);
void handle_change_password(void);
void about(void);
void wrong_password_alert(void);

void buzz(void)
{
    IO0SET |= BUZZER;      // Turn ON buzzer
    timemdel(50);          // Small beep (~10ms)
    IO0CLR |= BUZZER;      // Turn OFF buzzer
}

void blink_led(void)
{
    IO0SET |= LED;      // Turn ON LED
    timemdel(25);       // Small blink (~10ms)
    IO0CLR |= LED;      // Turn OFF LED
}

int main(void)
{

    char choice;
    int i;
	
   IO0DIR |= BUZZER; // Set P0.22 as output
   IO0CLR |= BUZZER; // Make sure it's OFF initially
   IO0DIR |= LED;     // Set P0.23 as output
   IO0CLR |= LED;     // Ensure it's OFF at start


    lcd_init();
    

    while (1)
    {
	    lcd_cmd(0x01);
        lcd_string("Enter 1 for pwd");
        choice = get_key();
		blink_led(); 
		buzz();


        if (choice == '1') {
            handle_open_lock();
        } 
        else if (choice == '*') {
            handle_change_password();
        } 
        else if (choice == '#') {
            about();
        }  
        else {
            lcd_cmd(0x01);
            lcd_string("Invalid Choice");
            timemdel(50);
			buzz();
        }

    }

    return 0;
}



void handle_open_lock(void)
{
    int i;
    lcd_cmd(0x01);
    lcd_string("Enter Pwd:");
    for (i = 0; i < 4; i++)
    {
    input[i] = get_key();
    buzz();               // <- Add this line
    lcd_string("*");
	blink_led(); // Replaces the buzzer

    }

    input[i] = '\0';

    if (strcmp(input, pwd) == 0)
    {
        lock();
        attempts = 0;  // reset on success
    }
    else
    {
        attempts++;
        wrong_password_alert();
    }
}

void handle_change_password(void)
{
    int i;
    lcd_cmd(0x01);
    lcd_string("Old Pwd:");
    for (i = 0; i < 4; i++)
    {
        input[i] = get_key();
        lcd_string("*");
		buzz();
		blink_led(); 

    }
    input[i] = '\0';

    if (strcmp(input, pwd) == 0)
    {
        lcd_cmd(0x01);
        lcd_string("New Pwd:");
        for (i = 0; i < 4; i++)
        {
            pwd[i] = get_key();
            lcd_string("*");
			buzz();
			blink_led(); 

        }
        pwd[i] = '\0';
        lcd_cmd(0x01);
        lcd_string("Password Updated");
        timemdel(200);
    }
    else
    {
        lcd_cmd(0x01);
        lcd_string("Wrong Old Pwd");
        timemdel(200);
		buzz();
    }
}

void lock(void)
{	
    IO0DIR |= LED;     // Set P0.23 as output
    IO0CLR |= LED;     // Ensure it's OFF at start
    IO0SET |= LED;      // Turn ON LED
    timemdel(500);       // Small blink (~10ms)
    IO0CLR |= LED;
    entry +=1;
    IO0DIR |= bit(19) | bit(20);

    lcd_cmd(0x01);
    lcd_string("Lock Opening...");
    IO0SET |= bit(19);
    timemdel(50);
    IO0CLR |= bit(19);
    timemdel(1000);

    lcd_cmd(0x01);
    lcd_string("Lock Closing...");
    IO0SET |= bit(20);
    timemdel(100);
    IO0CLR |= bit(20);
	timemdel(1000);
}

void about(void)
{
    char buffer[16];  // buffer to hold converted number as string
    lcd_cmd(0x01);  

    sprintf(buffer, "Count: %d", entry);  // Convert int to string
    lcd_string(buffer);

    timemdel(200);
}

void wrong_password_alert(void)
{	 IO0DIR |= bit(21);     // Configure P0.21 as output
     IO0SET |= bit(21);
    lcd_cmd(0x01);
    lcd_string("Wrong Password!");
	buzz();
	timemdel(100);
	lcd_cmd(0x01);
    IO0CLR |= bit(21);     // Turn OFF LED
    lcd_cmd(0x01);
    if (attempts >= 3)
    {	
	    char buffer[16];
	    int i;
		IO0DIR |= bit(21);     // Configure P0.21 as output
        IO0SET |= bit(21); 
        lcd_cmd(0x01);
        lcd_string("Too Many Tries");
		buzz();
		timemdel(500);
		lcd_cmd(0x01);
		lcd_string("Retry in ");
		timemdel(100);
		buzz();
		
        // LED setup on P0.21
		for(i=10;i>=0;i--){    // Turn ON LED
        lcd_cmd(0x01);
        sprintf(buffer, "%d", i);
		lcd_string(buffer);
		buzz();
		timemdel(100);
		}
		

        IO0CLR |= bit(21);     // Turn OFF LED

        attempts = 0;  // reset after alert
		lcd_cmd(0x01);
    }
}



