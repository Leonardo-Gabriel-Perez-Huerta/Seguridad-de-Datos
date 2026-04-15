# DeauthKeychain – ESP32-C3 Wi-Fi Deauthentication Tool con Interfaz Web

[![GitHub](https://img.shields.io/badge/status-working-brightgreen)]()

Este proyecto es una **herramienta de desautenticación WiFi** para el **ESP32-C3 Super Mini** que incorpora un **panel web interactivo**. Permite escanear redes cercanas y lanzar ataques de desautenticación (deauth) de forma selectiva y cancelable, todo desde un navegador conectado al punto de acceso del propio ESP32.

## ✨ Características principales

- **Panel web integrado** – Controla el ataque desde cualquier dispositivo con navegador (móvil, tablet, PC).
- **Escaneo de redes WiFi** – Detecta SSID, canal, intensidad de señal y BSSID de los puntos de acceso cercanos.
- **Ataque de desautenticación dirigido** – Selecciona la red objetivo desde la interfaz web.
- **Ataque continuo pero cancelable** – El ataque puede detenerse en cualquier momento con un botón en la web.
- **No bloqueante** – El servidor web sigue respondiendo mientras se ejecuta el ataque (gracias a `runAttack()` en el `loop()`).
- **Máxima efectividad** – Envío de ráfagas de 100 paquetes de deauth con latencia mínima.
- **Optimizado para ESP32-C3** – Utiliza `esp_wifi_80211_tx()` para inyección de tramas raw y evita bibliotecas asíncronas problemáticas.
- **Sin dependencias externas complicadas** – Solo usa `WiFi.h` y `esp_wifi.h` del framework de Arduino.

## 🛠️ Requisitos de hardware

- **ESP32-C3 Super Mini** (u otra placa con chip ESP32-C3)
- Cable USB-C (que soporte datos)
- Alimentación USB (PC, power bank o cargador)

## 📥 Instalación y configuración

1. **Clona el repositorio** (o copia los archivos fuente):
   ```bash
   git clone https://github.com/tuusuario/DeauthKeychain-Web.git

## Uso de la interfaz web

1. **Enciende el ESP32** (se iniciará automáticamente al recibir corriente).
2. **Conéctate a su red WiFi**:
   - SSID: `MiDeauther`
   - Contraseña: `12345678`
3. **Abre un navegador** y visita `http://192.168.4.1`.
4. **Escanea redes cercanas** pulsando el botón **📡 Escanear redes**.
5. **Selecciona una red objetivo** (debe ser de tu propiedad o con autorización) y haz clic en **⚡ Atacar**.
6. **Observa el efecto** – Los dispositivos conectados a esa red se desconectarán.
7. **Detén el ataque** en cualquier momento con el botón **⏹️ Detener ataque**.

## ¿Cómo funciona el ataque de desautenticación?

El ataque explota una debilidad del protocolo WiFi en sus versiones WPA2 y anteriores: las **tramas de gestión** (como la de desautenticación) **no están cifradas**. Cualquier dispositivo puede falsificarlas.

Tu ESP32 actúa de la siguiente manera:

1. **Escanea** las redes cercanas para obtener la dirección MAC (BSSID) y el canal del router objetivo.
2. **Se sintoniza** en ese canal.
3. **Construye una trama de desautenticación** (deauth frame) que parece provenir del router legítimo:
   - Dirección origen = MAC del router (falsificada)
   - Dirección destino = broadcast (`FF:FF:FF:FF:FF:FF`) o la MAC de un cliente específico.
4. **Envía la trama** cientos de veces por segundo usando `esp_wifi_80211_tx()`.
5. Los dispositivos receptores, al creer que la orden viene del router, **se desconectan inmediatamente**.

Si el ataque es continuo (como en este código), los dispositivos no alcanzan a reconectarse y la red queda inutilizable mientras dure el ataque.

## ⚠️ Aviso legal y ético

**Este proyecto es exclusivamente con fines educativos y de investigación en seguridad.**

El uso no autorizado de ataques de desautenticación (deauth) es **ilegal** en muchos países y viola las políticas de uso aceptable de redes.

**Solo debe utilizarse en redes propias o con permiso explícito del propietario.**

El autor no se hace responsable del mal uso de esta herramienta. Al emplearla, usted acepta la responsabilidad total sobre sus acciones.

## Personalizaciones realizadas respecto al repositorio original

| Característica del repositorio original | Mejora implementada |
|------------------------------------------|----------------------|
| Ataque automático e ininterrumpido | Ahora es **selectivo y cancelable** desde una interfaz web. |
| Sin interfaz de usuario | Se añadió un **panel web completo** (HTML/CSS/JS) alojado en el ESP32. |
| Usaba bibliotecas asíncronas incompatibles con ESP32-C3 | Se reemplazó por un **servidor síncrono** (`WiFiServer`) 100% compatible. |
| El ataque bloqueaba el resto de funciones | El código es **no bloqueante**; el servidor web responde incluso durante el ataque. |
| Solo podía detenerse reiniciando el ESP32 | Se incorporó un **botón "Detener ataque"** que detiene el envío de paquetes al instante. |
| Los delays fijos limitaban la efectividad | Se optimizaron los tiempos para enviar ráfagas de 100 paquetes con latencia mínima. |

## Licencia

Este proyecto se distribuye bajo la licencia **MIT**. Se proporciona "tal cual", sin garantías de ningún tipo.
Eres libre de usarlo, modificarlo y distribuirlo siempre que mantengas el aviso de copyright y la licencia original.
