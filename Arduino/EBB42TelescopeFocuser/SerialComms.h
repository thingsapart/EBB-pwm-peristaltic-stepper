//     _____           _       _ 
//    / ____|         (_)     | |
//   | (___   ___ _ __ _  __ _| |
//    \___ \ / _ \ '__| |/ _` | |
//    ____) |  __/ |  | | (_| | |
//   |_____/ \___|_|  |_|\__,_|_|
//                               
//  

/**************************************************************
    Serial vars and g code processing
 *************************************************************/

//SERIAL COMMUNICATION
String G_SERIAL_TEXT;
String G_SERIAL_OUT;
bool G_SERIAL_LINE_FEED_RECEIVED;
char G_SERIAL_CHAR;
bool G_END_COMMAND_FOUND;
char G_END_OF_COMMAND_CHAR = '#';

/**************************************************************
    SERIAL PORT PROCESSING
 *************************************************************/

void P_PROCESS_SERIAL_PORT()
{
  // RESET IF WE FOUND LINE FEED LAST LOOP
  if (G_SERIAL_LINE_FEED_RECEIVED)
  {
    G_SERIAL_LINE_FEED_RECEIVED = false;
    G_SERIAL_TEXT = "";
  }

  // CHECK IF DATA IN SERIAL
  while (Serial.available()) // Serial.available() returns the number of bytes in the serial buffer so we keep looping until they all read or the loop exits because G_END_OF_COMMAND_CHAR was received
  {
    // READ SERIAL DATA INTO CHAR
    //G_SERIAL_CHAR = "";
    G_SERIAL_CHAR = Serial.read();

    //ADD VAR ONTO END OF STRING OF ALREADY RECEIVED CHARS
    if (G_SERIAL_CHAR != '\n' && G_SERIAL_CHAR != '\r') // Don't care about line feed and return s
    {
       G_SERIAL_TEXT += G_SERIAL_CHAR; 
    }

    //CHECK TO SEE IF WE GOT END OF COMMAND
    if (G_SERIAL_CHAR == G_END_OF_COMMAND_CHAR)
    {
      G_SERIAL_LINE_FEED_RECEIVED = true;
      break;
    }

  }
}

//     _____ _____  _      _____ _______    _____    _____ ____  _____  ______            _   _ _____    _____        _____            __  __  _____ 
//    / ____|  __ \| |    |_   _|__   __|  / ____|  / ____/ __ \|  __ \|  ____|     /\   | \ | |  __ \  |  __ \ /\   |  __ \     /\   |  \/  |/ ____|
//   | (___ | |__) | |      | |    | |    | |  __  | |   | |  | | |  | | |__       /  \  |  \| | |  | | | |__) /  \  | |__) |   /  \  | \  / | (___  
//    \___ \|  ___/| |      | |    | |    | | |_ | | |   | |  | | |  | |  __|     / /\ \ | . ` | |  | | |  ___/ /\ \ |  _  /   / /\ \ | |\/| |\___ \ 
//    ____) | |    | |____ _| |_   | |    | |__| | | |___| |__| | |__| | |____   / ____ \| |\  | |__| | | |  / ____ \| | \ \  / ____ \| |  | |____) |
//   |_____/|_|    |______|_____|  |_|     \_____|  \_____\____/|_____/|______| /_/    \_\_| \_|_____/  |_| /_/    \_\_|  \_\/_/    \_\_|  |_|_____/ 
//                                                                                                                                                   
//              
/**************************************************************
    SPLIT G CODE AND PARAMS
 *************************************************************/
// Badly named, just converts serial text into a command text and a parameter (if any) text string
 
String G_COMMAND;
String G_PARAMS;
bool   G_HAS_PARAMS;
int    G_PARAMS_START_AT;
int    G_INCOMING_STRING_LENGTH;
String G_FIRST_CHAR;


void P_SPLIT_G_CODE_AND_PARAMS()
{
  // First we will dig out the actual command
  G_COMMAND = "";
  G_PARAMS = "";
  G_SERIAL_OUT = "";
  G_HAS_PARAMS = false;
  G_PARAMS_START_AT = 0;
  G_END_COMMAND_FOUND = false;

  // Get length of string so we can loop through it
  G_INCOMING_STRING_LENGTH = G_SERIAL_TEXT.length();
  // Find first char of incoming string for later
  G_FIRST_CHAR = G_SERIAL_TEXT.charAt(0);

  // Loop through it
  for (int i = 0; i < G_INCOMING_STRING_LENGTH; i++)
  {
    // We are looking for one of two types of end command chars
    G_END_COMMAND_FOUND = false;

    // We found hash symbol
    if (G_SERIAL_TEXT.charAt(i) == G_END_OF_COMMAND_CHAR)
    {
      G_END_COMMAND_FOUND = true;
    }

    // We found space
    if (isWhitespace(G_SERIAL_TEXT.charAt(i)) && !G_END_COMMAND_FOUND)
    {
      G_HAS_PARAMS = true;
      G_END_COMMAND_FOUND = true;
      G_PARAMS_START_AT = i + 1;
    }

    // If we didn't find the end of the command
    // we will add the character to our command string
    // and continue looping until we find it
    if (!G_END_COMMAND_FOUND)
    {
      G_COMMAND += G_SERIAL_TEXT.charAt(i);
    }

    // if we did find the end of command then we just exit
    // loop otherwise carry on finding rest of command text
    if (G_END_COMMAND_FOUND)
    {
      G_COMMAND.toUpperCase();
      break;
    }
  }

  // Check to see if we got any parameters
  // And store them in param list if we did
  if (G_HAS_PARAMS)
  {
    G_PARAMS = G_SERIAL_TEXT.substring(G_PARAMS_START_AT, G_INCOMING_STRING_LENGTH - 1);
  }

}
