function Decoder(bytes, port) {
  var decoded = {};
  
  // Decode bytes to int
  var payloadByte = (bytes[0] << 8) | bytes[1];
  
  // convert decimal byte values to int (ie, 01  == 256, want 1, 10 == 512, want 2)
  decoded.parkState = payloadByte/256;
 
  return decoded;
}
