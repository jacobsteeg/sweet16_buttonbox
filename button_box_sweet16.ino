#include <Joystick.h>

const int numRows = 4; // Number of rows in the matrix
const int numCols = 4; // Number of columns in the matrix

// Define the Arduino pins connected to the rows
int rowPins[numRows] = {A0, A1, A2, A3};

// Define the Arduino pins connected to the columns
int colPins[numCols] = {2, 3, 4, 5};

// Initialize the Joystick library
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 16, 0,
  false, false, false, false, false, false,
  false, false, false, false, false);

void setup() {
  Joystick.begin();
  // Initialize the row pins as outputs
  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
  }

  // Initialize the column pins as inputs with pullup resistors
  for (int i = 0; i < numCols; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  int buttonId = 0;
  // Scan the button matrix
  for (int row = 0; row < numRows; row++) {
    // Set the current row LOW
    digitalWrite(rowPins[row], LOW);

    // Check each column
    for (int col = 0; col < numCols; col++) {
      buttonId++;
      // Read the button state (active LOW)
      bool buttonState = !digitalRead(colPins[col]);
      // Update the button state in the Joystick library
      Joystick.setButton(buttonId - 1, buttonState);
    }

    // Set the current row back to HIGH
    digitalWrite(rowPins[row], HIGH);
  }

  // Small delay to debounce
  delay(50);
}
