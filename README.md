### IntroductionToRobotics

# Homework 0
Creating Github Repo

# Homework 1
 Use a different potentiometer in controlling each of the color of the RGB led (Red,Green and Blue). The control must be done with digital electronics(aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.)
**[Link Video](https://www.youtube.com/shorts/tXOv2wLMJO4)**

![WhatsApp Image 2022-10-23 at 15 55 35](https://user-images.githubusercontent.com/39965333/197393710-37d05769-bde8-4796-ad36-10f4df25b93f.jpg)

# Homework 2
Building the traffic lights  for a crosswalk.You will use 2 LEDs to represent the traffic lights for people (red and green)and 3 LEDs to represent the traffic lights for cars (red, yellow and green). **[Link Video](https://youtube.com/shorts/XuJmmIKzuxQ)**
![WhatsApp Image 2022-11-04 at 9 53 27 AM](https://user-images.githubusercontent.com/39965333/199921659-39f82a1b-711a-4fd7-8eae-b7eeb510eb24.jpeg)

# Homework 3
This project will use the joystick and the 7-segment display. The movement between segments should be natural (meaning they should jump from the current position only to neighbors, but without passing through "walls". I used a matrix of movements that stores the direction in which it should jump depending on the current position. I implemented this project with the next arhitecture: This embedded system runs on 2 states. State 1 allows the user to move between the segments and State 2 blocks the current segment and could be turned on or turned off. The user can get back to a segment that already is on in order to turn it off. This system allows the user to "draw" on the 7-segment display.  **[Link Video](https://youtube.com/shorts/-AmXUNjfck0)**
![WhatsApp Image 2022-11-10 at 20 53 34](https://user-images.githubusercontent.com/39965333/201185355-2ae0d8d5-710b-4198-abf3-d18ef757f998.jpg)

# Homework 4
The joystick is used in this project to move through the 4 digit 7segment displays digits. If the button is pressed to lock in on the current digit and use the other axis to increment or decrement the number. This system use a State Machine. The first state is choosing the digit the user want to change and the second state of the system enables the digit changing. Furthermore for the display's implementations, I used the multiplexing of the bits and a classical shift register. For this reason, in the picture and the video I took the segments are flickering. In the picture, the camera of my phone catch only 2 of the 4 displays turn on.
 **[Link Video](https://youtube.com/shorts/_M0VwvUTyTM)**
 ![WhatsApp Image 2022-11-18 at 12 29 13](https://user-images.githubusercontent.com/39965333/202758259-89e8e52b-1773-4fc1-8c85-4948a93993e2.jpg)
 
 
 # Homework 5
This is sub-project of the final Matrix Game. I used a breadboard, a joystick and a button to develop a retro game controller. To the Arduino Uno I connected an LCD Screen too where it should display the menu of the future game.

### Implementation Ideas
 I tought the menu as a DFA. I created a matrix of movements like the transition function. START GAME state is connected to the GAMEPLAY state, SETTINGS state is connected to the Username state which is related as well with Difficulty state and so on.
 
 The game should store those info somewhere and I prepared it to be written on Arduino UNO's EEPROM. I defined a struct for the system's info(eg. matrix brightness) and a struct for player's info(his 3 letters name and his score). The EEPROM should be updated with the system info and the highscores of 3 best players only when it was changed  because we should avoid excesivly excessively writing on this type of memory.
 
 The refresh time of the LCD display is 250ms which means the refresh frequency rate is 4Hz.
 
 One move UP or DOWN of the joystick can iterate only to the next state, even if the user is holding it. The exception is made at username, you cand iterate trough all characters just by holding it UP or DOWN because it's faster to choose your name. In the first place I used one move one itaration for the username too but it was too slow. 
 
 **[Link Video](https://youtu.be/Jl3W35kquCA)**
 
 ![45](https://user-images.githubusercontent.com/39965333/205901945-74db2116-aab8-4e4e-985e-de2d674d6b8a.jpg)

![WhatsApp Image 2022-12-06 at 13 34 54](https://user-images.githubusercontent.com/39965333/205901969-38a0934f-de2e-4c71-9ebf-ad9014b5fbf0.jpg)

