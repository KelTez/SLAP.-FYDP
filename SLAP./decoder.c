function Decoder(bytes, port) {
  // Decode plain text; for testing only 
  return {
      IR_Sensor_Data: String.fromCharCode.apply(null, bytes),
      IMU_Sensor_Data: "1... ONLY TEST",
      Pod_Health: "1... ONLY TEST",
  };
}

