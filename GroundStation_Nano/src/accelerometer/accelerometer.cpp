#include "accelerometer.h"

void Accelerometer::accelerometer_init()
{
  Serial.println("Initialize MPU6050");

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("Não foi possível encontrar um sensor MPU6050 válido, verifique a ligação!");
    delay(500);
  }

  // Calibrar o giroscópio. A calibração deve estar em repouso.
  // Se você não quiser calibrar, comente esta linha.
  mpu.calibrateGyro();

  // Defina a sensibilidade do limite. Padrão 3.
  // Se você não quiser usar o limite, comente esta linha ou defina 0.
  mpu.setThreshold(1);

  // Verifique as configurações
  Accelerometer::accelerometer_settings();
}


DataAccelerometer Accelerometer::accelerometer_update()
{
  // Lê valores normalizados
  Vector normAccel = mpu.readNormalizeAccel();
  Vector normGyro = mpu.readNormalizeGyro();

  // Calcular Pitch & Roll
  pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;

  // Ignore o giroscópio se nossa velocidade angular não atingir nosso limite
  if (normGyro.ZAxis > 1 || normGyro.ZAxis < -1) {
    normGyro.ZAxis /= 100;
    yaw += normGyro.ZAxis;
  }

  // Mantenha nosso ângulo entre 0-359 graus
  if (yaw < 0)
    yaw += 360;
  else if (yaw > 359)
    yaw -= 360;

  DataAccelerometer updated_values;

  updated_values.pitch_value = pitch;
  updated_values.roll_value = roll;
  updated_values.yaw_value = yaw;

  return updated_values;
}

void Accelerometer::accelerometer_settings()
{
  Serial.println();

  Serial.print(" * Sleep Mode:        ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Clock Source:      ");
  switch (mpu.getClockSource()) {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Para o relógio e mantém o gerador de cronometragem reiniciado"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }

  Serial.print(" * Gyroscope:         ");
  switch (mpu.getScale()) {
    case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
  }

  Serial.print(" * Gyroscope offsets: ");
  Serial.print(mpu.getGyroOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getGyroOffsetZ());

  Serial.println();
}