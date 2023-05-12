# CSE211s: Introduction To Embedded Systems
## GPS Tracking using TM4C123

## Project description:
The project is mainly a GPS tracking system module which stores the coordinates of a start point and after reaching an end point it calculates the total distance taken by the user to navigate between them.

We’ve used the UART protocol to provide the longitude and latitude points.

We also used UART5 with Bluetooth configurations to show the total traveled distance on a smartphone to be easily understood by the users.

## Required tasks:
Using the texas instruments TM4C123GH6PM ARM Cortex-M4 microcontroller, we are required to write the embedded C program with the required drivers to:
1. Get the GPS data using UART protocol.
2. Control the built-in RGB led based on these criterias:
   - If distance from target > 10 m -> Turn `Red` led on.
   - If distance from target <= 5 m -> Turn `Yellow` led on.
   - If distance from target ~ 0 m -> Turn `Green` led on.
3. When the destination is reached, the total distance should be printed and it must be within 5% range of error.

### Aditions:
-  Using a bluetooth module to get the output from the microcontroller to a smarthphone.

## Example run of the project:
Video link: https://drive.google.com/file/d/1Pw2tym7RomJ8NxHQpPRE3LdAZ8ArI4zF/view?usp=share_link
