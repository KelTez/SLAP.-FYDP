function Decoder(bytes, port) {
  var decoded = {};
  
  // Decode bytes to int
  var parkByte = (bytes[0] << 8) | bytes[1]; //never change
  var rBoundByte = (bytes[2] << 8) | bytes[3]; //int, so not good
  var lBoundByte = (bytes[4] << 8) | bytes[5]; //int, so not good
  var magValByte = (bytes[6] << 8) | bytes[7]; //int, so not good, convert to float. or might keep everything as ints, might be good enough and less work
  
  // convert decimal byte values to int (ie, 01  == 256, want 1, 10 == 512, want 2)
  decoded.parkState = parkByte/256; //never cange
  decoded.rightBound = rBoundByte/100;
  decoded.leftBound = lBoundByte/100;
  decoded.magVal = magValByte/100; //most likely incorrect, for all but 'never change'
 
  return decoded;
}
