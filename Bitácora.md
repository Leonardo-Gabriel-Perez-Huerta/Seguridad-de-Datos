# Bitácora de Clase

---

## Conceptos sobre Seguridad de Datos

En esta sección se presentan los conceptos básicos relacionados con la seguridad de Datos, organizados de manera estructurada para facilitar su comprensión.

---

| Concepto | Definición |
|--------|------------|
| **Triada CIA (Confidentiality, Integrity, Availability)** | Modelo fundamental de la seguridad de la información que establece tres principios: confidencialidad, que garantiza que la información solo sea accesible por usuarios autorizados; integridad, que asegura que los datos no sean alterados sin autorización; y disponibilidad, que permite el acceso a la información cuando se necesita. |
| **Usability Triangle (Triángulo de Usabilidad)** | Modelo que relaciona seguridad, usabilidad y funcionalidad en un sistema. Incrementar la seguridad puede afectar la experiencia del usuario, por lo que se busca un equilibrio adecuado entre estos tres elementos. |
| **Riesgo** | Probabilidad de que una amenaza explote una vulnerabilidad y genere un impacto negativo. El riesgo considera tanto la posibilidad de ocurrencia como las consecuencias del incidente. |
| **MFA (Multi-Factor Authentication)** | Mecanismo de autenticación que requiere dos o más factores de verificación, basados en algo que el usuario sabe, posee o es, para confirmar su identidad y reducir accesos no autorizados. |
| **Vulnerabilidad** | Debilidad presente en un sistema, aplicación, red o en el factor humano que puede ser explotada por una amenaza. Puede originarse por errores de configuración, software desactualizado o malas prácticas de seguridad. |
| **Amenaza** | Evento, actor o circunstancia con el potencial de causar daño a un sistema o a la información. Puede ser intencional, como un ataque informático, o no intencional, como errores humanos o desastres naturales. |
| **Impacto** | Daño o consecuencia que se produce cuando una amenaza explota una vulnerabilidad. Puede implicar pérdidas económicas, interrupción de servicios, daño reputacional o pérdida de información. |

---

# Bitácora — Fundamentos de Seguridad de Datos y Redes

---

## 1. Authentication (Autenticación)
La **autenticación** es el proceso mediante el cual un sistema verifica la identidad de un usuario, dispositivo o entidad antes de permitir el acceso.

### Factores de autenticación
- **Algo que sabes:** contraseña, PIN
- **Algo que tienes:** token, tarjeta inteligente
- **Algo que eres:** biometría (huella, rostro)

### Importancia
- Evita accesos no autorizados
- Primer paso del control de acceso
- Base de auditoría y trazabilidad

---

## 2. Authorization (Autorización)
La **autorización** determina qué acciones puede realizar un usuario después de autenticarse.

### Ejemplo
Un usuario puede iniciar sesión (autenticación), pero solo el administrador puede borrar registros (autorización).

---

## 3. Accountability (Responsabilidad o Trazabilidad)
Garantiza que las acciones realizadas en un sistema puedan atribuirse a una identidad específica.

### Mecanismos
- Logs
- Auditorías
- Control de sesiones

---

## 4. Non-Repudiation (No repudio)
Impide que una entidad niegue haber realizado una acción.

### Mecanismos
- Firmas digitales
- Certificados
- Sellos de tiempo

---

## 5. MTA (Mail Transfer Agent)
Software responsable de transferir correos entre servidores.

### Funciones
- Enrutamiento
- Entrega de correo
- Gestión de colas

---

## 6. MFA (Multi-Factor Authentication)
Uso de dos o más factores de autenticación para verificar identidad.

### Ventajas
- Mayor seguridad
- Mitigación de robo de credenciales

---

## 7. TFA (Two-Factor Authentication)
Caso particular de MFA que usa exactamente dos factores.

---

## 8. Separation of Duties (Separación de funciones)
Principio de seguridad que distribuye responsabilidades para evitar abuso o fraude.

### Ejemplo
Quien aprueba pagos no es quien los ejecuta.

---

## 9. Least Privilege (Mínimo privilegio)
Los usuarios solo deben tener permisos estrictamente necesarios para su función.

### Beneficios
- Reduce impacto de ataques
- Minimiza errores humanos
- Limita movimiento lateral

---

## 10. Modelo OSI
Modelo conceptual de 7 capas que describe comunicaciones de red.

### Capas
1. Física
2. Enlace
3. Red
4. Transporte
5. Sesión
6. Presentación
7. Aplicación

### Importancia
- Diagnóstico
- Interoperabilidad
- Diseño de protocolos

---

## 11. Modelo TCP/IP
Arquitectura de red práctica usada en Internet.

### Capas
1. Acceso a red
2. Internet
3. Transporte
4. Aplicación

---

## 12. MAC Address y Spoofing
### MAC Address
Dirección física única de una interfaz de red.

### MAC Spoofing
Técnica de falsificación de la dirección MAC para:
- Evadir controles
- Suplantar dispositivos
- Realizar ataques de red

---

## 13. Dirección Física
Identificador hardware asignado a interfaces de red (MAC).

---

## 14. Switch
Dispositivo de red de capa 2 que conecta equipos dentro de una LAN.

### Funciones
- Conmutación de tramas
- Aprendizaje de direcciones MAC
- Segmentación de red

---

## 15. Direcciones Lógicas
Identificadores asignados por software (ej. IP) para comunicación entre redes.

### Diferencia clave
- MAC → hardware
- IP → software y enrutamiento

---

## 16. Troubleshooting
Proceso sistemático para diagnosticar y resolver fallos técnicos.

### Fases
1. Identificar problema
2. Establecer teoría
3. Probar solución
4. Implementar
5. Verificar
6. Documentar

---

## 17. Nmap
Herramienta de escaneo de red para descubrimiento de hosts y servicios.

### Usos
- Auditoría
- Pentesting
- Inventario de red

---

## 18. Falso Positivo
Alerta de seguridad que indica amenaza inexistente.

### Impacto
- Sobrecarga de análisis
- Pérdida de tiempo

---

## 19. Falso Negativo
Amenaza real que no es detectada por el sistema.

### Impacto
- Alto riesgo
- Compromiso silencioso

---

## 20. Vulnerabilidad
Debilidad explotable en sistema, red o aplicación.

### Tipos
- Software
- Configuración
- Hardware
- Humano

---

## 21. Hacker
Persona con conocimientos técnicos avanzados en sistemas y redes.

### Tipos
- White hat
- Black hat
- Gray hat

---


