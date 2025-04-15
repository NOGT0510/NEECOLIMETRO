#define SENSOR_PIN 26  // GPIO26 no ESP32

float alcohol_mg_per_l;
float alcohol_g_per_l;
int Ro = 469664.78 / 2.4;

void setup() {
  Serial.begin(115200);
  Serial.println("MQ3 warming up!");
  delay(12000);  // Espera o sensor aquecer (2 minutos)
}

float getgL(float rs_ro_ratio) {
  // Equação aproximada baseada na curva do datasheet MQ-3 (álcool)
  return 0.3946 * pow(rs_ro_ratio, -1.515);
}

void loop() {
  int sensor_value;
  float voltage;
  float mgL_ar;
  float rs_ro_ratio;
  float Rs;
  float gL_sangue;
  sensor_value = analogRead(SENSOR_PIN);

  // Conversão para tensao REAL do sensor (0–3.3V)
  voltage = sensor_value * 3.3 / 4095;
  Rs = (200000 * (3.3 - voltage)) / voltage;
  rs_ro_ratio = Rs/Ro;

  // Estimativa de álcool
  mgL_ar = getgL(rs_ro_ratio);
  Serial.print("Álcool no ar [mg/L_ar]: ");
  Serial.println(mgL_ar, 4);
  gL_sangue = mgL_ar * 0.0021;
  Serial.print("Álcool no sangue [g/L_sangue]: ");
  Serial.println(gL_sangue, 4);
  /* prints para verificar o valor Ro*/
  Serial.print("Rs: ");
  Serial.println(Rs);
  Serial.print("Voltage: ");
  Serial.println(voltage);
  Serial.println("---------------------------------- ");

/*
  Serial.print("Leitura analógica: ");
  Serial.print(sensor_value);
  Serial.print("  |  Voltagem: ");
  Serial.print(voltage, 2);
  Serial.print(" V  |  Álcool: ");
  Serial.print(alcohol_g_per_l, 4);  // Quatro casas decimais pra mais precisão
  Serial.println(" g/L");
*/
  delay(2000);
}
